<?php
class Mail
{
    public  $body;
    public static $mime="";

    public function getMessage()
    {
    	return "errmsg";
    }

	public function factory ($string,$array)
	{
		$mail_object=new Mail;
		$mail_object->body=$array;
		return $mail_object; 
	}

	public function send ($to, $headers, $body)
	{

		if (array_key_exists('MIME-Version', $headers)) {
			self::$mime=$headers['MIME-Version'];
		}
		return new Mail;
	}
}

class PEAR
{

	public static $error=false;

	public function isError ($mail)
	{
		$mail_object=new Mail;
		return self::$error;
	}
}


?>
