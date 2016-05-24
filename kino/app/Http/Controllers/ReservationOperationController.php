<?php

namespace App\Http\Controllers;

use Auth;
use App\Users;
use App\Http\Requests;
use App\Http\Controllers\Controller;
use Request;

class ReservationOperationController extends Controller
{
    /**
     * Display a listing of the resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function reserve()
    {

        $p_id=Request::get('p_id');
        $s_id=Request::get('s_id');
        $reservation_type=Request::get('type');

        $get_discount=\DB::table('ticket_type')
            ->where('ticket_type.type', '=', $reservation_type )
            ->select( 'ticket_type.discount AS discount') 
            ->get();
        
        foreach ($get_discount as $d){
            $discount=$d->discount;
        }

        $tmp_p = \DB::table('projection')
            ->where('projection.id', '=', $p_id )
            ->select('projection.price AS price')
            ->get();

        foreach ($tmp_p as $p){
            $price=$p->price * $discount;
        }

        $my_id= Auth::user()->getId();


        \DB::table('reservation')->insert([
            ['price' => $price, 'users_id'=> $my_id , 'seat_id' => $s_id, 'projection_id' => $p_id ]
        ]);

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

    public function storno()
    {

        $p_id=Request::get('p_id');
        $r_id=Request::get('r_id');
        $s_id=Request::get('s_id');

        $reservation_type=Request::get('type');

        $get_discount=\DB::table('ticket_type')
            ->where('ticket_type.type', '=', $reservation_type )
            ->select( 'ticket_type.discount AS discount') 
            ->get();
        
        foreach ($get_discount as $d){
            $discount=$d->discount;
        }

        $my_id= Auth::user()->getId();


        \DB::table('reservation')
            ->where('id', '=', $r_id)
            ->where('seat_id', '=', $s_id)
            ->delete();


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