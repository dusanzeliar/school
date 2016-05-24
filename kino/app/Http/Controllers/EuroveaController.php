<?php

namespace App\Http\Controllers;

use App\Film;
use App\Http\Requests;
use App\Http\Controllers\Controller;
use Request;
use DateTime;


class EuroveaController extends Controller
{
    /**
     * Show a list of all available flights.
     *
     * @return Response
     */
    public function index()
    {
        //$halls= \DB::table('hall')->where('kino_id', '1')->get();
        $kino='Eurovea';
        $url='eurovea';
        //$halls= \DB::table('hall')->where('kino_id', '1')->get();
        $time = new DateTime();
        $time->setTime(00, 00, 00);

        //$time_end = date('Y-m-d', strtotime($time) + 86400);
        $time_end =clone $time;
        $time_end->modify('+1 day');

        //return $time->format('Y-m-d H:i:s');

        $projections = \DB::table('projection')
            ->join('film', 'film.id', '=', 'projection.film_id')
            ->join('hall', 'hall.id', '=', 'projection.hall_id')
            ->where('hall.kino_id', '=', 2)
            ->where('projection.start', '>', $time)
            ->where('projection.start', '<', $time_end)
            ->select('film.name AS name', 'projection.start AS start', 'hall.number AS hall' , 'projection.price AS price' , 'projection.id AS p_id')
            ->get();

        //return $projections;

        return view('program', compact('time', 'projections', 'kino' , 'url' ));
        //return view('filmy', ['film_db' => $film_db]);
        //return view('filmy');
    }

    public function date()
    {
        $kino='Eurovea';
        $url='eurovea';

        //$input = Request::all();
        $time = new DateTime(Request::get('date'));
        //$time = date('Y-m-d', strtotime($time));
        //return $time->format('Y-m-d');
        $time->setTime(00, 00, 00);

        //$time_end = date('Y-m-d', strtotime($time) + 86400);
        $time_end =clone $time;
        $time_end->modify('+1 day');
        //return $time_end->format('Y-m-d');

        //return $time->format('Y-m-d H:i:s');

        $projections = \DB::table('projection')
            ->join('film', 'film.id', '=', 'projection.film_id')
            ->join('hall', 'hall.id', '=', 'projection.hall_id')
            ->where('hall.kino_id', '=', 2)
            ->where('projection.start', '>', $time)
            ->where('projection.start', '<', $time_end)
            ->select('film.name AS name', 'projection.start AS start', 'hall.number AS hall' , 'projection.price AS price' , 'projection.id AS p_id')
            ->get();

        //return $projections;
        return view('program', compact('time', 'projections', 'kino' , 'url' ));
        //return view('filmy', ['film_db' => $film_db]);
        //return view('filmy');
    }
}
