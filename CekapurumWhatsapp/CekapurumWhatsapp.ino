#include <AntaresESP8266MQTT.h>                       //inisiasi library Antares MQTT
#include <LiquidCrystal_I2C.h>                        //inisiasi library LCD
#include <Adafruit_Sensor.h>                          //inisiasi library Adafruit
#include <Wire.h>                                     //inisiasi library komunikasi I2C
#include <Servo.h>                                    //inisiasi library servo
#include "DHT.h"                                      //inisiasi library sensor suhu&kelembaban
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "base64.h"

#define DHTTYPE DHT11                                 //sensor DHT yang digunakan adalah tipe DHT11
#define ACCESSKEY "6e6b74ca7ead77f7:09437f0a4cc56904" //mendefinisikan ACCESSKEY, ganti dengan Access Key yang terdapat di akun Antares
#define WIFISSID "dikry"                              //mendefinisikan WIFISSID, ganti dengan SSID Wifi anda
#define PASSWORD "123dikri"                           //mendefinisikan PASSWORD, ganti dengan password Wifi anda
#define projectName "Cekapurumiot"                    //mendefinisikan projectName, tuliskan projectname sesuai yang sudah di-inputkan pada Antares
#define deviceName "CekapurumSensor"                  //mendefinisikan deviceName, tuliskan devicename sesuai yang sudah di-inputkan pada Antares

AntaresESP8266MQTT antares(ACCESSKEY);                //memanggil library antares
DHT dht(13, DHTTYPE);                                 //membuat objek dht, pin yang digunakan untuk pembacaan sensor adalah pin 13
Servo cekservo;                                       //membuat objek servo untuk mengontrol servo
LiquidCrystal_I2C lcd(0x27, 16, 2);                   //I2C address 0x27, ukuran LCD 16x2
HTTPClient http;  

int button = 16;                                      //variabel "button" dengan tipe data integer, pin 16
int led_merah = 14;                                   //variabel "led_merah" dengan tipe data integer, pin 14                          
int led_hijau = 12;                                   //variabel "led_hijau" dengan tipe data integer, pin 12
int buzzer = 0;                                       //variabel "buzzer" dengan tipe data integer, pin 0
int pinServo = 2;                                     //variabel "pinServo" dengan tipe data integer, pin 2
int pinFlame = A0;                                    //variabel "pinFlame" dengan tipe data integer, pin A0
int f;                                                //variabel "f" dengan tipe data integer 
int buttonState;                                      //variabel "buttonState" dengan tipe data integer 
float h;                                              //variabel "h" / kelembaban dengan tipe data float
float t;                                              //variabel "t" / suhu dengan tipe data float
String status_kebakaran;                              //variabel "status_kebakaran" dengan tipe data string

String account_sid = "AC8e2712345b5541ceecdfff4e182799e0";
String auth_token = "c9af96ad8df6d795dec00ce235eab955";
String from = "14155238886";
String to = "62xxxxxxxxxxxxxxx"; //ganti sesuai nomor hp
String body;

void setup() {
  Serial.begin(115200);                               //membuka komunikasi serial dengan baudrate(kecepatan transfer data dalam bps) 115200
  WiFi.begin(WIFISSID, PASSWORD);
  antares.setDebug(true);                             //menyalakan debug. Set menjadi "false" jika tidak ingin pesan tampil di serial monitor
  antares.wifiConnection(WIFISSID, PASSWORD);         //mencoba untuk menyambungkan ke Wifi
  antares.setMqttServer();                           //inisiasi server MQTT Antares
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.print("Wifi terkoneksi");
  dht.begin();                                        //menyalakan sensor suhu&kelembaban
  Wire.begin(4,5);                                    //memulai fungsi dengan menginisiasi port I2C
  lcd.begin();                                        //memulai penggunaan LCD
  lcd.backlight();                                    //menyalakan backlight
  cekservo.attach(pinServo);                          //objek servo mengatur pin yang digunakan
  cekservo.write(0);                                  //mengatur posisi servo ke 0 derajat
  pinMode(led_merah, OUTPUT);                         //mengkonfigurasi pin led_merah menjadi output
  pinMode(led_hijau, OUTPUT);                         //mengkonfigurasi pin led_hijau menjadi output
  pinMode(buzzer, OUTPUT);                            //mengkonfigurasi pin buzzer menjadi output
}

