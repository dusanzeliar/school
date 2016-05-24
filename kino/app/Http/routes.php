<?php

/*
|--------------------------------------------------------------------------
| Application Routes
|--------------------------------------------------------------------------
|
| Here is where you can register all of the routes for an application.
| It's a breeze. Simply tell Laravel the URIs it should respond to
| and give it the controller to call when that URI is requested.
|
*/

Route::get('/', function () {
    return view('welcome');
});

//Entrust::routeNeedsPermission('filmy*', 'user');
Route::get('filmy', 'FilmController@index');

Entrust::routeNeedsRole('reserve*', array('user'));
Route::get('reserve', 'ReserveController@index');
Route::post('reserve', 'ReserveController@storno');

Entrust::routeNeedsRole('showprojection*', array('user'));
Route::post('showprojection', 'ShowProjectionController@show');

Entrust::routeNeedsRole('buyprojection*', array('salesman'));
Route::post('buyprojection', 'BuyProjectionController@show');

Entrust::routeNeedsRole('p_buy*', array('salesman'));
Route::post('p_buy', 'BuyTicketController@buy_ticket');
Route::post('p_buy_res', 'BuyTicketController@buy_reservation');
Route::post('p_del_res', 'BuyTicketController@storno');
//Route::post('buyreservation', 'ReservationOperationController@reserve');

Entrust::routeNeedsRole('reservation*', array('user'));
Entrust::routeNeedsRole('stornoreservation*', array('user'));
Route::post('reservation', 'ReservationOperationController@reserve');
Route::post('stornoreservation', 'ReservationOperationController@storno');

Route::get('aupark', 'AuparkController@index');
Route::post('aupark', 'AuparkController@date');

Route::get('eurovea', 'EuroveaController@index');
Route::post('eurovea', 'EuroveaController@date');

Entrust::routeNeedsRole('aupark_p*', 'salesman');
//Entrust::routeNeedsRole('aupark_p*', array('salesman'));
Route::get('aupark_p', 'Aupark_pController@index');
Route::post('aupark_p', 'Aupark_pController@date');

Entrust::routeNeedsRole('eurovea_p*', array('salesman'));
Route::get('eurovea_p', 'Eurovea_pController@index');
Route::post('eurovea_p', 'Eurovea_pController@date');

Entrust::routeNeedsRole('add_salesman*', array('boss'));
Route::get('add_salesman', 'BossController@add_salesman');
Route::post('add_salesman', 'BossController@create_salesman');

Entrust::routeNeedsRole('show_sales*', array('boss'));
Route::get('show_sales', 'ShowSalesController@show_sales');
Route::post('show_sales_data', 'ShowSalesController@show_sales_data');

