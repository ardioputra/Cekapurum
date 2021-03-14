#include<LiquidCrystal.h>   //memasukan library LCD ke program        
#include<Servo.h>           //memasukan library servo ke program
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
float temp = 0;
float gas = 0;

const int analog = A0;
int gassen = 0;
int temptmp = 0;

int led_caution = D1;                 //inisialisasi led_caution di PIN 11 pada ARDUINO UNO
int buzzer = D3;
int led_fine = D2;                     //inisialisasi led_fine di PIN 3 pada ARDUINO UNO
int pushButton = D5;
int pinServo = D4;
//int flamesen = x;                     //ganti sesuai dengan pinout yang digunakan (digital)

float tmp;
int flameon;
int buttonState;

Servo cekservo;                       //inisialisasi variable myservo untuk menggerakan posisi servo
LiquidCrystal lcd(D6, D7, D8, D8, D8, D8);

//apabila ingin menggunakan nodemcu esp8266 rubah sesuai dengan pin yang dipasang

void setup()
{
  Serial.begin(9600);               //mendeklarasi kecepatan data rate untuk Serial Monitor
  cekservo.attach(pinServo);        //mendeklarasi pin D2 di arduino terhubung dengan kabel Signal di motor servo
  lcd.begin(16,2);
  //pinMode(flamesen, INPUT);
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
  //flameon = digitalRead(flamesen);
  
  gas = analogRead(analog);
  tmp = analogRead(analog);

  temp = tmp*5; 
  temp = temp/1024;
  temp = (temp-0.5)*100;
  if (temp >= 30 && gas >= 100 ) {
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
