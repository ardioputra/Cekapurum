#include<Adafruit_Sensor.h>
#include<Servo.h>
#include "DHT.h"
#define DHTTYPE DHT11
#define DHTPIN 16

DHT dht(DHTPIN, DHTTYPE);
Servo cekservo;

/*
 * Ganti Pin sesuai dengan keinginan kecuali variabel f, f untuk indikator api
 * static const uint8_t D0   = 16;
 * static const uint8_t D1   = 5;
 * static const uint8_t D2   = 4;
 * static const uint8_t D3   = 0;
 * static const uint8_t D4   = 2;
 * static const uint8_t D5   = 14;
 * static const uint8_t D6   = 12;
 * static const uint8_t D7   = 13;
 * static const uint8_t D8   = 15;
 * static const uint8_t D9   = 3;
 * static const uint8_t D10  = 1;
 */

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
  Serial.println("Test Humidity and temperature\n\n");
  pinMode(led_merah, OUTPUT);
  pinMode(led_hijau, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  f = analogRead(pinFlame);
  float t = dht.readTemperature();
  Serial.print("temperature = ");
  Serial.print(t); 
  Serial.println("C  ");
  delay(200);
  if(f<100 && t>=36.5){
    digitalWrite(led_hijau, LOW);
    digitalWrite(led_merah, HIGH);
    tone(buzzer,5000,5000);
    cekservo.write(90);
    Serial.print("Kebakaran!");
    delay(200); 
  } else {
    digitalWrite(led_hijau, HIGH);
    digitalWrite(led_merah, LOW);
    tone(buzzer,0,0);
    delay(1000); 
  } 
}
