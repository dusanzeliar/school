<?php
class Mail_mime
{
	public static $body;
	
	public function setHTMLBody ($new_body)
	{
		self::$body = $new_body;
	}

	public function get ()
	{
		return self::$body;
	}

	public function headers ($headers)
	{
		return $headers;
	}

}

?>
