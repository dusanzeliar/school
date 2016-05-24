<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Reservation extends Model
{
    protected $table = 'reservation';

	protected $fillable = [
	'discount',
	'users_id',
	'seat_id',
	'projection_id',
     ];

    public function seat() {
    	return $this->belongsTo ('App\Seat')
    }

    public function projection() {
    	return $this->belongsTo ('App\Projection')
    }

    public function users() {
    	return $this->belongsTo ('App\User')
    }
}
