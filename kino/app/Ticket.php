<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Ticket extends Model
{
    protected $table = 'ticket';

	protected $fillable = [
	'discount',
	'seat_id',
	'projection_id',
     ];

    public function seat() {
    	return $this->belongsTo ('App\Seat')
    }

    public function projection() {
    	return $this->belongsTo ('App\Projection')
    }

}
