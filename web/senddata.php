<?php
    //koneksi ke database
    $koneksi = mysqli_connect("localhost", "root", "", "sensorweb");
    $temp = $_GET['temp']
    $humi = $_GET['humi']
    $fire = $_GET['fire']
    $stat = $_GET['stat']

    mysqli_query($koneksi, "ALTER TABLE sensor AUTO_INCREMENT=1");
    $update = mysqli_query($koneksi, "insert into sensor(temp,humi,fire,stat)values('$temp','$humi','$fire','$stat')");

    if($update)
        echo "Acquired";
    else
        echo "Failed";

?>