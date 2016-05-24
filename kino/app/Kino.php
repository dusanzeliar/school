<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Kino extends Model
{
    protected $table = 'kino';

	protected $fillable = [
	'name',
	'town',
	'street'
    ];

    public function hall()
    {
        return $this->hasMany('App\Hall');
    }
}
