<?php

use Illuminate\Database\Schema\Blueprint;
use Illuminate\Database\Migrations\Migration;

class TicketType extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::create('ticket_type', function (Blueprint $table) {
            $table->increments('id');
            $table->float('discount');
            $table->string('type');
        });

        $id = DB::table('ticket_type')->insert([
            ['type' =>'dospelý', 'discount' => 1],
            ['type' =>'študent', 'discount' => 0.8],
            ['type' =>'senior', 'discount' => 0.7],
            ['type' =>'detský', 'discount' => 0.8]
        ]);
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
         Schema::drop('ticket_type');
    }
}
