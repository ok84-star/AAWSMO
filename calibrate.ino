#include "HX711.h" //This library can be obtained here http://librarymanager/All#Avia_HX711

#define LOADCELL_DOUT_PIN  A0//Define the pins that the scale is connected to
#define LOADCELL_SCK_PIN  A1

HX711 scale;//initialize the library
float calibration_factor = -395.5;//play around with this number until you get a value that is in the ball park of your actual weight
//The initial numbers that you will see on your scale will most likely be either way too small or way too large, unless they are about right in which case skip this step

void setup() {
  Serial.begin(9600);//begin serial communication
  Serial.println("HX711 calibration sketch");
  Serial.println("Remove all weight from scale");//remove all weight from scale
  Serial.println("After readings begin, place known weight on scale");//place your known weight on the scale, if it is an arbitrarily high or low value adjust the calibration factor significantly because this code will only make minor changes to it. If you are measuring a 100 gram weight and the scale is reading 70000 I recommend going in either direction by 5. 
  Serial.println("Press + or a to increase calibration factor");//open the serial monitor and type in + or -
  Serial.println("Press - or z to decrease calibration factor");

  scale.begin(A0, A1);
  scale.set_scale();
  scale.tare();  //Reset the scale to 0

  long zero_factor = scale.read_average(); //Get a baseline reading
  Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  Serial.println(zero_factor);
}

void loop() {

  scale.set_scale(calibration_factor); //Adjust to this calibration factor

  Serial.print("Reading: ");
  Serial.print(scale.get_units(), 1);//acquires the scale reading
  Serial.print(" g"); //Change this to your desired units and re-adjust the calibration factor if you like 
  Serial.print(" calibration_factor: ");//this will print the calibration factor
  Serial.print(calibration_factor);//,make sure that once you find a calibration factor that works you note it down for that load cell since it will be used in the set up of the code. Make sure to recalibrate your load cell once in a while if you notice off values
  Serial.println();
  delay(2000);

  if(Serial.available())//This part of the code reads the serial communication between your laptop and the load cell. 
  {
    char temp = Serial.read();
    if(temp == '+' || temp == 'a')
      calibration_factor += .1;
    else if(temp == '-' || temp == 'z')
      calibration_factor -= .1;
  }
}
