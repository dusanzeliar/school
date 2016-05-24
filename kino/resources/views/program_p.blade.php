@extends('app')

@section('htmlheader_title')
    Film
@endsection


@section('main-content')

<div class="container">
	<div class="row">
		<div class="col-md-10 col-md-offset-1">
		<div class="box-header">

        {!! Form::open(['url' => $url]) !!}
            <div class="form-group">
                {!! Form::label('date','Dátum:') !!}
                
                {!! Form::input('date', 'date', null, ['class' => 'form-control', 'placeholder' => 'Date']) !!} 

            </div>

            <div class="form-group">
                {!! Form::submit('Vyhľadaj program dňa', ['class' => 'btn btn-primary form-control']) !!}
            </div>
        {!! Form::close() !!}

		    <h1>Program kina {{$kino}} dňa {{$time->format('d.m.Y')}}</h1>
		    
			<div class="table">
			    <table class = "table table-bordered table-striped table-hover">
				    <tbody>
				    <?php $tmp = ''; ?>
				    @foreach($projections as $projection)
				        <tr>
				        @if ($projection->name != $tmp)
                            <?php $tmp = $projection->name; ?>
                            <h2>{{ $projection->name }}</h2>
                        @endif
                        
                           {!! Form::open(['url' => 'buyprojection']) !!}
                           {!! Form::hidden('p_id', $projection->p_id, ['class' => 'form-control'] )!!}
                           {!! Form::hidden('type', 'dospelý', ['class' => 'form-control'] )!!}

                           <div class="form-group">
                           <div class="col-lg-10 col-lg-offset-0">
                           {!! Form::submit(DateTime::createFromFormat('Y-m-d H:i:s', $projection->start )->format('H:i'), ['class' => 'btn btn-lg btn-info pull-left']) !!}
                           </div>
                           </div>
                           {!! Form::close() !!}

				            <h2><br></h2>
				        </tr>
                    @endforeach
                    </tbody>              

                </table>
			</div>
		</div>
	</div>
	</div>
</div>
@endsection
