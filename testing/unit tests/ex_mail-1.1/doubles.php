<?php
class Db
{
	public static $match_found=true;

	public function set_prof_yes ()
	{
		self::$match_found=true;
	}
	public function set_prof_no ()
	{
		self::$match_found=false;
	}

	public function DbQuery ($expression)
	{
		$return_array = array();
		//database return 1 if x is searched, else return 0
		if (self::$match_found) {
			$return_array['proforma']=1;
		}
		else $return_array['proforma']=0;
		return $return_array;
	} 
}
?>
