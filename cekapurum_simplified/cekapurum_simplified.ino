#include<Adafruit_Sensor.h>
#include<Servo.h>
#include "DHT.h"
#define DHTTYPE DHT11

DHT dht(16, DHTTYPE);
Servo cekservo;

int led_merah = 5;
int led_hijau = 4;
int buzzer = 0;
int pinServo = 2;
int pinFlame = A0;

int f = 0;

void setup() {
  Serial.begin(115200);
  dht.begin();
  cekservo.attach(pinServo);
  cekservo.write(0);
  pinMode(led_merah, OUTPUT);
  pinMode(led_hijau, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  f = analogRead(pinFlame);
  delay(2000);
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  if(isnan(t) || isnan(h)){
    Serial.println("Data Nan!");
  }
    Serial.print(f);
    Serial.print("Suhu : ");
    Serial.print(t);
    Serial.print("°");
    Serial.print("C / ");
    Serial.print("Kelembaban: ");
    Serial.print(h);
    Serial.print(" %\t");
  
  if(f<100 || t>30){
    digitalWrite(led_hijau, LOW);
    digitalWrite(led_merah, HIGH);
    digitalWrite(buzzer, HIGH);
    cekservo.write(90);
    delay(200); 
  } else {
    digitalWrite(led_hijau, HIGH);
    digitalWrite(led_merah, LOW);
    digitalWrite(buzzer, LOW);
    cekservo.write(0);
    delay(1000); 
  } 
}
