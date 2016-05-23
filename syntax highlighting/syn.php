#!/usr/bin/php5
<?php
#SYN:xzelia00
 // syn.php
 // Implementation of syntax highlighter, 28.2.2014
 // Autor: Dusan Zeliar,xzelia00, FIT

setlocale(LC_ALL, 'cs_CZ');
/*FUNCTIONS*/

// wrong command line argumets or their combination
function wrongParameters () {
	fwrite(STDERR, "wrong combination or format of arguments\n");
	exit(1);
}
//function pritns help and exits 
function help () {
	fwrite(STDOUT, "Script highlights various parts of text\n");
	fwrite(STDOUT, "Parameters:\n");
	fwrite(STDOUT, "--help - print help to standard output\n");
	fwrite(STDOUT, "--format=filename - set format file\n");
	fwrite(STDOUT, "--input=filename - set UTF-8 input file\n");
	fwrite(STDOUT, "--output=filename - set UTF-8 output file\n");
	fwrite(STDOUT, "--br - add <br /> element to end of each line\n\n");
	fwrite(STDOUT, "Autor: Dusan Zeliar, 2015\n");

	exit(0);
}
//function is called with error message to print and exit code, also closes opened files
function fileError ($message,$returnValue){
    //close open files
    if ($GLOBALS['format_set']==TRUE){
        if ($GLOBALS['format_file']) fclose($GLOBALS['format_file']);
    }    
    if ($GLOBALS['output_set']==TRUE){
        if ($GLOBALS['output_file']) fclose($GLOBALS['output_file']);
    }
	fwrite(STDERR, $message);
	exit($returnValue);

}
//function is called when no format files is set, just prints input to output
function noFormatOutput($output_file,$content,$br){
$output="";
$slen=strlen($content);
for ($i = 0; $i < $slen; $i++) {
    if (($br) and ($content[$i]=="\n")){
        $output=$output."<br />\n";
    }else $output=$output.$content[$i];
}
fwrite($output_file, $output);
//close open files
if ($GLOBALS['format_set']==TRUE){
    if ($GLOBALS['format_file']) fclose($GLOBALS['format_file']);
}    
if ($GLOBALS['output_set']==TRUE){
    if ($GLOBALS['output_file']) fclose($GLOBALS['output_file']);
}

exit(0);
}
//function apply regex expression and saves start and stop tag to array of tags
function Format($start,$stop,$filter,&$array_of_tags,&$format_file){
		//apply regular expression
		$filter="/".$filter."/su";

		preg_match_all($filter, $format_file, $matches, PREG_OFFSET_CAPTURE);

        //for every match put start and stop tag to array
		for ($i = 0; $i < count($matches[0]); $i++) {

			$index_start=$matches[0][$i][1];
			$string=$matches[0][$i][0];
            //empty string
            if($string == '') continue;
			$index_stop=strlen($string)+$index_start;
			//put start html tag
			if (array_key_exists($index_start, $array_of_tags)) {
			    $array_of_tags[$index_start]=$array_of_tags[$index_start].$start;
			}else $array_of_tags[$index_start] = $start;
			//put stop html tag
			if (array_key_exists($index_stop, $array_of_tags)) {
			    $array_of_tags[$index_stop]=$stop.$array_of_tags[$index_stop];
			}else $array_of_tags[$index_stop] = $stop;
		}
			
}
//function takes one line of format line and creates a formal expression to match regex requirements
function createNewFormatExpression ($line,&$array_of_tags,&$format_file) {
	$format_line=explode('	', $line, 2);
	if (count($format_line) !== 2) fileError("Invalid format file\n",4);
	$regular_expression=$format_line[0];
	//var_dump($regular_expression);

	//helpful variables
	$state="start";
	$slen=strlen($regular_expression);
	//put ( to start and end )
	$filter="(";
	//helpful array to check if every ( bracket has )
	$bracket=array();

    $neg="false";

	for ($i = 0; $i < $slen; $i++) {
		//var_dump($regular_expression[$i]);
		//var_dump($state);
		//var_dump($neg);

        if (ord ( $regular_expression[$i]) < 32) fileError("Invalid char in format file\n",4);

        //basic automat states: start, char, special and ! negation
        if ($state == "start"){
        	switch ($regular_expression[$i]) {
        		//negation
        		case '!':
        			 $state="!";
        			break;
        		//counts brackets
        		case '(':
        			 $bracket[]="(";
        			 $filter=$filter."(";
        			break;
        		//special char
        		case '%':
        			 $state="special";
        			break;
        		//chars that cant be at the start of expression
        		case '.':
        		case '|':
        		case ')':
        		case '*':
        		case '+':
        			fileError("Invalid char in format file\n",4);
        			break;
        		//regex function special characters, add \to eliminate special usage
        		case ('\\'):
                case '/':
        		case '^':
        		case '$':
        		case '[':
        		case ']':
        		case '?':
        		case '}':
        		case '{':
        			$filter=$filter.'\\'.$regular_expression[$i];
        			$state="char";
        			break;
        		//all nomal ascii >=32 characters
        		default:
        		    $filter=$filter.$regular_expression[$i];	
        		    $state="char";
        			break;
        	}
        }
        else if ($state=="char"){
            //if negation is set, only one char can follow
            if ($neg == "yes"){
                if (($regular_expression[$i]!='|') and ($regular_expression[$i]!=')')) fileError("Invalid char in format file\n",4);
            }
        	switch ($regular_expression[$i]) {
        		//negation
        		case '!':
        			 $state="!";
        			break;
        		//counts brackets
        		case '(':
        			 $state="start";
        			 $bracket[]="(";
        			 $filter=$filter."(";
        			break;
        		case ')':
                     if ($neg == "yes"){
                        $neg_bracket=FALSE;
                    }else{
        			 if (empty($bracket)) {fileError("Invalid char in format file\n",4);}
        			 array_pop($bracket);
        			 $filter=$filter.")";
                     }
        			break;
        		//special char
        		case '%':
        			 $state="special";
        			break;
        		//concatenate, old +new
        		case '.':
        			 $state="start";
        			break;
        		//regex function special characters, add \to eliminate special usage
        		case '\\':
                case '/':
        		case '^':
        		case '$':
        		case '[':
        		case ']':
        		case '?':
        		case '}':
        		case '{':
        			$filter=$filter.'\\'.$regular_expression[$i];
        			break;
                //check if neg is set, | will not be written
                case '|':
                    if ($neg == "yes"){
                        $state="start";
                    }else {
                        $filter=$filter.$regular_expression[$i];
                    }
                    break;
        		//all nomal ascii >=32 characters
        		default:
        		    $filter=$filter.$regular_expression[$i];	
        			break;
        	}
        }else if ($state=="special"){
            if ($neg == "yes"){
            	//endign bracket after neg
            	if ( $neg_bracket==FALSE) {
            		$neg="no";
            		$end_neg="]";
            	}else $end_neg="";
                //unset bracket []
                $left="";
                $right="";
            }else{
            	$end_neg="";
                $left="[";
                $right="]";
            }
        	switch ($regular_expression[$i]) {
        		case 's':
        			//whitespace chars
        			$filter=$filter."\s".$end_neg; 
        			$state="char";
        			break;
        		case 'a':
        			//any char
        			$filter=$filter.".".$end_neg; 
        			$state="char";
        			break;
        		case 'd':
        			//any number
        			$filter=$filter."\d".$end_neg; 
        			$state="char";
        			break;
        		case 'l':
        			//any [a-z] char
        			$filter=$filter.$left."a-z".$right.$end_neg; 
        			$state="char";
        			break;
        		case 'L':
        			//any [A-Z] char
        			$filter=$filter.$left."A-Z".$right.$end_neg; 
        			$state="char";
        			break;
        		case 'w':
        			//any [a-zA-Z] char
        			$filter=$filter.$left."a-zA-Z".$right.$end_neg; 
        			$state="char";
        			break;
        		case 'W':
        			//any [a-zA-Z0-9] char
        			$filter=$filter.$left."a-zA-Z0-9".$right.$end_neg; 
        			$state="char";
        			break;
        		case 't':
        			//tab
        			$filter=$filter."\t".$end_neg; 
        			$state="char";
        			break;
        		case 'n':
        			//newline
        			$filter=$filter."\n".$end_neg; 
        			$state="char";
        			break;

        		//not special chars in regex
        		case '!':
        		case '%':
        		    $filter=$filter.$regular_expression[$i].$end_neg; 
        			$state="char";
        			break;
        		//special chars in regex
        		case '.':
        		case '|':
        		case '*':
        		case '+':
        		case '(':
        		case ')':
        			$filter=$filter.'\\'.$regular_expression[$i].$end_neg;
        			$state="char";
        			break;
        		
        		default:
        		    fileError("Invalid char in format file\n",4);
        			break;
        	}
        }else if ($state=="!"){
            $neg="yes";
            $neg_bracket=FALSE;
            $filter=$filter."[^";
            switch ($regular_expression[$i]) {
                //chars that cant be at the start of expression
                case '.':
                case '|':
                case ')':
                case '*':
                case '+':
                    fileError("Invalid char in format file\n",4);
                    break;
                case '\\':
                case '/':
                case '^':
                case '$':
                case '[':
                case ']':
                case '?':
                case '}':
                case '{':
                    $filter=$filter.'\\'.$regular_expression[$i];
                    $state="char";
                    $neg="no";
                    $filter=$filter.']';
                    break;
                //special char
                case '%':
                     $state="special";
                    break;
                case '(':
                     $state="start";
                     $neg_bracket=TRUE;
                    break;
                default:
                    $filter=$filter.$regular_expression[$i]; 
                    $state="char";
                    $neg="no";
                    $filter=$filter.']';
                }
            }

            if ($neg=="yes"){
                //add ending bracket
                if (($state=="char") and ($neg_bracket==FALSE))  {
                	$state="start";
                    $filter=$filter.']';
                    $neg="no";
                }
            }
    }
    //not ended negation
    if ($neg=="yes" or $state=="!") {fileError("Invalid chars in format file\n",4);}
    //not right operant to dot
    if ($state=="start" and $regular_expression[$i-1]==".") fileError("Invalid chars in format file\n",4);

    //count brackets
    if (!empty($bracket)) {fileError("Invalid chars in format file\n",4);}
    //put ( to start and end )
	$filter=$filter.")";

    //List of commands
    $commands=$format_line[1];
    //var_dump($commands);

    //remove rest od tabulators
    $commands = preg_replace('/^\t*/', '', $commands);
    //check there is no empty file and there are no spaces at start of first command 
    if (empty($commands)) fileError("invalid format file\n",4);
    if($commands[0] == " ") fileError("invalid format file\n",4);

    $commands=explode(',', $commands, 2);
    $format_expression=$commands[0];

    while (!empty($format_expression))
    {
        //remove white chars
        $format_expression = preg_replace('/^\s*/', '', $format_expression);
        //remove white chars at end of string
        $format_expression = preg_replace('/\s*$/', '', $format_expression);

        switch ($format_expression) {
            case "bold":
                Format("<b>","</b>",$filter,$array_of_tags,$format_file);
                break;
            case "italic":
                Format("<i>","</i>",$filter,$array_of_tags,$format_file);
                break;
            case "underline":
                Format("<u>","</u>",$filter,$array_of_tags,$format_file);
                break;
            case "teletype":
                Format("<tt>","</tt>",$filter,$array_of_tags,$format_file);
                break;
            default:
                if(preg_match("/^size:[1-7]$/", $format_expression)){
                    Format("<font size=".$format_expression[5].">","</font>",$filter,$array_of_tags,$format_file);
                }
                else if(preg_match("/^color:[0-9A-Fa-f][0-9A-Fa-f][0-9A-Fa-f][0-9A-Fa-f][0-9A-Fa-f][0-9A-Fa-f]$/", $format_expression)){
                    $start="<font color=#".$format_expression[6].$format_expression[7].$format_expression[8].$format_expression[9].$format_expression[10].$format_expression[11].">";
                    Format($start,"</font>",$filter,$array_of_tags,$format_file);
                }
                else fileError("invalid format file\n",4);
                break;
        }

        if (count($commands) !== 1){
        $commands=$commands[1];
        $commands=explode(',', $commands, 2);
        $format_expression=$commands[0];
        } else $format_expression="";
    }

}



