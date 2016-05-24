<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Projection extends Model
{
    protected $table = 'projection';

	protected $fillable = [
	'start',
    'price',
	'hall_id',
	'film_id',
     ];

    public function hall() {
    	return $this->belongsTo ('App\Hall')
    }

    public function film() {
    	return $this->belongsTo ('App\Film')
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
