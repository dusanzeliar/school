<?php

use Illuminate\Database\Schema\Blueprint;
use Illuminate\Database\Migrations\Migration;

class Kino extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::create('kino', function (Blueprint $table) {
            $table->increments('id');
            $table->string('name');
            $table->string('town');
            $table->string('street');
            $table->timestamps();
        });

        $id = DB::table('kino')->insert([
            ['name' => 'Aupark', 'town' => 'Bratislava 5', 'street' => 'Einsteinova 20'],
            ['name' => 'Eurovea', 'town' => 'Bratislava 1', 'street' => 'Pribinova 8']
        ]);
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
         Schema::drop('kino');
    }
}
