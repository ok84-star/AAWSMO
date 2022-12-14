
#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h> // include i/o class header

hd44780_I2Cexp lcd; // declare lcd object: auto locate & config display for hd44780 chip

#include "HX711.h" //include the library for the load cell scale

float calibration_factor =     ;
const int motorPin = 9; // motor is connected to pin 7
HX711 scale;//for the library i have downloaded there is no declaration of data input pins
//initialize data pins
const int BUTTON = 7;
const int data1 = A0;//analog pins
const int data2 = A1;
// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = A0;
const int LOADCELL_SCK_PIN = A1;
float weight_now = 0.0 ;
float weight_prev = 0.0 ;
float weight_before=0.0;
int val = 0;//setting a variable for the pushbutton to store its values in
int val_new = 0; //setting a variable for the push button to store its new values in

void setup() {
  pinMode(motorPin, OUTPUT); // motor pin is an output
  Serial.begin(9600);//begin serial connection
  scale.begin(A0, A1);//begin connection with load cell through pins A0 and A1
  scale.set_scale();//set the scale
  scale.tare();  //Reset the scale to 0
  lcd.begin(16, 2);//set the lcd display
  lcd.clear();//clear the lcd display of all messages
  long zero_factor = scale.read_average(); //Get a baseline reading
  lcd.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  lcd.print(zero_factor);
  delay(1000);
}

void loop()
{
  for (int i = 0; i <    ; i++)
    while (i <   ) {
      while (val < 1) {
        lcd.print("Press button");
        val_new = digitalRead(BUTTON);
        val = val_new;
        delay(750);
        lcd.clear();
      }
      lcd.print("pot#...");
      //lcd.print("Pot Number");
      Serial.print(i + 1);
      Serial.print(",");
      lcd.print(i + 1);
      delay(2000);
      lcd.clear();
      lcd.print("ref weight");
     // Serial.print("Reference Weight");
      int myRefs[  ] = {     };
      int REF = myRefs[i];
      //Serial.print(myRefs[i]);
      lcd.print(myRefs[i]);
      delay(2000);
      lcd.clear();
      i++;
      delay(1000);
      lcd.setCursor(0, 0); // Sets the cursor at col 0 and row 0
      scale.set_scale(calibration_factor); //Adjust to this calibration factor
      lcd.print("Weight(g) ");
      weight_now = scale.get_units();
      weight_before=scale.get_units();
      //Serial.print("Weight before");
      Serial.print(weight_before);
      Serial.print(",");
      //
      //Serial.println(weight_before);
      lcd.print(weight_now);
      //Serial.print("Weight(g)");
      //Serial.print(weight_now);
      delay(2000);
      lcd.clear();

      while (weight_now < REF) {
            float a= REF-weight_now;
        float b= a/8;
        float c=750*b;
        if (a<10){
            lcd.print("Watering...");
            digitalWrite(motorPin, HIGH); // turn the motor on (full speed)
            //2000ms is approx 10 grams (this is an underestimate)
            delay(1000); // wait (delay) for this many milliseconds
            digitalWrite(motorPin, LOW); // turn the motor off
            delay(3000); // wait (delay) for this many milliseconds
            lcd.clear();
            }
        if (a>10){
                 lcd.print("Watering...");
                 digitalWrite(motorPin, HIGH); // turn the motor on (full speed)
                 //2000ms is approx 10 grams (this is an underestimate)
                 delay(c); // wait (delay) for this many milliseconds
                 digitalWrite(motorPin, LOW); // turn the motor off
                 delay(3000); // wait (delay) for this many milliseconds
                  lcd.clear();
                  }
        lcd.print("Wt ");
        weight_prev = scale.get_units();
        lcd.print(weight_prev);
        delay(2000);
        lcd.clear();
        weight_now = weight_prev;
      }
       //Serial.print("Final WT");
      Serial.println(weight_now);
      lcd.print("Next pot...");
      delay(4000);
      lcd.clear();
      val = 0;

    }
}
