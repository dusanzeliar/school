<?php

use Illuminate\Database\Schema\Blueprint;
use Illuminate\Database\Migrations\Migration;

class Seat extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::create('seat', function (Blueprint $table) {
            $table->increments('id');
            $table->integer('number');
            $table->integer('hall_id')->unsigned();
            $table->foreign('hall_id')->references('id')->on('hall')->onDelete('cascade');
        });

        for ($hall = 1; $hall <= 8; $hall++) {
            for ($seat = 1; $seat <= 168; $seat++){
                $id = DB::table('seat')->insert(['number' => $seat, 'hall_id'=> $hall ]);
            }
        }
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
         Schema::drop('seat');
    }
}
