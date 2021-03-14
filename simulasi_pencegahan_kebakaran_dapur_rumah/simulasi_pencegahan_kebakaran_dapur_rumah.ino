#include<LiquidCrystal.h>   //memasukan library LCD ke program        
#include<Servo.h>           //memasukan library servo ke program

float temp = 0;
float gas = 0;

/*
 * untuk analog dual pinpoint
 * const int analog = A0;
 * int sensorgas = 0;
 * int sensortmp = 0;
 */

const int temptmp = A0;
const int gassen = A1;
int led_caution = 11;                 //inisialisasi led_caution di PIN 11 pada ARDUINO UNO
int buzzer = 4;
int led_fine = 3;                     //inisialisasi led_fine di PIN 3 pada ARDUINO UNO
int pushButton = 12;
int pinServo = 2;
int flamesen = x;                     //ganti sesuai dengan pinout yang digunakan (digital)

float tmp;
int flameon;
int buttonState;

Servo cekservo;                       //inisialisasi variable myservo untuk menggerakan posisi servo
LiquidCrystal lcd(5, 6, 10, 9, 8, 7);

//apabila ingin menggunakan nodemcu esp8266 rubah sesuai dengan pin yang dipasang

void setup()
{
  Serial.begin(9600);               //mendeklarasi kecepatan data rate untuk Serial Monitor
  cekservo.attach(pinServo);        //mendeklarasi pin D2 di arduino terhubung dengan kabel Signal di motor servo
  lcd.begin(16,2);
  pinMode(flamesen, INPUT);
  pinMode(temptmp, INPUT);
  pinMode(pushButton, INPUT);
  pinMode(led_caution, OUTPUT);     //mendeklarasi led_caution sbg OUTPUT
  pinMode(led_fine, OUTPUT);        //mendeklarasi led_fine sbg OUTPUT
  pinMode(gassen, INPUT);           //mendeklarasi Gas Sensor sbg INPUT
  pinMode(buzzer, OUTPUT);          //mendeklarasi Buzzer Piero sbg OUTPUT
}

void loop()
{
  buttonState = digitalRead(pushButton);
  flameon = digitalRead(flamesen);
  /*
   * nanti ganti juga variabel gas dan tmp karena kita hanya bikin satu pin analog
   * sensorgas = analogRead(analog);
   * sensortmp = analogRead(analog);
   */
  gas = analogRead(gassen);
  tmp = analogRead(temptmp);
  temp = tmp*5; 
  temp = temp/1024;
  temp = (temp-0.5)*100;
  if (temp >= 110.5 && gas >= 100 && flameon == 1) {
    delay(200);
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
    delay(200);
    lcd.clear();
    digitalWrite(led_caution, LOW);
    digitalWrite(led_fine, HIGH);       //LED nyala
    digitalWrite(buzzer, LOW);
    cekservo.write(0);
    lcd.setCursor(0,0);
    lcd.print("Masih Aman");
    lcd.setCursor(0,1);
    lcd.print("Suhu: ");
    lcd.print(temp);
    lcd.print(" 'C");
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
