<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Film extends Model
{
	protected $table = 'film';

	protected $fillable = [
	'name',
	'year',
	'genre',
	'minute',
	'age',
	'director',
	'description'
    ];

    public function projection()
    {
        return $this->hasMany('App\Projection');
    }

}
