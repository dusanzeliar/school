<?php

use Illuminate\Database\Schema\Blueprint;
use Illuminate\Database\Migrations\Migration;

class Film extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::create('film', function (Blueprint $table) {
            $table->increments('id');
            $table->string('name');
            $table->integer('year');
            $table->string('genre');
            $table->integer('minute');
            $table->string('age');
            $table->string('director');
            $table->longText('description');
            $table->timestamps();
        });
     
        $id = DB::table('film')->insert([
            ['name' => 'Most špiónov', 'year' => 2015, 'genre' => 'Dráma | Thriller', 'minute' => 141 , 'age' => '12' , 'director' => 'Steven Spielberg',
             'description' =>'Svet na oboch stranách železnej opony sa prepadá do šialenej paranoje. Ubehlo už viac ako desať rokov od porážky nacistického Nemecka a ľudstvo ohrozuje studená vojna. Napätie medzi USA a ZSSR je skoro hmatateľné. Keď v roku 1957 FBI zatkne Rudolfa Abela (Mark Rylance), sovietskeho špióna žijúceho v New Yorku, strach a mocenská nedôvera sa ešte viac vystupňujú. Abel sa v skutočnosti volá Viljam Genrichovič Fišer, riadil sieť agentov a do Moskvy dômyselným spôsobom odosielal kódované správy.
Americká vláda osloví Jamesa Donovana (Tom Hanks), uznávaného právnika z Brooklynu, aby sa chytil Abelovej obhajoby. Cez počiatočné obavy jeho aj jeho rodiny sa ho rozhodne zastupovať. Chce zaistiť, aby bol podrobený spravodlivému súdu. Behom príprav na obhajobu sa začne medzi nimi vytvárať puto, ktoré je založené na vzájomnom rešpekte. Pred súdom prednesie vášnivú obhajobu a tak ho ochráni pred trestom smrti.
O tri roky neskôr je nad sovietskym vzdušným priestorom zostrelené americké prieskumné lietadlo a jeho pilot Francis Gary Powers (Austin Stowell) je zajatý a odsúdený k desiatim rokom väzenia. CIA sa obáva, že Powers bude krutými výsluchmi a tvrdými väzenskými podmienkami prinútený k odhaleniu prísne tajných informácii. CIA preto osloví Donovana a presvedčí ho, aby sa stal členom záchrannej misie. Donovan sa vydá do Berlína, kde má za úlohu vyjednať výmenu Abela a Powersa. Po svojom príchode sa dozvie aj o americkom študentovi, ktorý bol zatknutý vo východnom Berlíne. Aj napriek pokynom CIA sústrediť sa iba na zostreleného pilota, Donovan sa rozhodne vyjednávať prepustenie oboch- pilota aj študenta, pretože odmieta kohokoľvek v tejto zemi opustiť. Veľká hra začína...' 
            ],
            ['name' => 'Malý princ', 'year' => 2015, 'genre' => 'Animovaný', 'minute' => 108 , 'age' => 'MP' , 'director' => 'Mark Osborne',
             'description' => 'V centre príbehu je dievčatko, ktoré už od detstva vychováva a pripravuje na seriózny a dospelý svet jej ambiciózna mama. Jej každodenné úsilie bez povolenia naruší excentrický a dobrosrdečný sused, letec. Ten predstaví svojej novej malej priateľke doteraz nepoznaný svet, v ktorom nie je nič nemožné.

Malá dievčatko, ktoré doteraz poznalo iba prísny každodenný režim a nepoznalo spontánnosť a priateľstvo sa vydáva so svojim sprievodcom na magickú cestu do fantázie, do vesmíru za Malým princom. Tu nachádza svoje stratené detstvo a zisťuje, že priateľstvo je vzťah na ktorom v živote veľmi záleží, je pre človeka veľmi dôležité a rozpoznať ho je možné iba srdcom.'
            ],
            ['name' => 'Spectre', 'year' => 2015, 'genre' => 'Akčný | Thriller', 'minute' => 150 , 'age' => '15' , 'director' => 'Sam Mendes',
             'description' => 'James Bond dostane záhadný odkaz z minulosti, ktorý ho privedie na stopu neslávne známej zločineckej organizácii. Postupne rozplieta zložitú pavučinu klamstiev, aby napokon odhalil desivú pravdu o SPECTRE.'
            ]
        ]);

    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
         Schema::drop('film');
    }
}
