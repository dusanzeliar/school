<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Hall extends Model
{
    protected $table = 'hall';

	protected $fillable = [
	'number',
	'kino_id',
     ];

    public function kino() {
    	return $this->belongsTo ('App\Kino')
    }
    public function seat()
    {
        return $this->hasMany('App\Seat');
    }

    public function projection()
    {
        return $this->hasMany('App\Projection');
    }
}
