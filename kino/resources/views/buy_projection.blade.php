@extends('app')

@section('htmlheader_title')
    Projekcia
@endsection


@section('main-content')
<!-- Scrip to show description -->


<div class="panel panel-default">
    @foreach($projection as $p)
    <?php $price=$p->price; ?>
    <?php $tmp_p_id=$p->p_id; ?>
    <div class="panel-heading "><font size="6"> {{ $p->kino }} dňa {{DateTime::createFromFormat('Y-m-d H:i:s', $p->start )->format('Y-m-d H:i')}} Film: {{ $p->name }} Sála: {{ $p->hall }} </font></div>
    @endforeach
    <table class="table lesson-list-table table-bordered">
		<tbody>
		<?php $count = 0; ?>
		@foreach($seats as $seat)

		    <?php $seat_reserved = 0; ?>
		    @foreach($reserved_seats as $r_seat)
		        @if ($seat->seat_id == $r_seat->seat)
		            <?php $seat_reserved = 1; ?>
		        @endif
		    @endforeach

            @foreach($tickets as $ticket)
                @if ($seat->seat_id == $ticket->seat)
                    <?php $seat_reserved = 2; ?>
                @endif
            @endforeach

            <?php $count = $count + 1; ?>
		    @if ($count % 14 == 1) 
		        <tr>
		    @endif



		    @if ($seat_reserved != 0) 
                <td width="7%">
                    {!! Form::open(['url' => 'buyprojection']) !!}
                    {!! Form::hidden('type', $reservation_type, ['class' => 'form-control'] )!!}
                    {!! Form::hidden('p_id', $p_id, ['class' => 'form-control'] )!!}
                    {!! Form::submit($seat->seat, ['class' => 'btn btn-danger form-control']) !!}
                    {!! Form::close() !!}
                    </td> 
            @else 
                <td width="7%">
                    {!! Form::open(['url' => 'p_buy']) !!}
                    {!! Form::hidden('type', $reservation_type, ['class' => 'form-control'] )!!}
                    {!! Form::hidden('p_id', $p_id, ['class' => 'form-control'] )!!}
                    {!! Form::hidden('s_id', $seat->seat_id, ['class' => 'form-control'] )!!}
                    {!! Form::submit($seat->seat, ['class' => 'btn btn-info form-control']) !!}
                    {!! Form::close() !!}
                </td>
            @endif        
                       
            @if ($count % 14 == 0) 
		        </tr>
		    @endif
        @endforeach
        </tbody>
    </table>
</div>


<?php $price=$price * $discount; ?>
<h3>Typ lístka: {{$reservation_type}} Cena: {{$price}} €</h3>

{!! Form::open(['url' => 'buyprojection']) !!}
{!! Form::select('type', array('detský' => 'Detský', 'študent' => 'Študent' , 'dospelý' => 'Dospelý', 'senior' => 'Senior'), $reservation_type); !!}
{!! Form::hidden('p_id', $tmp_p_id, ['class' => 'form-control'] )!!}
{!! Form::submit('Zmeň typ lístka', ['class' => 'btn btn-primary']) !!}
{!! Form::close() !!}

