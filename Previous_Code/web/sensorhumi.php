<?php
    //koneksi ke database
    $koneksi = mysqli_connect("localhost", "root", "", "websensor");

    //baca data sensor
    $sql = mysqli_query($koneksi, "select * from sensor");
    $data = mysqli_fetch_array($sql);
    $humidity = $data["humi"];

    echo "$humidity"
?>