$shortopts ="";
$longopts  = array(
    "help",
    "format:",
    "output:",
    "input:",
    "br"
);
$options = getopt($shortopts, $longopts);

//Create two variables to find redundant arguments
$arg_count=$argc;
//firs decrease number (script name)
--$arg_count;
// "split" arguments with '=' to two
foreach ($argv as $argv => $value) {
	if (strpos($value, '=') !== false) ++$arg_count;
}

$opt_count=0;
$opt=$options;
//count all parameners and their value
foreach ($opt as $opt => $value) {
	++$opt_count;
	if ($value != FALSE) ++$opt_count;
}

if ($opt_count != $arg_count){
	wrongParameters();
}

// Handle command line arguments
// helpful variable checks if all requested arguments were set
$format_set=FALSE;
$input_set=FALSE;
$output_set=FALSE;
$input_file_name='php://stdin';
$output_file_name=STDOUT;
$output_file=STDOUT;
$format_file_name=STDIN;
$format_file='';
$br=FALSE;
foreach ($options as $options => $value)  {
	switch ($options) {
		case 'help':
            if ($argc != 2){
    	        wrongParameters();
            }
            else help();
        break;
        case 'input': 
            if ($input_set==TRUE) wrongParameters();
            $input_set=TRUE;
            $input_file_name=$value;
            break;
        case 'output':
            if ($output_set==TRUE) wrongParameters();
            $output_set=TRUE;
            $output_file_name=$value;
            break;
        case 'format':
            if ($format_set==TRUE) wrongParameters();
            $format_file_name=$value;
            $format_set=TRUE;
            break;
        case 'br':
            if (count($value) != 1) wrongParameters();
            $br=TRUE;
            break;
    }
}

