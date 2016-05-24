<?php

namespace App\Http\Controllers;

use App\Film;
use App\Http\Controllers\Controller;
use Zizaco\Entrust\Traits\EntrustUserTrait;

class FilmController extends Controller
{
    /**
     * Show a list of all available flights.
     *
     * @return Response
     */
    public function index()
    {
        $film_db = Film::get();
        
        //$film_db='a';
        return view('list_film')->with('film_db', $film_db);
        //return view('filmy', ['film_db' => $film_db]);
        //return view('filmy');
    }
}
