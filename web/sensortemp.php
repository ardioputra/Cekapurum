<?php
    //koneksi ke database
    $koneksi = mysqli_connect("localhost", "root", "", "sensorweb");

    //baca data sensor
    $sql = mysqli_query($koneksi, "select * from sensor");
    $data = mysqli_fetch_array($sql);
    $temperature = $data["temp"];

    echo "$temperature"
?>