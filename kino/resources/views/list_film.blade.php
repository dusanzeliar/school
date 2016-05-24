@extends('app')

@section('htmlheader_title')
    Film
@endsection


@section('main-content')
<!-- Scrip to show description -->
<script type="text/javascript">
 function showhide(id) {
    var e = document.getElementById(id);
    e.style.display = (e.style.display == 'block') ? 'none' : 'block';
 }
</script>

<div class="container">
	<div class="row">
		<div class="col-md-10 col-md-offset-1">
		    <h1>Filmy v kinách</h1>
		    
			<div class="table">
			    <table class = "table table-bordered table-striped table-hover">
				    <tbody>
				    @foreach($film_db as $film_db)
				        <tr>
				            <h2>{{ $film_db->name }}<br></h2>
				            <img src="/img/<?php echo $film_db->name ?>.jpg"  alt="Poster"/>
				            <h4>({{ $film_db->year }}) {{$film_db->genre}} {{$film_db->minute}} minút<br></h4>

				            <a href="javascript:showhide('{{ $film_db->name }}')">
                                Obsah
                            </a>

                            <div id="{{ $film_db->name }}" style="display:none;">
                                <p>{{ $film_db->description }}</p>
                            </div>

				        </tr>
                    @endforeach
                    </tbody>              

                </table>
			</div>
		</div>
	</div>
</div>
@endsection
