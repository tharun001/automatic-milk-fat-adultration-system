int rfid0 = 10;
int row=0;
void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  Serial.println("CLEARDATA");
  Serial.println("LABEL,Time,LDR_Read");
}
 
void loop() {
  int rfidreading = digitalRead(rfid0);
  Serial.print("DATA,TIME,");Serial.println(rfidreading);
  row++;
  rfidreading++;
 
  delay(100);
}
