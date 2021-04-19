<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Cekapurum V.1.1</title>
    <!-- Bootstrap CSS -->
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.0-beta3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-eOJMYsd53ii+scO/bJGFsiCZc+5NDVN2yr8+0RDqr0Ql0h+rP48ckxlpbzKgwra6" crossorigin="anonymous">
    <link rel="stylesheet" type="text/css" href="css/style.css">
    <script type="text/javascript" src="jquery/jquery.min.js"></script>
    <link rel="preconnect" href="https://fonts.gstatic.com">
    <link href="https://fonts.googleapis.com/css2?family=Quicksand:wght@500&display=swap" rel="stylesheet">
    <script type="text/javascript">
        $(document).ready(function(){
            setInterval(function(){
                $("#sensortemp").load('sensortemp.php');
                $("#sensorhumi").load('sensorhumi.php');
                $("#sensorfire").load('sensorfire.php');
                $("#sensorstat").load('sensorstat.php');
            }, 1000);
        });
    </script>
</head>
<body>
    <!--loader-->
    <div class="bg-loader">
        <div class="loader"></div>
    </div>
    
    <header>
        <div class="container"> 
            <h1><a href="index.html">CEKAPURUM</a></h1>
            <ul>
                <li><a href="index.html">HOME</a></li>
                <li><a href="about.html">ABOUT</a></li>
                <li><a href="sensor.php">DATA</a></li>
            </ul>
        </div>
    </header>
   
    <!--sensor-->
    <section class="sensor">
        <div class="container">
            <h3>Data</h3>
            <p>Berikut merupakan data yang diterima oleh sensor</p>
        <div style="display: flex; ">

            <!--suhu-->
        <div class="card text-center" style="width: 25%">
            <div class="card-header" style="font-size: 20px; font-weight: bold; background-color: grey">
                Temperature
            </div>
            <div class="card-body">
             <h4><span id="sensortemp"></span></h4>
            </div>
        </div>

            <!--kelembaban-->
        <div class="card text-center" style="width: 25%">
            <div class="card-header" style="font-size: 20px; font-weight: bold; background-color: grey">
                Humidity
            </div>
            <div class="card-body">
             <h4><span id="sensorhumi"></span></h4>
            </div>
        </div>

            <!--fire-->
        <div class="card text-center" style="width: 25%">
            <div class="card-header" style="font-size: 20px; font-weight: bold; background-color: grey">
                Fire Sensor
            </div>
            <div class="card-body">
             <h4><span id="sensorfire"></span></h4>
            </div>
        </div>

            <!--status-->
        <div class="card text-center" style="width: 25%">
            <div class="card-header" style="font-size: 20px; font-weight: bold; background-color: grey">
                Status
            </div>
            <div class="card-body">
             <h4><span id="sensorstat"></span></h4>
            </div>
        </div>

        </div>  
    </section>

    <script type="text/javascript">
        $(document).ready(function(){
            $(".bg-loader").hide();
        })
    </script>
</body>
</html>