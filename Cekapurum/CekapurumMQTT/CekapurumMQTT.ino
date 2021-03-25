#include <AntaresESP8266MQTT.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Servo.h>
#include "DHT.h"
#define DHTTYPE DHT11

#define ACCESSKEY "6e6b74ca7ead77f7:09437f0a4cc56904"
#define WIFISSID "dikry"
#define PASSWORD "123dikri"

#define projectName "Cekapurumiot"
#define deviceName "CekapurumSensor"

AntaresESP8266MQTT antares(ACCESSKEY);

DHT dht(13, DHTTYPE);
Servo cekservo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

int button = 16; 
int led_merah = 14;
int led_hijau = 12;
int buzzer = 0;
int pinServo = 2;
int pinFlame = A0;

int f;
int buttonState;
float h;
float t;

void setup() {
  Serial.begin(115200);
  antares.setDebug(true);
  antares.wifiConnection(WIFISSID, PASSWORD);
  antares.setMqttServer();
  dht.begin();
  Wire.begin(4,5);
  lcd.begin();
  lcd.backlight();
  cekservo.attach(pinServo);
  cekservo.write(0);
  pinMode(led_merah, OUTPUT);
  pinMode(led_hijau, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  antares.checkMqttConnection();

  buttonState = digitalRead(button);
  f = analogRead(pinFlame);
  t = dht.readTemperature();
  h = dht.readHumidity();
  
  /*if(isnan(t)){
    Serial.println("Data Nan!");
  } else {
    Serial.print("Units Fire Sensor : ");
    Serial.print(f);
    Serial.print(" Units / ");
    Serial.print("Suhu : ");
    Serial.print(t);
    Serial.print("°");
    Serial.print("C / ");
    Serial.print("Kelembaban: ");
    Serial.print(h);
    Serial.print(" %\n");
    delay(250);
  }*/
  
  if(f<100 && t>35 && h<50){
    lcd.clear();
    digitalWrite(led_hijau, LOW);
    digitalWrite(led_merah, HIGH);
    digitalWrite(buzzer, HIGH);
    cekservo.write(90);
    lcd.setCursor(0,0);
    lcd.print("KEBAKARAN !!");
    lcd.setCursor(0,1);
    lcd.print("SELAMATKAN DIRI !!");
    delay(200); 
  } else {
    lcd.clear();
    digitalWrite(led_hijau, HIGH);
    digitalWrite(led_merah, LOW);
    digitalWrite(buzzer, LOW);
    cekservo.write(0);
    lcd.setCursor(0,0);
    lcd.print("TEMP : ");
    lcd.print(t);
    lcd.print("'C ");
    lcd.setCursor(0,1);
    lcd.print("HUMI : ");
    lcd.print(h);
    lcd.print(" %");
    delay(200); 
  }

  if (buttonState==1){
    lcd.clear();
    cekservo.write(0);
    digitalWrite(buzzer, LOW);
    digitalWrite(led_hijau, LOW);
    digitalWrite(led_merah, LOW);
    lcd.setCursor(0,0);
    lcd.print("Sistem");
    lcd.setCursor(0,1);
    lcd.print("Direset!!");
    delay(20000);
  } 

  antares.add("temperature", t);
  antares.add("humidity", h);
  antares.add("fire_units", f);
  antares.publish(projectName, deviceName);
  delay(1000);
}
