<?php

use Illuminate\Database\Schema\Blueprint;
use Illuminate\Database\Migrations\Migration;

class Hall extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::create('hall', function (Blueprint $table) {
            $table->increments('id');
            $table->string('number');
            $table->integer('kino_id')->unsigned();
            $table->foreign('kino_id')->references('id')->on('kino')->onDelete('cascade');
        });

        $id = DB::table('hall')->insert([
            ['number' => '1', 'kino_id'=> 1 ],
            ['number' => '2', 'kino_id'=> 1 ],
            ['number' => '3', 'kino_id'=> 1 ],
            ['number' => '4', 'kino_id'=> 1 ],
            ['number' => '1', 'kino_id'=> 2 ],
            ['number' => '2', 'kino_id'=> 2 ],
            ['number' => '3', 'kino_id'=> 2 ],
            ['number' => '4', 'kino_id'=> 2 ]
        ]);

    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
         Schema::drop('hall');
    }
}
