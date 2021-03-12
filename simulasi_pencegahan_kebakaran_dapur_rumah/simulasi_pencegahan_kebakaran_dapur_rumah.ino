#include<LiquidCrystal.h>  
#include<Servo.h>
float temp = 0;
float tmp;
float gas = 0;
int const pinServo = 2;
int const temptmp = A0;
int const gassen = A1;
int led_caution = 11;
int buzzer = 4;
int led_fine = 3;
int pushButton = 12;
Servo cekservo;
LiquidCrystal lcd(5, 6, 10, 9, 8, 7);
void(* resetFunc)(void)=0;

void setup()
{
  lcd.begin(16,2);
  pinMode(temptmp, INPUT);
  pinMode(pushButton, INPUT);
  pinMode(led_caution, OUTPUT);
  pinMode(led_fine, OUTPUT);
  pinMode(gassen, INPUT);
  pinMode(buzzer, OUTPUT);
  cekservo.attach(pinServo);
  Serial.begin(9600);
}

void loop()
{
  int buttonState = digitalRead(pushButton);
  digitalWrite(led_caution, LOW);
  gas = analogRead(gassen);
  tmp = analogRead(temptmp);
  temp = tmp*5; 
  temp = temp/1024;
  temp = (temp-0.5)*100;
  if (temp >= 110.5 && gas >= 100) {
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
    digitalWrite(led_fine, HIGH);
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
    digitalWrite(led_fine, LOW);
    digitalWrite(led_caution, LOW);
    lcd.setCursor(0,0);
    lcd.print("Sistem");
    lcd.setCursor(0,1);
    lcd.print("Direset!!");
    delay(10000);
  }  
  delay(1000);
}