@if (!(empty ( $all_r )))
<div class="panel panel-default">
<div class="panel-heading "><font size="6">Rezervácie</font></div>
            <?php $pr_id = -1; ?>
            <?php $tmpsum = 0; ?>
            <?php $seatstring = ""; ?>
            <?php $lastElement = end($all_r); ?>
            <?php $tmp_uid = '';?>
            <?php $tmp_name = ''; ?>
            <?php $tmp_email = ''; ?>
            @foreach($all_r as $res)
                @if ($res->user_id != $pr_id) 
                    @if  ($pr_id != -1 ) 
                        <table class="table lesson-list-table table-bordered">
                        <tbody>
                         <tr>
                        <td width="25%">{{$res->name}}</td>
                        <td width="20%">{{$res->email}}</td> 
                        <td width="25%">Rezervované miesta: {{$seatstring}}</td>
                        <td width="10%">Cena: {{$tmpsum}} €</td>
                        <td width="10%">
                            {!! Form::open(['url' => 'p_buy_res']) !!}
                            {!! Form::hidden('type', $reservation_type, ['class' => 'form-control'] )!!}
                            {!! Form::hidden('u_id', $res->user_id, ['class' => 'form-control'] )!!}
                            {!! Form::hidden('p_id', $res->projection, ['class' => 'form-control'] )!!}
                            {!! Form::submit('Kúpiť', ['class' => 'btn btn-info form-control']) !!}
                            {!! Form::close() !!}
                        </td>
                        <td width="10%">
                            {!! Form::open(['url' => 'p_del_res']) !!}
                            {!! Form::hidden('type', $reservation_type, ['class' => 'form-control'] )!!}
                            {!! Form::hidden('u_id', $res->user_id, ['class' => 'form-control'] )!!}
                            {!! Form::hidden('p_id', $res->projection, ['class' => 'form-control'] )!!}
                            {!! Form::submit('Storno', ['class' => 'btn btn-danger form-control']) !!}
                            {!! Form::close() !!}
                        </td>
                        </tr>
                        </tbody>
                        </table>
                        <?php $tmp_uid = $res->user_id; ?>
                        <?php $tmp_name = $res->name; ?>
                        <?php $tmp_email = $res->email; ?> 
                        <?php $tmpsum = 0; 
                              $seatstring=""?>
                    @endif

                        <?php $pr_id = $res->user_id; ?>
                        <?php $tmpsum = $tmpsum + $res->price; ?>
                        <?php $seatstring= $seatstring.$res->seat." "; ?>
                    @if  ($lastElement == $res)
                        <?php $tmp_uid = $res->user_id; ?>
                        <?php $tmp_name = $res->name; ?>
                        <?php $tmp_email = $res->email; ?>  
                        <table class="table lesson-list-table table-bordered">
                        <tbody>
                         <tr>
                        <td width="25%">{{$res->name}}</td>
                        <td width="20%">{{$res->email}}</td> 
                        <td width="25%">Rezervované miesta: {{$seatstring}}</td>
                        <td width="10%">Cena: {{$tmpsum}} €</td>
                        <td width="10%">
                            {!! Form::open(['url' => 'p_buy_res']) !!}
                            {!! Form::hidden('type', $reservation_type, ['class' => 'form-control'] )!!}
                            {!! Form::hidden('u_id', $res->user_id, ['class' => 'form-control'] )!!}
                            {!! Form::hidden('p_id', $res->projection, ['class' => 'form-control'] )!!}
                            {!! Form::submit('Kúpiť', ['class' => 'btn btn-info form-control']) !!}
                            {!! Form::close() !!}
                        </td>
                        <td width="10%">
                            {!! Form::open(['url' => 'p_del_res']) !!}
                            {!! Form::hidden('type', $reservation_type, ['class' => 'form-control'] )!!}
                            {!! Form::hidden('u_id', $res->user_id, ['class' => 'form-control'] )!!}
                            {!! Form::hidden('p_id', $res->projection, ['class' => 'form-control'] )!!}
                            {!! Form::submit('Storno', ['class' => 'btn btn-danger form-control']) !!}
                            {!! Form::close() !!}
                        </td>
                        </tr>
                        </tbody>
                        </table>
                        <?php $tmpsum = 0; 
                              $seatstring=""?>
                    @endif
                        
                @else
                    <?php $tmpsum = $tmpsum + $res->price; ?>
                    <?php $seatstring= $seatstring.$res->seat." "; ?>
                    @if ($lastElement == $res)
                        <table class="table lesson-list-table table-bordered">
                        <tbody>
                         <tr>
                        <td width="25%">{{$res->name}}</td>
                        <td width="20%">{{$res->email}}</td> 
                        <td width="25%">Rezervované miesta: {{$seatstring}}</td>
                        <td width="10%">Cena: {{$tmpsum}} €</td>
                        <td width="10%">
                            {!! Form::open(['url' => 'p_buy_res']) !!}
                            {!! Form::hidden('type', $reservation_type, ['class' => 'form-control'] )!!}
                            {!! Form::hidden('u_id', $res->user_id, ['class' => 'form-control'] )!!}
                            {!! Form::hidden('p_id', $res->projection, ['class' => 'form-control'] )!!}
                            {!! Form::submit('Kúpiť', ['class' => 'btn btn-info form-control']) !!}
                            {!! Form::close() !!}
                        </td>
                        <td width="10%">
                            {!! Form::open(['url' => 'p_del_res']) !!}
                            {!! Form::hidden('type', $reservation_type, ['class' => 'form-control'] )!!}
                            {!! Form::hidden('u_id', $res->user_id, ['class' => 'form-control'] )!!}
                            {!! Form::hidden('p_id', $res->projection, ['class' => 'form-control'] )!!}
                            {!! Form::submit('Storno', ['class' => 'btn btn-danger form-control']) !!}
                            {!! Form::close() !!}
                        </td>
                        </tr>
                        </tbody>
                        </table>
                        <?php $tmpsum = 0; 
                              $seatstring=""?>
                    @endif
                @endif
                <?php $tmp_uid = $res->user_id; ?>
                <?php $tmp_name = $res->name; ?>
                <?php $tmp_email = $res->email; ?> 
            @endforeach
            </div>
@endif
@endsection
