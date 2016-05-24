@extends('app')

@section('htmlheader_title')
    Film
@endsection


@section('main-content')

<div class="container">
	<div class="row">
		<div class="col-md-10 col-md-offset-1">
		<div class="box-header">

        {!! Form::open(['url' => 'add_salesman']) !!}
            <div class="form-group">
                {!! Form::label('email','Email registrovaného uživateľa:') !!}
                
                {!! Form::text('email', null, ['class' => 'form-control']) !!} 

            </div>

            <div class="form-group">
                {!! Form::submit('Pridaj pokladníka', ['class' => 'btn btn-primary form-control']) !!}
            </div>
        {!! Form::close() !!}
        <h4>{{$msg}}</h4>

		</div>
	</div>
	</div>
</div>
@endsection
