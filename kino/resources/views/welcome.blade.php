<html>
	<head>
		<title>Vitajte</title>
		
		<style>
			body {
				margin: 0;
				padding: 0;
				width: 100%;
				height: 100%;
				color: black;
				display: table;
				font-weight: 100;
				font-family: 'Lato';
			}

			.container {
				text-align: center;
				display: table-cell;
				vertical-align: middle;
			}

			.content {
				text-align: center;
				display: inline-block;
			}

			.title {
				font-size: 96px;
				margin-bottom: 40px;
			}

			.quote {
				font-size: 24px;
			}
		</style>
	</head>

	<body>
		<div class="container">
			<div class="content">

               <form action="{{ url('/auth/login') }}">
               <input type="submit" style="font-face: 'Comic Sans MS'; font-size: larger; color: black;
                background-color: white; border: 3pt ridge lightgrey; height:50px; width:300px" value=" Vstúp do systému ">
               </form>
				<div class="title">Cinemax</div>
			</div>
		</div>
	</body>
</html>
