/*code adappted from Playground, crickit, sparks fun examples
*/
#include <Adafruit_CircuitPlayground.h>
#include "Adafruit_Crickit.h"
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_CircuitPlayground.h>

Adafruit_Crickit crickit;
#define PWM CRICKIT_SIGNAL3
int sensorValue = 0; //value for storing moisture value 
int voltage = 0;
int soilPin = A2;//Declare a variable for the soil moisture sensor 
int soilPower = A3;//Variable for Soil moisture Power

//Rather than powering the sensor through the 3.3V or 5V pins, 
//we'll use a digital pin to power the sensor. This will 
//prevent corrosion of the sensor as it sits in the soil. 

void setup() 
{
  //initiate serial port connection
  Serial.begin(9600);   // open serial over USB
  pinMode(soilPower, OUTPUT);//Set D7 as an OUTPUT
  digitalWrite(soilPower, LOW);//Set to LOW so no power is flowing through the sensor
}


//start loop
void loop() {
  // put your main code here, to run repeatedly:

int sensorValue = readSoil();
float voltage = sensorValue * (3.3 / 1023.0);
Serial.println(voltage);

}

//read soil function for getting a sensor reading
int readSoil()
{

    digitalWrite(soilPower, HIGH);//turn D7 "On"

    sensorValue = analogRead(soilPin);//Read the SIG value form sensor 
    delay(100);
    digitalWrite(soilPower, LOW);//turn D7 "Off"
    return sensorValue;//send current moisture value
    }
