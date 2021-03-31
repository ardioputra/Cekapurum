<?php
    //koneksi ke database
    $koneksi = mysqli_connect("localhost", "root", "", "websensor");
    $temp = $_GET['temp'];
    $humi = $_GET['humi'];
    $fire = $_GET['fire'];
    $stat = $_GET['stat'];

    mysqli_query($koneksi, "update sensor set temp='$temp'");
    mysqli_query($koneksi, "update sensor set humi='$humi'");
    mysqli_query($koneksi, "update sensor set fire='$fire'");
    mysqli_query($koneksi, "update sensor set stat='$stat'");

?>