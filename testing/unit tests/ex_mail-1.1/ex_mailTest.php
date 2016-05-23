<?php

require "ex_mail.php";

class MyMailTest extends PHPUnit_Framework_TestCase
{
    public function testSingleMailSent()
    {
        global $CONFIG, $ERRORMSG;

        $CONFIG['mail_odesilatel'] = 'from@example.com';
        $CONFIG['mail_server'] = 'smtp.example.com';
        $CONFIG['mail_server_name'] = 'smtp.example.com';
        $CONFIG['mail_server_pass'] = 's3cr3dp4ssw0rd';
        $CONFIG['mail_server_port'] = '25';
        $CONFIG['proforma_splatnost'] = '7';

        Db::set_prof_yes();
        
        MyMail::pear_mail("to@example.com", "Subject text", "Nadpis x y", "some body");
        
        $this->assertEquals(Mail_mime::$body, '<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
          <html><body><h1>Nadpis x y</h1><div id="ObsahMailu">some body</div></body></html>');
    }
    /*BCC*
     *Nadpis- xxx xxx xxx / else
     *Database- true/false
     *Headers- set good/set bad/empty
     *to- set good/set bad/empty
     */

    public function testNadpisObjednavka()
    {
        global $CONFIG, $ERRORMSG;

        $CONFIG['mail_odesilatel'] = 'from@example.com';
        $CONFIG['mail_server'] = 'smtp.example.com';
        $CONFIG['mail_server_name'] = 'smtp.example.com';
        $CONFIG['mail_server_pass'] = 's3cr3dp4ssw0rd';
        $CONFIG['mail_server_port'] = '25';
        $CONFIG['proforma_splatnost'] = '7';

        Db::set_prof_yes();
        
        MyMail::pear_mail("to@example.com", "Subject text", "Objednávka č. 10", "some body");
        
        $this->assertEquals(Mail_mime::$body, '<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
          <html><body><h1>Proforma faktura č. 10</h1><div id="ObsahMailu">some body<p>Děkujeme za Vaši objednávku v našem eshopu. Objednávka byla přijata, o jejím potvrzení Vás budeme co nejdříve informovat.</p></div></body></html>');
    }

    public function testNadpisObjednavkaNoSpace()
    {
        global $CONFIG, $ERRORMSG;

        $CONFIG['mail_odesilatel'] = 'from@example.com';
        $CONFIG['mail_server'] = 'smtp.example.com';
        $CONFIG['mail_server_name'] = 'smtp.example.com';
        $CONFIG['mail_server_pass'] = 's3cr3dp4ssw0rd';
        $CONFIG['mail_server_port'] = '25';
        $CONFIG['proforma_splatnost'] = '7';

        Db::set_prof_no();
        
        MyMail::pear_mail("to@example.com", "Subject text", "Objednávka č.10", "some body");
        
        $this->assertEquals(Mail_mime::$body, '<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
          <html><body><h1>Objednávka č. 10</h1><div id="ObsahMailu">some body<p>Děkujeme za Vaši objednávku v našem eshopu. Objednávka byla přijata, o jejím potvrzení Vás budeme co nejdříve informovat.</p></div></body></html>');
    }

    public function testNadpisEmpty()
    {
        global $CONFIG, $ERRORMSG;

        $CONFIG['mail_odesilatel'] = 'from@example.com';
        $CONFIG['mail_server'] = 'smtp.example.com';
        $CONFIG['mail_server_name'] = 'smtp.example.com';
        $CONFIG['mail_server_pass'] = 's3cr3dp4ssw0rd';
        $CONFIG['mail_server_port'] = '25';
        $CONFIG['proforma_splatnost'] = '7';

        Db::set_prof_no();
        
        MyMail::pear_mail("to@example.com", "Subject text", "", "some body");
        
        $this->assertEquals(Mail_mime::$body, '<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
          <html><body><h1></h1><div id="ObsahMailu">some body</div></body></html>');
    }

    public function testDbNoMatch()
    {
        global $CONFIG, $ERRORMSG;

        $CONFIG['mail_odesilatel'] = 'from@example.com';
        $CONFIG['mail_server'] = 'smtp.example.com';
        $CONFIG['mail_server_name'] = 'smtp.example.com';
        $CONFIG['mail_server_pass'] = 's3cr3dp4ssw0rd';
        $CONFIG['mail_server_port'] = '25';
        $CONFIG['proforma_splatnost'] = '7';

        Db::set_prof_no();
        
        MyMail::pear_mail("to@example.com", "Subject text", "Nadpis: produkt 125", "some body");
        
        $this->assertEquals(Mail_mime::$body, '<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
          <html><body><h1>Nadpis: produkt 125</h1><div id="ObsahMailu">some body</div></body></html>');
    }

    public function testHeadersHostPort()
    {
        global $CONFIG, $ERRORMSG;

        $CONFIG['mail_odesilatel'] = 'from@example.com';
        $CONFIG['mail_server'] = 'smtp.example.com';
        $CONFIG['mail_server_name'] = 'smtp.example.com';
        $CONFIG['mail_server_pass'] = 's3cr3dp4ssw0rd';
        $CONFIG['mail_server_port'] = '-1';
        $CONFIG['proforma_splatnost'] = '7';

        Db::set_prof_yes();
        PEAR::$error=true;
        
        $this->assertEquals( MyMail::pear_mail("to@example.com", "Subject text", "Nadpis: produkt 125 ", "Objednávka č. 2 some body"), false);
    }

    public function testHeadersAuthentication()
    {
        global $CONFIG, $ERRORMSG;

        $CONFIG['mail_odesilatel'] = 'from@example.com';
        $CONFIG['mail_server'] = 'smtp.example.com';
        $CONFIG['mail_server_name'] = '';
        $CONFIG['mail_server_pass'] = 's3cr3dp4ssw0rd';
        $CONFIG['mail_server_port'] = '25';
        $CONFIG['proforma_splatnost'] = '7';

        Db::set_prof_yes();
        PEAR::$error=true;
        
        $this->assertEquals( MyMail::pear_mail("to@example.com", "Subject text", "Nadpis: produkt 125 ", "Objednávka č. 2 some body"), false);
    }

    public function testHeadersSender()
    {
        global $CONFIG, $ERRORMSG;

        $CONFIG['mail_odesilatel'] = 'from@example..com';
        $CONFIG['mail_server'] = 'smtp.example.com';
        $CONFIG['mail_server_name'] = 'smtp.example.com';
        $CONFIG['mail_server_pass'] = 's3cr3dp4ssw0rd';
        $CONFIG['mail_server_port'] = '25';
        $CONFIG['proforma_splatnost'] = '7';

        Db::set_prof_yes();
        PEAR::$error=true;
        
        $this->assertEquals( MyMail::pear_mail("to@example.com", "Subject text", "Nadpis: produkt 125 ", "Objednávka č. 2 some body"), false);
    }

    public function testHeadersSenderEmpty()
    {
        global $CONFIG, $ERRORMSG;

        $CONFIG['mail_odesilatel'] = '';
        $CONFIG['mail_server'] = 'smtp.example.com';
        $CONFIG['mail_server_name'] = 'smtp.example.com';
        $CONFIG['mail_server_pass'] = 's3cr3dp4ssw0rd';
        $CONFIG['mail_server_port'] = '25';
        $CONFIG['proforma_splatnost'] = '7';

        Db::set_prof_yes();
        PEAR::$error=true;
        
        $this->assertEquals( MyMail::pear_mail("to@example.com", "Subject text", "Nadpis: produkt 125 ", "Objednávka č. 2 some body"), false);
    }

    public function testTo()
    {
        global $CONFIG, $ERRORMSG;

        $CONFIG['mail_odesilatel'] = 'from@example.com';
        $CONFIG['mail_server'] = 'smtp.example.com';
        $CONFIG['mail_server_name'] = 'smtp.example.com';
        $CONFIG['mail_server_pass'] = 's3cr3dp4ssw0rd';
        $CONFIG['mail_server_port'] = '25';
        $CONFIG['proforma_splatnost'] = '7';

        Db::set_prof_yes();
        PEAR::$error=true;
        
        
        $this->assertEquals( MyMail::pear_mail("toexample..com", "Subject text", "Nadpis: produkt 125 ", "Objednávka č. 2 some body"), false);
    }

    public function testToEmpty()
    {
        global $CONFIG, $ERRORMSG;

        $CONFIG['mail_odesilatel'] = 'from@example.com';
        $CONFIG['mail_server'] = 'smtp.example.com';
        $CONFIG['mail_server_name'] = 'smtp.example.com';
        $CONFIG['mail_server_pass'] = 's3cr3dp4ssw0rd';
        $CONFIG['mail_server_port'] = '25';
        $CONFIG['proforma_splatnost'] = '7';

        Db::set_prof_yes();
        PEAR::$error=true;
        
        
        $this->assertEquals( MyMail::pear_mail("", "Subject text", "Nadpis: produkt 125 ", "Objednávka č. 2 some body"), false);
    }

    public function testFrom()
    {
        global $CONFIG, $ERRORMSG;

        $CONFIG['mail_odesilatel'] = 'from@example.com';
        $CONFIG['mail_server'] = 'smtp.example.com';
        $CONFIG['mail_server_name'] = 'smtp.example.com';
        $CONFIG['mail_server_pass'] = 's3cr3dp4ssw0rd';
        $CONFIG['mail_server_port'] = '25';
        $CONFIG['proforma_splatnost'] = '7';

        Db::set_prof_yes();
        PEAR::$error=true;
        
        $this->assertEquals( MyMail::pear_mail("to@example.com", "Subject text", "Nadpis: produkt 125 ", "Objednávka č. 2 some body",1,"from@example..com"), false);
    }

    public function testHtmlZero()
    {
        global $CONFIG, $ERRORMSG;

        $CONFIG['mail_odesilatel'] = 'from@example.com';
        $CONFIG['mail_server'] = 'smtp.example.com';
        $CONFIG['mail_server_name'] = 'smtp.example.com';
        $CONFIG['mail_server_pass'] = 's3cr3dp4ssw0rd';
        $CONFIG['mail_server_port'] = '25';
        $CONFIG['proforma_splatnost'] = '7';

        Db::set_prof_yes();
        Mail::$mime="";
        
        MyMail::pear_mail("to@example.com", "Subject text", "Nadpis x y", "some body",0);
        
        $this->assertEquals(Mail::$mime,"");
    }





}
?>

