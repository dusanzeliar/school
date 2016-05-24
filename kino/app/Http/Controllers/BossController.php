<?php

namespace App\Http\Controllers;

use Auth;
use App\Users;
use App\Http\Requests;
use App\Http\Controllers\Controller;
use Request;

class BossController extends Controller
{
    /**
     * Display a listing of the resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function add_salesman()
    {
        $msg='';
        return view('add_salesman', compact('msg'));
    }

    public function create_salesman()
    {
        $email=Request::get('email');
        if (empty($email)) {
            $msg='Prosim zadajte email';
            return view('add_salesman', compact('msg'));
        }

        $user_data = \DB::table('users')
            ->where('users.email', '=', $email )
            ->select('users.id AS u_id', 'users.name AS name')
            ->get();

        if (empty($user_data)) {
            $msg='Uživateľ s daným emailom neexistuje';
            return view('add_salesman', compact('msg'));
        }

        foreach ($user_data as $d){
            $u_id=$d->u_id;
            $msg=$email."   ".$d->name." bol pridaný medzi pokladníkov"; 
        }
        //return $u_id;

        $user_role = \DB::table('role_user')->where('user_id', '=', $u_id)->update(array('role_id' => 1));

        return view('add_salesman', compact('msg'));
    }

}
