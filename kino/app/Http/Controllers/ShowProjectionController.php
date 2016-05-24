<?php

namespace App\Http\Controllers;

use Auth;
use App\Users;
use App\Http\Requests;
use App\Http\Controllers\Controller;
use Request;

class ShowProjectionController extends Controller
{
    /**
     * Display a listing of the resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function show()
    {
        $p_id=Request::get('p_id');
        $reservation_type=Request::get('type');
        //return $price;
        //return $reservation_type;
        $get_discount=\DB::table('ticket_type')
            ->where('ticket_type.type', '=', $reservation_type )
            ->select( 'ticket_type.discount AS discount') 
            ->get();
        
        foreach ($get_discount as $d){
            $discount=$d->discount;
        }

        $my_id= Auth::user()->getId();
        //return $my_id;
        $seats = \DB::table('projection')
            ->join('hall', 'hall.id', '=', 'projection.hall_id')
            ->join('seat', 'seat.hall_id', '=', 'hall.id')
            ->where('projection.id', '=', $p_id )
            ->select( 'seat.number AS seat' , 'seat.id AS seat_id')                     
            ->orderBy('seat.number', 'desc')
            ->get();

        $projection = \DB::table('projection')
            ->join('film', 'film.id', '=', 'projection.film_id')
            ->join('hall', 'hall.id', '=', 'projection.hall_id')
            ->join('kino', 'kino.id', '=', 'hall.kino_id')
            ->where('projection.id', '=', $p_id )
            ->select('kino.name AS kino', 'film.name AS name', 'projection.start AS start', 'hall.number AS hall' , 'projection.price AS price' , 'projection.id AS p_id')
            ->get();


        $reserved_seats = \DB::table('reservation')
            ->where('reservation.projection_id', '=', $p_id )
            ->select('reservation.seat_id AS seat')
             ->get();

        $my_seats = \DB::table('reservation')
            ->where('reservation.projection_id', '=', $p_id )
            ->where('reservation.users_id', '=', $my_id )
            ->select('reservation.seat_id AS seat', 'reservation.id AS r_id')
            ->get();

        $tickets = \DB::table('ticket')
            ->where('ticket.projection_id', '=', $p_id )
            ->select('ticket.seat_id AS seat')
            ->get();
 

        return view('show_projection', compact('projection', 'seats', 'reservations', 'my_id' , 'p_id' , 'reserved_seats', 'my_seats', 'reservation_type' , 'discount', 'tickets'));




    }

}
