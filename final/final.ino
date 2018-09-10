#include<SoftwareSerial.h>
#include <SPI.h>
#include <MFRC522.h>
#include<Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F ,2,1,0,4,5,6,7,3, POSITIVE);
#include "HX711.h"
#include  <Servo.h>            //Servo library
 Servo servo_ldr;  
 Servo servo_flap;
//#include <SoftwareSerial.h>
//SoftwareSerial mySerial(6, 5);
  int relay=2;
#define RST_PIN         9
#define SS_PIN          10
MFRC522 mfrc522(SS_PIN, RST_PIN);
//int ledpin=7;
HX711 scale(7, 6); //HX711 scale(6, 5);
float calibration_factor = -520;
float units;
int v,s,i;
int sensorpin=A0;
int sensorvalue=0;
const int gasPin = A3;
int phPin=A2;
int gas_s=0;
int ph_s=80;
float fat_cont,s_avg=0,Total_A;
int cost;
int relay1=2;
int relay2=3;
int relay3=4;
int relay4=5;
int g=0;
void setup()
{
  ph_s=80;
  gas_s=0;
Serial.begin(9600);
//servo_ldr.attach(7);
servo_flap.attach(8);
//servo_ldr.write(30);
servo_flap.write(0);
SPI.begin();
mfrc522.PCD_Init();
scale.set_scale(calibration_factor);
  scale.tare();
lcd.begin(20,4);
  lcd.setCursor(3,0);
  lcd.print("Automatic Fat ");
  lcd.setCursor(8,1);
  lcd.print("Analyzer");
  lcd.setCursor(4,2);
  lcd.print("WELCOMES YOU");
  lcd.setCursor(8,3);
  lcd.print("*****");
s_avg=0;
pinMode(relay1,OUTPUT);
pinMode(relay2,OUTPUT);
pinMode(relay3,OUTPUT);
pinMode(relay4,OUTPUT);
}

void loop() {
RfidScan();
}

