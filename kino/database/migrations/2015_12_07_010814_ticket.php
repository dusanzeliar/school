<?php

use Illuminate\Database\Schema\Blueprint;
use Illuminate\Database\Migrations\Migration;

class Ticket extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::create('ticket', function (Blueprint $table) {
            $table->increments('id');
            $table->float('price');
            $table->integer('seat_id')->unsigned();
            $table->foreign('seat_id')->references('id')->on('seat')->onDelete('cascade');
            $table->integer('projection_id')->unsigned();
            $table->foreign('projection_id')->references('id')->on('projection')->onDelete('cascade');
        });

        $id = DB::table('ticket')->insert([
            ['price' => '10', 'seat_id' => 11, 'projection_id' => 1 ],
            ['price' => '10', 'seat_id' => 12, 'projection_id' => 1 ],
            ['price' => '10', 'seat_id' => 13, 'projection_id' => 1 ]
        ]);


    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
         Schema::drop('ticket');
    }
}
