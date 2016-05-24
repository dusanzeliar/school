<?php

use Illuminate\Database\Schema\Blueprint;
use Illuminate\Database\Migrations\Migration;

class Reservation extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::create('reservation', function (Blueprint $table) {
            $table->increments('id');
            $table->float('price');
            $table->integer('users_id')->unsigned();
            $table->foreign('users_id')->references('id')->on('users');
            $table->integer('seat_id')->unsigned();
            $table->foreign('seat_id')->references('id')->on('seat')->onDelete('cascade');
            $table->integer('projection_id')->unsigned();
            $table->foreign('projection_id')->references('id')->on('projection')->onDelete('cascade');
        });

        $id = DB::table('reservation')->insert([
            ['price' => '10', 'users_id'=> 1 , 'seat_id' => 4, 'projection_id' => 1 ],
            ['price' => '10', 'users_id'=> 1 , 'seat_id' => 5, 'projection_id' => 1 ],
            ['price' => '10', 'users_id'=> 1 , 'seat_id' => 6, 'projection_id' => 1 ],
            ['price' => '8' , 'users_id'=> 1 , 'seat_id' => 7, 'projection_id' => 1 ],
            ['price' => '6', 'users_id'=> 1 , 'seat_id' => 40, 'projection_id' => 2 ],
            ['price' => '6', 'users_id'=> 1 , 'seat_id' => 41, 'projection_id' => 2 ],
            ['price' => '6', 'users_id'=> 1 , 'seat_id' => 42, 'projection_id' => 2 ],
            ['price' => '5', 'users_id'=> 1 , 'seat_id' => 43, 'projection_id' => 2 ],
            ['price' => '5', 'users_id'=> 1 , 'seat_id' => 4, 'projection_id' => 3 ],
            ['price' => '6', 'users_id'=> 1 , 'seat_id' => 5, 'projection_id' => 3 ],
            ['price' => '7', 'users_id'=> 1 , 'seat_id' => 76, 'projection_id' => 4 ],
            ['price' => '7', 'users_id'=> 1 , 'seat_id' => 32, 'projection_id' => 4 ],
            ['price' => '7', 'users_id'=> 1 , 'seat_id' => 33, 'projection_id' => 5 ],
        ]);


    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
         Schema::drop('reservation');
    }
}