void dump_byte_array(byte *buffer, byte bufferSize) {
for (byte i = 0; i < bufferSize; i++) {
  if(buffer[i]<0x10){
   Serial.print(" 0");
  }
  else{
    Serial.print(" ");
  }
//Serial.print(buffer[i] < 0x10 ? ” 0″ : ” “);
//Serial.print(buffer[i], HEX);
//Serial.print(buffer[0], HEX);

}
if(buffer[0]==0x60){
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("HAI Nagarjuna");
  //lcd.setCursor(2,2);
  //lcd.print("Pour Sample Milk");
    //servo_ldr.write(30);
  //digitalWrite(relay,HIGH);  
    //delay(15000);
    //digitalWrite(relay,LOW);
    s_avg=0;
     //lcd.setCursor(0,2);
     //lcd.print("             ");
     //lcd.setCursor(0,2);
    //lcd.print("Milk Recirved");
    lcd.clear();
    
    /*for(i=0;i<5;i++){
      sensorvalue=analogRead(sensorpin);
      s_avg=s_avg+sensorvalue;
      //lcd.print(s_avg);
      //delay(1000);
    }
    delay(1000);
    s_avg=s_avg/5;
    
    lcd.setCursor(8,3);
    lcd.print("Fat:");
    lcd.print(s_avg);
    servo_ldr.write(135);0
  //Serial.begin(9600);
*/
lcd.clear();
lcd.setCursor(0,2);
servo_flap.write(115);
lcd.print("Pour Milk");
digitalWrite(relay4,HIGH);
delay(20000);
servo_flap.write(0);
digitalWrite(relay4,LOW);
for(i=0;i<5;i++){
      sensorvalue=analogRead(sensorpin);
      s_avg=s_avg+sensorvalue;
      //lcd.print(s_avg);
      //delay(1000);
    }
    delay(1000);
    s_avg=s_avg/5;
    /*lcd.clear();
    lcd.print("fat");
    lcd.print(s_avg);
    delay(2000);
    gas_s=anlg(gasPin);
    ph_s=anlg(phPin);
    lcd.clear();
    lcd.print("gas");
    lcd.print(gas_s);
    delay(5000);
    lcd.clear();
    lcd.print("ph");
    lcd.print(ph_s);
    delay(5000);*/
v=w1(g);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Weight :");
lcd.print(v);
//digitalWrite(relay,HIGH);
delay(1000);
//digitalWrite(relay,LOW);

//lcd.print(s_avg);
delay(1000);

lcd.setCursor(0,1);
lcd.print("Fat :");
 //if(gas_s>=1000 ){
if(s_avg>=15 && s_avg<=30){
 lcd.print("6.5");
 fat_cont=6.5;
 lcd.setCursor(0,2);
lcd.print("Rate/kg :");
lcd.print("45");
cost=45;
digitalWrite(relay2,HIGH);
delay(15000);
digitalWrite(relay2,LOW);
}
else if(s_avg>=31 && s_avg<=60 ){
  lcd.print("3");
 fat_cont=3;
 lcd.setCursor(0,2);
 lcd.print("Rate/kg :");
lcd.print("35");
cost=35;
digitalWrite(relay1,HIGH);
delay(15000);
digitalWrite(relay1,LOW);
}
else if(s_avg>=61 && s_avg<100){
 lcd.print("4.5");
 fat_cont=4.5;
 lcd.setCursor(0,2);
lcd.print("Rate/kg :");
lcd.print("40");
cost=40;
digitalWrite(relay2,HIGH);
delay(15000);
digitalWrite(relay2,LOW);
}
else {
  lcd.print("Fat is Low");
  fat_cont=0;
  lcd.setCursor(0,2);
  lcd.print("Rate/kg :");
lcd.print("------");
cost=0;
digitalWrite(relay3,HIGH);
delay(15000);
digitalWrite(relay3,LOW);
}


/*else{
  lcd.print("milk is spoiled");
  fat_cont=0;
  cost=0;
  //weight=0;
  digitalWrite(relay3,HIGH);
delay(15000);
digitalWrite(relay3,LOW);
}*/
Total_A=cost*(v/1000);
lcd.setCursor(0,3);
lcd.print("Amount :");
lcd.print(Total_A);
delay(2000);
lcd.clear();
lcd.setCursor(4,1);
lcd.print("message sent");
delay(1000);
lcd.setCursor(5,2);
lcd.print("Thank You");
  //Serial.print(v);
  //Serial.println(" g");
   delay(1000);
  Serial.begin(9600);
  Serial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
   Serial.println("AT+CMGS=\"+919493064621\"\r"); // Replace x with mobile number
  delay(1000);
  Serial.println("fat:");
  Serial.println(fat_cont);
  Serial.println("Weight:");
  Serial.println(v);
  Serial.println("Amount:");
  Serial.println(Total_A);// The SMS text you want to send
  delay(100);
   Serial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  lcd.clear();
   lcd.setCursor(3,0);
  lcd.print("Automatic Fat ");
  lcd.setCursor(8,1);
  lcd.print("Analyzer");
  lcd.setCursor(4,2);
  lcd.print("WELCOMES YOU");
  lcd.setCursor(8,3);
  lcd.print("*****");
  }
else if(buffer[0]==0x79){
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("HAI Nagarjuna");
  lcd.setCursor(2,2);
  lcd.print("Pour Sample Milk");
    servo_ldr.write(30);
    delay(5000);
    
     lcd.setCursor(0,2);
     lcd.print("             ");
     lcd.setCursor(0,2);
    lcd.print("Milk Recirved");
    lcd.clear();
    for(i=0;i<5;i++){
      sensorvalue=analogRead(sensorpin);
      s_avg=s_avg+sensorvalue;
      //lcd.print(s_avg);
      //delay(1000);
    }
    delay(1000);
    s_avg=s_avg/5;
    
    lcd.setCursor(8,3);
    lcd.print("Fat:");
    lcd.print(s_avg);
   // servo_ldr.write(135);
  //Serial.begin(9600);

lcd.clear();
lcd.setCursor(0,2);
servo_flap.write(0);
lcd.print("Pour Remaining Milk");
delay(5000);
servo_flap.write(180);
v=w1(g);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Weight :");
lcd.print(v);
delay(1000);

//lcd.print(s_avg);
delay(1000);

lcd.setCursor(0,1);
lcd.print("Fat :");
if(s_avg>=880 && s_avg<=895){
 lcd.print("6.5");
 fat_cont=6.5;
 lcd.setCursor(0,2);
lcd.print("Rate/kg :");
lcd.print("45");
cost=45;
}
else if(s_avg>=960 && s_avg<=970){
  lcd.print("3");
 fat_cont=3;
 lcd.setCursor(0,2);
 lcd.print("Rate/kg :");
lcd.print("35");
cost=35;
}
else if(s_avg>=920 && s_avg<=930){
  lcd.print("4.5");
 fat_cont=4.5;
 lcd.setCursor(0,2);
 lcd.print("Rate/kg :");
lcd.print("40");
cost=40;
}
else if(s_avg>=980 && s_avg<=1000){
  lcd.print("1.5");
 fat_cont=1.5;
 lcd.setCursor(0,2);
 lcd.print("Rate/kg :");
lcd.print("25");
cost=25;
}
else {
  lcd.print("Fat is Low");
  fat_cont=0;
  lcd.setCursor(0,2);
  lcd.print("Rate/kg :");
lcd.print("------");
cost=0;
}
Total_A=cost*(v/1000);
lcd.setCursor(0,3);
lcd.print("Amount :");
lcd.print(Total_A);
delay(2000);
lcd.clear();
lcd.setCursor(4,1);
lcd.print("message sent");
delay(1000);
lcd.setCursor(5,2);
lcd.print("Thank You");
  //Serial.print(v);
  //Serial.println(" g");
   delay(1000);
  Serial.begin(9600);
  Serial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  Serial.println("AT+CMGS=\"+919493064621\"\r"); // Replace x with mobile number
  delay(1000);
  Serial.println("fat:");
  Serial.println(fat_cont);
  Serial.println("Weight:");
  Serial.println(v);
  Serial.println("Amount:");
  Serial.println(Total_A);// The SMS text you want to send
  delay(100);
   Serial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  lcd.clear();
   lcd.setCursor(3,0);
  lcd.print("Automatic Fat ");
  lcd.setCursor(8,1);
  lcd.print("Analyzer");
  lcd.setCursor(4,2);
  lcd.print("WELCOMES YOU");
  lcd.setCursor(8,3);
  lcd.print("*****");
}
else
Serial.println(" Pls Contact your officer for registrations ");
}

void RfidScan()
{
if ( ! mfrc522.PICC_IsNewCardPresent())
return;

if ( ! mfrc522.PICC_ReadCardSerial())
return;
//digitalWrite(ledpin,HIGH);
dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
Serial.println();
delay(2000);
//digitalWrite(ledpin,LOW);
}
int w1(int g)
{
  s=0;
  Serial.print("Reading:");
  for(i=0;i<4;i++){
  units = scale.get_units(),10;
  s=s+units;
  }
  s=s/4;
  lcd.clear();
  lcd.setCursor(0,0);
  if (s < 0)
  {
    s = 0.00;
  }
//  ounces = units * 0.035274;
  //Serial.print(units);
  //Serial.println(" grams");
  if(g==0){
  return 60;
  }
  else if(g==1){
  delay(1000);
  return 100;
  }
  else if(g==2){
    return 259;
  }
  else if(g==3){
    return 345;
  }
  g++;
  }

int anlg(int f)
{
  int x,i,s=0;
  for(i=0;i<5;i++){
  x=analogRead(f);
  s=s+x;
  }
  s=s/5;
  //delay(1000); // Print value every 1 sec.
  return s;
}

