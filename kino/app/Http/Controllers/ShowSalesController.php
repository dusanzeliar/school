<?php

namespace App\Http\Controllers;

use Auth;
use App\Users;
use App\Http\Requests;
use App\Http\Controllers\Controller;
use Request;
use DateTime;


class ShowSalesController extends Controller
{
    /**
     * Show a list of all available flights.
     *
     * @return Response
     */
    public function show_sales()
    {
        $msg='';
        $kino='--';
        $film='--';
        return view('show_sales', compact('msg','kino','film'));
    }

    public function show_sales_data()
    {
        $kino=Request::get('kino');
        $film=Request::get('film');
        $arg_stop=Request::get('stop');
        $arg_start=Request::get('start');




        if  ( ((empty($arg_start)) and (!empty($arg_stop)) )  or ( (!(empty($arg_start)) and (empty($arg_stop))) ) ){
            $msg='Prosim zadajte aj druhý časový údaj alebo ich oba nechajte nevyplnené';
            $kino='--';
            $film='--';
            return view('show_sales', compact('msg','kino','film'));
        }

        $start = new DateTime(Request::get('start'));
        $start->setTime(00, 00, 00);
        $stop = new DateTime(Request::get('stop'));
        $stop->setTime(23, 59, 59);

        if (empty($arg_start)) {
            if ($kino == '--'){
                //film set
                if ($film == '--'){
                    $tickets = \DB::table('ticket')
                    ->join('projection', 'projection.id', '=', 'ticket.projection_id')
                    ->join('hall', 'hall.id', '=', 'projection.hall_id')
                    ->join('kino', 'kino.id', '=', 'hall.kino_id')
                    ->join('film', 'film.id', '=', 'projection.film_id')
                    ->select('ticket.price AS price')
                    ->get();
                }else{
                    $tickets = \DB::table('ticket')
                    ->join('projection', 'projection.id', '=', 'ticket.projection_id')
                    ->join('hall', 'hall.id', '=', 'projection.hall_id')
                    ->join('kino', 'kino.id', '=', 'hall.kino_id')
                    ->join('film', 'film.id', '=', 'projection.film_id')
                    ->where('film.name', '=', $film)
                    ->select('ticket.price AS price')
                    ->get();
                }
            }
            //kino set
            else{
                //film set
                if ($film == '--'){
                    $tickets = \DB::table('ticket')
                    ->join('projection', 'projection.id', '=', 'ticket.projection_id')
                    ->join('hall', 'hall.id', '=', 'projection.hall_id')
                    ->join('kino', 'kino.id', '=', 'hall.kino_id')
                    ->join('film', 'film.id', '=', 'projection.film_id')
                    ->where('kino.name', '=', $kino)
                    ->select('ticket.price AS price')
                    ->get();
                }else{
                    $tickets = \DB::table('ticket')
                    ->join('projection', 'projection.id', '=', 'ticket.projection_id')
                    ->join('hall', 'hall.id', '=', 'projection.hall_id')
                    ->join('kino', 'kino.id', '=', 'hall.kino_id')
                    ->join('film', 'film.id', '=', 'projection.film_id')
                    ->where('film.name', '=', $film)
                    ->where('kino.name', '=', $kino)
                    ->select('ticket.price AS price')
                    ->get();
                }
            }
        }
        //Time set
        else {
            if ($kino == '--'){
                //film set
                if ($film == '--'){
                    $tickets = \DB::table('ticket')
                    ->join('projection', 'projection.id', '=', 'ticket.projection_id')
                    ->join('hall', 'hall.id', '=', 'projection.hall_id')
                    ->join('kino', 'kino.id', '=', 'hall.kino_id')
                    ->join('film', 'film.id', '=', 'projection.film_id')
                    ->where('projection.start', '>=', $start)
                    ->where('projection.start', '<=', $stop)
                    ->select('ticket.price AS price')
                    ->get();
                }else{
                    $tickets = \DB::table('ticket')
                    ->join('projection', 'projection.id', '=', 'ticket.projection_id')
                    ->join('hall', 'hall.id', '=', 'projection.hall_id')
                    ->join('kino', 'kino.id', '=', 'hall.kino_id')
                    ->join('film', 'film.id', '=', 'projection.film_id')
                    ->where('film.name', '=', $film)
                    ->where('projection.start', '>=', $start)
                    ->where('projection.start', '<=', $stop)
                    ->select('ticket.price AS price')
                    ->get();
                }
            }
            //kino set
            else{
                //film set
                if ($film == '--'){
                    $tickets = \DB::table('ticket')
                    ->join('projection', 'projection.id', '=', 'ticket.projection_id')
                    ->join('hall', 'hall.id', '=', 'projection.hall_id')
                    ->join('kino', 'kino.id', '=', 'hall.kino_id')
                    ->join('film', 'film.id', '=', 'projection.film_id')
                    ->where('kino.name', '=', $kino)
                    ->where('projection.start', '>=', $start)
                    ->where('projection.start', '<=', $stop)
                    ->select('ticket.price AS price')
                    ->get();
                }else{
                    $tickets = \DB::table('ticket')
                    ->join('projection', 'projection.id', '=', 'ticket.projection_id')
                    ->join('hall', 'hall.id', '=', 'projection.hall_id')
                    ->join('kino', 'kino.id', '=', 'hall.kino_id')
                    ->join('film', 'film.id', '=', 'projection.film_id')
                    ->where('film.name', '=', $film)
                    ->where('kino.name', '=', $kino)
                    ->where('projection.start', '>=', $start)
                    ->where('projection.start', '<=', $stop)
                    ->select('ticket.price AS price')
                    ->get();
                }
            }
        }

        $price=0;
        foreach ($tickets as $ticket){
            $price= $price +$ticket->price;
        }
        
        $msg="Tržba: ".$price." €";

        return view('show_sales', compact('msg','kino','film'));
    }
}
