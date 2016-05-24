@extends('app')

@section('htmlheader_title')
    Reserve
@endsection


@section('main-content')
<h1>Moje rezervácie</h1>
            <?php $pr_id = -1; ?>
            <?php $tmpsum = 0; ?>
            <?php $seatstring = ""; ?>
            <?php $lastElement = end($myreservations); ?>
            <?php $res_id = '';?>
            @foreach($myreservations as $reservation)
            	@if ($reservation->projection != $pr_id) 
            	    @if  ($pr_id != -1 ) 
            	        <table class="table lesson-list-table table-bordered">
				        <tbody>
				         <tr>
            	        <td width="70%">Rezervované miesta: {{$seatstring}}</td>
            	        <td width="20%">Cena: {{$tmpsum}} €</td>
            	        <td width="10%">
                            {!! Form::open(['url' => 'reserve']) !!}
                            {!! Form::hidden('u_id', $reservation->user_id, ['class' => 'form-control'] )!!}
                            {!! Form::hidden('p_id', $res_id, ['class' => 'form-control'] )!!}
                            {!! Form::submit('Storno', ['class' => 'btn btn-primary form-control']) !!}
                            {!! Form::close() !!}
                        </td>
            	        </tr>
            	        </tbody>
                        </table>
                        </div>
                        <?php $res_id = $reservation->projection;?>
            	        <?php $tmpsum = 0; 
            	              $seatstring=""?>
            	    @endif


                    <?php $pr_id = $reservation->projection; ?>
                    <div class="panel panel-default">
				        <div class="panel-heading "><font size="6"> {{ $reservation->kino }} dňa {{DateTime::createFromFormat('Y-m-d H:i:s', $reservation->start )->format('Y-m-d H:i')}} Film: {{ $reservation->film }} Sála: {{ $reservation->hall }}</font></div>

				        <?php $tmpsum = $tmpsum + $reservation->price; ?>
				        <?php $seatstring= $seatstring.$reservation->seat." "; ?>
				    @if  ($lastElement == $reservation) 
                        <?php $res_id = $reservation->projection;?>
            	        <table class="table lesson-list-table table-bordered">
				        <tbody>
				         <tr>
            	        <td width="70%">Rezervované miesta: {{$seatstring}}</td>
            	        

            	        <td width="20%">Cena: {{$tmpsum}} €</td>
            	        
            	        <td width="10%">
                            {!! Form::open(['url' => 'reserve']) !!}
                            {!! Form::hidden('u_id', $reservation->user_id, ['class' => 'form-control'] )!!}
                            {!! Form::hidden('p_id', $res_id, ['class' => 'form-control'] )!!}
                            {!! Form::submit('Storno', ['class' => 'btn btn-primary form-control']) !!}
                            {!! Form::close() !!}
                        </td>
                        
            	        </tr>
            	        </tbody>
                        </table>
                        </div>
            	        <?php $tmpsum = 0; 
            	              $seatstring=""?>
            	    @endif
				        
                @else
                    <?php $tmpsum = $tmpsum + $reservation->price; ?>
				    <?php $seatstring= $seatstring.$reservation->seat." "; ?>
				    @if ($lastElement == $reservation)
				        <table class="table lesson-list-table table-bordered">
				        <tbody>
				         <tr>
            	        <td width="70%">Rezervované miesta: {{$seatstring}}</td>
            	        <td width="20%">Cena: {{$tmpsum}} €</td>
            	        <td width="10%">
                            {!! Form::open(['url' => 'reserve']) !!}
                            {!! Form::hidden('u_id', $reservation->user_id, ['class' => 'form-control'] )!!}
                            {!! Form::hidden('p_id', $res_id, ['class' => 'form-control'] )!!}
                            {!! Form::submit('Storno', ['class' => 'btn btn-primary form-control']) !!}
                            {!! Form::close() !!}
                        </td>
            	        </tr>
            	        </tbody>
                        </table>
                        </div>
                    @endif
                @endif 
                 <?php $res_id = $reservation->projection;?>
            @endforeach


	            
@endsection
