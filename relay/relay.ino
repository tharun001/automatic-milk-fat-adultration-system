int relay1=2;
int relay2=3;
int relay3=4;
int relay4=5;
void setup() {
  // put your setup code here, to run once:

pinMode(relay1,OUTPUT);
pinMode(relay2,OUTPUT);
pinMode(relay3,OUTPUT);
pinMode(relay4,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

digitalWrite(relay1,HIGH);
delay(5000);
digitalWrite(relay1,LOW);
delay(5000);
digitalWrite(relay2,HIGH);
delay(5000);
digitalWrite(relay2,LOW);
delay(5000);

digitalWrite(relay3,HIGH);
delay(5000);
digitalWrite(relay3,LOW);
delay(5000);
digitalWrite(relay4,HIGH);
delay(5000);
digitalWrite(relay4,LOW);
delay(5000);

}
