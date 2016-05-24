<?php

namespace App\Http\Controllers;

use Auth;
use App\Users;
use App\Http\Requests;
use App\Http\Controllers\Controller;
use Request;


class ReserveController extends Controller
{
    /**
     * Show a list of all available flights.
     *
     * @return Response
     */
    public function index()
    {
        $my_id= Auth::user()->getId();
        //return $my_id;
        $myreservations = \DB::table('reservation')
            ->join('seat', 'seat.id', '=', 'reservation.seat_id')
            ->join('projection', 'projection.id', '=', 'reservation.projection_id')
            ->join('film', 'film.id', '=', 'projection.film_id')
            ->join('hall', 'hall.id', '=', 'projection.hall_id')
            ->join('kino', 'kino.id', '=', 'hall.kino_id')
            ->where('reservation.users_id', '=', $my_id )
            ->select('projection.start AS start', 'film.name AS film', 'kino.name AS kino', 'hall.number AS hall' , 'seat.number AS seat' ,
                      'reservation.price AS price', 'reservation.id AS reservation' , 'projection.id AS projection' , 'reservation.users_id AS user_id')
            ->orderBy('projection.start', 'asc','projection.id')
            ->get();
        //return $myreservations;
        return view('reserve', compact('myreservations'));
        
        

    }

    public function storno()
    {
        $u_id=Request::get('u_id');
        $p_id=Request::get('p_id');

        \DB::table('reservation')
            ->where('users_id', '=', $u_id)
            ->where('projection_id', '=', $p_id)
            ->delete();
        return redirect()->action('ReserveController@index');
        //DB::table('users')->where('votes', '<', 100)->delete();



    }
}
