<?php

use Illuminate\Database\Schema\Blueprint;
use Illuminate\Database\Migrations\Migration;

class Projection extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::create('projection', function (Blueprint $table) {
            $table->increments('id');
            $table->timestamp('start');
            $table->integer('hall_id')->unsigned();
            $table->foreign('hall_id')->references('id')->on('hall')->onDelete('cascade');
            $table->integer('film_id')->unsigned();
            $table->foreign('film_id')->references('id')->on('film')->onDelete('cascade');
        });


        $id = DB::table('projection')->insert([
            ['start' => '2015-12-5 18:10:00', 'hall_id'=> 1  , 'film_id'=>1],
            ['start' => '2015-12-5 21:30:00', 'hall_id'=> 1  , 'film_id'=>1],
            ['start' => '2015-12-6 18:40:00', 'hall_id'=> 1  , 'film_id'=>1],
            ['start' => '2015-12-6 22:00:00', 'hall_id'=> 1  , 'film_id'=>1],
            ['start' => '2015-12-10 18:10:00', 'hall_id'=> 1  , 'film_id'=>1],
            ['start' => '2015-12-5 12:10:00', 'hall_id'=> 2  , 'film_id'=>2],
            ['start' => '2015-12-6 12:10:00', 'hall_id'=> 2  , 'film_id'=>2],
            ['start' => '2015-12-6 15:00:00', 'hall_id'=> 2  , 'film_id'=>2],
            ['start' => '2015-12-5 19:10:00', 'hall_id'=> 3  , 'film_id'=>3],
            ['start' => '2015-12-6 18:40:00', 'hall_id'=> 3  , 'film_id'=>3],
            ['start' => '2015-12-9 18:40:00', 'hall_id'=> 3  , 'film_id'=>3]


        ]);



    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
         Schema::drop('projection');
    }
}