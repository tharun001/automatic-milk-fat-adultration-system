int LDR_Pin = A0;
int row = 0;
void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  Serial.println("CLEARDATA");
  Serial.println("LABEL,Time,LDR_Read");
}
 
void loop() {
  int LDRReading = analogRead(LDR_Pin);
  Serial.print("DATA,TIME,");Serial.println(LDRReading);
  row++;
  LDRReading++;
 
  delay(100);
}
