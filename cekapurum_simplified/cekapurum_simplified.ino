#include<Servo.h>
#include "DHT.h"
#define DHTTYPE DHT11
#define dht_dpin 0

static const uint8_t D0   = 16;
static const uint8_t D1   = 5;
static const uint8_t D2   = 4;
static const uint8_t D3   = 0;
static const uint8_t D4   = 2;
static const uint8_t D5   = 14;
static const uint8_t D6   = 12;
static const uint8_t D7   = 13;
static const uint8_t D8   = 15;
static const uint8_t D9   = 3;
static const uint8_t D10  = 1;

DHT dht(dht_dpin, DHTTYPE);
Servo cekservo;

/*
 * Ganti Pin sesuai dengan keinginan kecuali variabel f, f untuk indikator api
 */

int led_merah = D1;
int led_hijau = D2;
int buzzer = D3;
int pinServo = D4;
int pinFlame = A0;

int f = 0;

void setup() {
  dht.begin();
  cekservo.attach(pinServo);
  cekservo.write(0);
  Serial.begin(9600);
  Serial.println("Test Humidity and temperature\n\n");
  pinMode(led_merah, OUTPUT);
  pinMode(led_hijau, OUTPUT);
  pinMode(buzzer, OUTPUT);
  delay(1000);
}

void loop() {
  f = analogRead(pinFlame);
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if(f<100 && t>=36.5){
    digitalWrite(led_hijau, LOW);
    digitalWrite(led_merah, HIGH);
    digitalWrite(buzzer, HIGH);
    cekservo.write(90);
    Serial.print("Kebakaran!");
  } else {
    digitalWrite(led_hijau, HIGH);
    digitalWrite(led_merah, LOW);
    digitalWrite(buzzer, LOW);
    Serial.print("Current humidity = ");
    Serial.print(h);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(t); 
    Serial.println("C  ");
  }
  
  delay(800); 
}