//set output file
if ( $output_set==TRUE)  
{   
	if (file_exists($output_file_name)){
		if (!is_writeable($output_file_name)){
			fileError("fail-output file\n",3);
		}
	}
	if (FALSE ===( $output_file= fopen($output_file_name, 'w'))){
	    fileError("fail-output file\n",3);
	}
}else {
	$output_file=STDOUT;
}

//load input
$content="";
if ( $input_set==TRUE)  
{   
	if (!is_readable($input_file_name)){
		fileError("fail- input file\n",2);
	}
	if (FALSE ===($content = file_get_contents($input_file_name))){
	    fileError("fail- input file\n",2);
	}
}else {	$content = file_get_contents($input_file_name);}

//load format file
if($format_set == FALSE ) {
    noFormatOutput($output_file,$content,$br);
}else if (!is_readable($format_file_name)){
	 noFormatOutput($output_file,$content,$br);
}else if (filesize($format_file_name) == 0){
	noFormatOutput($output_file,$content,$br);
}

$format_file= fopen($format_file_name, 'r');

//array of html tags
$array_of_tags = array();

//proces format file 
while (($line = fgets($format_file)) !== false) {
      // var_dump($line);
      //if line is not empty create regular expression 
       if($line[0] !== "\n") createNewFormatExpression($line,$array_of_tags,$content); 
       //fwrite(STDOUT, "xxxxxx\n");
    }

//create final file
$output="";
$slen=strlen($content);
for ($i = 0; $i < $slen; $i++) {
	if (array_key_exists($i, $array_of_tags)) {
		$output=$output.$array_of_tags[$i];
	}
    if (($br) and ($content[$i]=="\n")){
        $output=$output."<br />\n";
    }else $output=$output.$content[$i];
}

fwrite($output_file, $output);
//control if last tag was not after end of the input
if (array_key_exists($i, $array_of_tags)) fwrite($output_file, $array_of_tags[$i]); 
if ($GLOBALS['format_set']==TRUE){
    if ($GLOBALS['format_file']) fclose($GLOBALS['format_file']);
}    
if ($GLOBALS['output_set']==TRUE){
    if ($GLOBALS['output_file']) fclose($GLOBALS['output_file']);
}
exit(0);