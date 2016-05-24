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
                    @foreach($my_seats as $my_seat)
                        @if ($seat->seat_id == $my_seat->seat)
                            <?php $seat_reserved = 2; ?>
                            <?php $r_id = $my_seat->r_id; ?>
                        @endif
                    @endforeach
                @endif

            @endforeach
 

            @foreach($tickets as $ticket)
                @if ($seat->seat_id == $ticket->seat)
                    <?php $seat_reserved = 1; ?>
                @endif
            @endforeach

            <?php $count = $count + 1; ?>
            @if ($count % 14 == 1) 
                <tr>
            @endif



            @if ($seat_reserved != 0) 
                @if ($seat_reserved == 2)
                    <td width="7%">
                        {!! Form::open(['url' => 'stornoreservation']) !!}
                        {!! Form::hidden('type', $reservation_type, ['class' => 'form-control'] )!!}
                        {!! Form::hidden('p_id', $p_id, ['class' => 'form-control'] )!!}
                        {!! Form::hidden('r_id', $r_id, ['class' => 'form-control'] )!!}
                        {!! Form::hidden('s_id', $seat->seat_id, ['class' => 'form-control'] )!!}
                        {!! Form::submit($seat->seat, ['class' => 'btn btn-success form-control']) !!}
                        {!! Form::close() !!}
                    </td>        
                @else
                    <td width="7%">
                        {!! Form::open(['url' => 'showprojection']) !!}
                        {!! Form::hidden('type', $reservation_type, ['class' => 'form-control'] )!!}
                        {!! Form::hidden('p_id', $p_id, ['class' => 'form-control'] )!!}
                        {!! Form::submit($seat->seat, ['class' => 'btn btn-danger form-control']) !!}
                        {!! Form::close() !!}
                    </td> 
                @endif
            @else 
                <td width="7%">
                    {!! Form::open(['url' => 'reservation']) !!}
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

{!! Form::open(['url' => 'showprojection']) !!}
{!! Form::select('type', array('detský' => 'Detský', 'študent' => 'Študent' , 'dospelý' => 'Dospelý', 'senior' => 'Senior'), $reservation_type); !!}
{!! Form::hidden('p_id', $tmp_p_id, ['class' => 'form-control'] )!!}
{!! Form::submit('Zmeň typ lístka', ['class' => 'btn btn-primary']) !!}
{!! Form::close() !!}

@endsection
