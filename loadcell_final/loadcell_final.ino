 #include "HX711.h"  //You must have this library in your arduino library folder
 
#define DOUT  3
#define CLK  2
 
HX711 scale(DOUT, CLK);
 float calibration_factor = -96650; //-106600 worked for my 40Kg max scale setup 
void setup() {
  Serial.begin(9600);  
  Serial.println("Press T to tare");
  scale.set_scale(-96650);  //Calibration Factor obtained from first sketch
  scale.tare();             //Reset the scale to 0  
}
 
void loop() {
  Serial.print("Weight: ");
  Serial.print(scale.get_units(), 3);  //Up to 3 decimal points
  Serial.println(" kg"); //Change this to kg and re-adjust the calibration factor if you follow lbs
 
  if(Serial.available())
  {
    char temp = Serial.read();
    if(temp == 't' || temp == 'T')
      scale.tare();  //Reset the scale to zero      
  }
}

