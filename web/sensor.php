<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Cekapurum V.1.1</title>
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
            <p>Temperatur : <span id="sensortemp"></span><br></p>
            <p>Kelembapan : <span id="sensorhumi"></span><br></p>
            <p>Unit Sensor Api : <span id="sensorfire"></span><br></p>
            <p>Status : <span id="sensorstat"></span><br></p>
        </div>
    </section>

    <script type="text/javascript">
        $(document).ready(function(){
            $(".bg-loader").hide();
        })
    </script>
</body>
</html>