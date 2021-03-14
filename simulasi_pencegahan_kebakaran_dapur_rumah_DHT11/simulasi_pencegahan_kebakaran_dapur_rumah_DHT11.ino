#include<LiquidCrystal.h>   //memasukan library LCD ke program        
#include<Servo.h>           //memasukan library servo ke program
#include<Adafruit_Sensor.h> 
#include "DHT.h"
#define DHTPIN 13
#define DHTTYPE DHT11
#define D0 16;
#define D1 5;
#define D2 4;
#define D3 0;
#define D4 2;
#define D5 14;
#define D6 12;
#define D7 13;
#define D8 15;
#define D9 3;
#define D10 1;
#define Analog A0;
DHT dht(DHTPIN, DHTTYPE)

int led_caution = D1;                 //inisialisasi led_caution di PIN 11 pada ARDUINO UNO
int buzzer = D3;
int led_fine = D2;                     //inisialisasi led_fine di PIN 3 pada ARDUINO UNO
int pushButton = D5;
int pinServo = D4;
int flamesen = D9;                     //ganti sesuai dengan pinout yang digunakan (digital)

float t;
float h;
int flameon;
int buttonState;

Servo cekservo;                       //inisialisasi variable myservo untuk menggerakan posisi servo
LiquidCrystal lcd(D6, D7, D8, D8, D8, D8);

void setup()
{
  Serial.begin(9600);               //mendeklarasi kecepatan data rate untuk Serial Monitor
  cekservo.attach(pinServo);        //mendeklarasi pin D2 di arduino terhubung dengan kabel Signal di motor servo
  lcd.begin(16,2);
  pinMode(led_caution, OUTPUT);     //mendeklarasi led_caution sbg OUTPUT
  pinMode(led_fine, OUTPUT);        //mendeklarasi led_fine sbg OUTPUT
  pinMode(buzzer, OUTPUT);          //mendeklarasi Buzzer Piero sbg OUTPUT
}

void loop()
{
  buttonState = digitalRead(pushButton);
  //flameon = digitalRead(flamesen);
  t = dht.temperature
  h = dht.humidity
  if (t >= 30 && h <= 30 ) {
    lcd.clear();
    digitalWrite(led_caution, HIGH);
    digitalWrite(led_fine, LOW);
    digitalWrite(buzzer, HIGH);
    cekservo.write(90);
    lcd.setCursor(0,0);
    lcd.print("Kebakaran!!");
    lcd.setCursor(0,1);
    lcd.print("Selamatkan Diri");
  } else {
    lcd.clear();
    digitalWrite(led_caution, LOW);
    digitalWrite(led_fine, HIGH);       //LED nyala
    digitalWrite(buzzer, LOW);
    cekservo.write(0);
    lcd.setCursor(0,0);
    lcd.print("Kelembapan: ");
    lcd.print(h);
    lcd.print("%");
    lcd.setCursor(0,1);
    lcd.print("Suhu: ");
    lcd.print(t);
    lcd.print((char)223);
    lcd.print("C");
  }
  
  if (buttonState==1){
    lcd.clear();
    cekservo.write(0);
    digitalWrite(buzzer, LOW);
    digitalWrite(led_fine, LOW);        //LED Mati
    digitalWrite(led_caution, LOW);     //LED Mati
    lcd.setCursor(0,0);
    lcd.print("Sistem");
    lcd.setCursor(0,1);
    lcd.print("Direset!!");
    delay(20000);
  }  
  delay(1000);
}