void loop() {
  antares.checkMqttConnection();                      //cek koneksi ke broker MQTT Antares. Jika disconnect, akan dicoba untuk menyambungkan lagi

  buttonState = digitalRead(button);                  //membaca nilai digital pada pinFlame dan menyimpannya kedalam variabel "buttonState"
  f = analogRead(pinFlame);                           //membaca nilai analog pada pinFlame dan menyimpannya kedalam variable "f"
  t = dht.readTemperature();                          //variabel "t" digunakan untuk membaca suhu
  h = dht.readHumidity();                             //variabel "h" digunakan untuk membaca kelembaban
  if(isnan(t)){
    Serial.println("Data Nan!");
  } else {
    Serial.print("Units Fire Sensor : ");
    Serial.print(f);
    Serial.print(" Units / ");
    Serial.print("Suhu : ");
    Serial.print(t);
    Serial.print("??");
    Serial.print("C / ");
    Serial.print("Kelembaban: ");
    Serial.print(h);
    Serial.print(" %\n");
    delay(250);
  }
  
  if(f<100 && t>35 && h<50){
    lcd.clear();                                      //menghapus tulisan pada LCD
    digitalWrite(led_hijau, LOW);                     //memberi nilai LOW pada pin led_hijau
    digitalWrite(led_merah, HIGH);                    //memberi nilai HIGH pada pin led_merah
    digitalWrite(buzzer, HIGH);                       //memberi nilai HIGH pada pin buzzer
    cekservo.write(90);                               //mengatur posisi servo ke 90 derajat
    lcd.setCursor(0,0);                               //mengatur tulisan pada kolom 0 dan baris 0
    lcd.print("KEBAKARAN !!");                        //menampilkan tulisan "KEBAKARAN !!" pada LCD
    lcd.setCursor(0,1);                               //mengatur tulisan pada kolom 0 dan baris 1
    lcd.print("SELAMATKAN DIRI !!");                  //menampilkan tulisan "SELAMATKAN DIRI !!" pada LCD
    status_kebakaran = "Kebakaran";                   //indikator status kebakaran
    if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
      body = "Dapur kamu terindikasi kebakaran, Membuka katup dry chemical powder untuk memadamkan api";
      String link = "http://jagorobot.pythonanywhere.com/kirimwa?account_sid=" + account_sid + "&auth_token="+ auth_token +"&to_wa=" + to + "&from_wa="+ from +"&body_message=" + body;
      http.begin(link);
      int httpCode = http.GET();
      Serial.println(httpCode);
      if (httpCode > 0) { //Check for the returning code
        String payload = http.getString();
        Serial.println(link);
        Serial.println(httpCode);
        Serial.println(payload);
        } else {
          Serial.println("Error on HTTP request");
        }
        http.end();
      }
    delay(200);                                       //mengatur waktu jeda selama 2 ms
  } else {
    lcd.clear();                                      //menghapus tulisan pada LCD
    digitalWrite(led_hijau, HIGH);                    //memberi nilai HIGH pada pin led_hijau
    digitalWrite(led_merah, LOW);                     //memberi nilai LOW pada pin led_merah
    digitalWrite(buzzer, LOW);                        //memberi nilai LOW pada pin buzzer
    cekservo.write(0);                                //mengatur posisi servo ke 0 derajat
    lcd.setCursor(0,0);                               //mengatur tulisan pada kolom 0 dan baris 0
    lcd.print("TEMP : ");                             //menampilkan tulisan "TEMP : " pada LCD
    lcd.print(t);                                     //mengambil nilai dari variabel "t" dan menampilkannya pada LCD
    lcd.print("'C ");                                 //menampilkan tulisan "'C " pada LCD
    lcd.setCursor(0,1);                               //mengatur tulisan pada kolom 0 dan baris 1
    lcd.print("HUMI : ");                             //menampilkan tulisan "HUMI: " pada LCD
    lcd.print(h);                                     //mengambil nilai dari variabel "h" dan menampilkannya pada LCD
    lcd.print(" %");                                  //menampilkan tulisan " %" pada LCD
    status_kebakaran = "Aman";                        //indikator status aman
    delay(200);                                       //mengatur waktu jeda selama 2 ms
  }

  if (buttonState==1){
    lcd.clear();                                      //menghapus tulisan pada LCD
    t = 0;
    h = 0;
    f = 0;
    status_kebakaran = "Resetting";
    cekservo.write(0);                                //mengatur posisi servo ke 0 derajat
    digitalWrite(buzzer, LOW);                        //memberi nilai LOW pada pin buzzer
    digitalWrite(led_hijau, LOW);                     //memberi nilai LOW pada led_hijau
    digitalWrite(led_merah, LOW);                     //memberi nilai LOW pada led_merah
    lcd.setCursor(0,0);                               //mengatur tulisan pada kolom 0 dan baris 0
    lcd.print("Sistem");                              //menampilkan tulisan "Sistem" pada LCD
    lcd.setCursor(0,1);                               //mengatur tulisan pada kolom 0 dan baris 1
    lcd.print("Direset!!");                           //menampilkan tulisan "Direset!!" pada LCD
    antares.add("temperature", t);                      //memasukkan value t kedalam variabel "temperature" pada database Non-SQL
    antares.add("humidity", h);                         //memasukkan value h kedalam variabel "humidity" pada database Non-SQL
    antares.add("fire_units", f);                       //memasukkan value f kedalam variabel "fire_units" pada database Non-SQL
    antares.add("status", status_kebakaran);            //memasukkan value status_kebakaran kedalam variabel "status" pada database Non-SQL
    antares.publish(projectName, deviceName); 
    delay(20000);                                     //mengatur waktu jeda selama 20 s
  } else {
    antares.add("temperature", t);                      //memasukkan value t kedalam variabel "temperature" pada database Non-SQL
    antares.add("humidity", h);                         //memasukkan value h kedalam variabel "humidity" pada database Non-SQL
    antares.add("fire_units", f);                       //memasukkan value f kedalam variabel "fire_units" pada database Non-SQL
    antares.add("status", status_kebakaran);            //memasukkan value status_kebakaran kedalam variabel "status" pada database Non-SQL
    antares.publish(projectName, deviceName);            //publish data ke database Antares dan juga broker MQTT Antares
    delay(1000);                                        //mengatur waktu jeda selama 1 s
  }
}
