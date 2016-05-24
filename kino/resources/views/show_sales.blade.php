@extends('app')

@section('htmlheader_title')
    Reserve
@endsection


@section('main-content')
<div class="container">
{!! Form::open(['url' => 'show_sales_data']) !!}
{!! Form::label('kino','Kino') !!}
{!! Form::select('kino', array('Aupark' => 'Aupark', 'Eurovea' => 'Eurovea' , '--' => '--'), $kino, ['class' => 'form-control']); !!}
{!! Form::label('film','Film') !!}
{!! Form::select('film', array('Most špiónov' => 'Most špiónov', 'Malý princ' => 'Malý princ' ,'Spectre' => 'Spectre' , '--' => '--'), $film, ['class' => 'form-control']); !!}
{!! Form::label('start','Začiatok') !!}
{!! Form::input('date', 'start', null, ['class' => 'form-control', 'placeholder' => 'Date']) !!}
{!! Form::label('stop','Koniec') !!}
{!! Form::input('date', 'stop', null, ['class' => 'form-control', 'placeholder' => 'Date']) !!}
{!! Form::submit('Zobraz tržbu', ['class' => 'btn btn-primary']) !!}
{!! Form::close() !!}
<h2>{{$msg}}</h2>
</div>
@endsection
