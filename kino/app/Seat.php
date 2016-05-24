<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Seat extends Model
{
    protected $table = 'seat';

	protected $fillable = [
	'number',
	'hall_id',
     ];

    public function hall() {
    	return $this->belongsTo ('App\Hall')
    }

    public function reservation()
    {
        return $this->hasMany('App\Reservation');
    }

    public function ticket()
    {
        return $this->hasMany('App\Ticket');
    }
}
