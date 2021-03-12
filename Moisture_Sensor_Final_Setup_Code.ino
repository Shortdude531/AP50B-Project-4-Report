/*code adappted from Playground, crickit, sparks fun examples

*/

#include <Adafruit_CircuitPlayground.h>
#include "Adafruit_Crickit.h"
#include <Wire.h>
#include <SPI.h>
#include "seesaw_motor.h"

Adafruit_Crickit crickit;
#define LED_1 CRICKIT_SIGNAL3
int sensorValue = 0; //value for storing moisture value 
int voltage = 0;
int soilPin = A2;//Declare a variable for the soil moisture sensor 
int soilPower = A3;//Variable for Soil moisture Power
seesaw_Motor motor_a(&crickit); //inialize dc motor'

//Rather than powering the sensor through the 3.3V or 5V pins, 
//we'll use a digital pin to power the sensor. This will 
//prevent corrosion of the sensor as it sits in the soil. 
#include <Adafruit_CircuitPlayground.h>
void setup() 
{
  Serial.begin(9600);   // open serial over USB
  pinMode(soilPower, OUTPUT);//Set D7 as an OUTPUT
  digitalWrite(soilPower, LOW);//Set to LOW so no power is flowing through the sensor
}

void loop() 
{
  //delay
  delay(1000);//take a reading every second to prevent Corrosion
  Serial.begin(9600);

  int sensorValue = readSoil();
  //converts soil reading to voltage
  float voltage = sensorValue * (3.3 / 1023.0);
  Serial.println(voltage);
  delay(100);
  
    //initiates CircuitPlayground
    CircuitPlayground.begin();
    //edit leds on playground
    CircuitPlayground.strip.setBrightness(140);

    //if the soil is saturated with water
    if (voltage >= 2.3) {
       //Edits the color of the LEDs to green to indicate there is plenty of water
       for (int i=0; i<10; ++i) {
        CircuitPlayground.strip.setPixelColor(i, 0, 255, 0);
        }
      //Shows LEDs
      CircuitPlayground.strip.show();
    
      //initiates crickit
      crickit.begin();
      
      //turns on growing lights
      crickit.pinMode(LED_1, OUTPUT);
      crickit.digitalWrite(LED_1, HIGH);
    }

    //if the soild is drying out
    if (voltage < 2.3 && voltage > .6) {
       //Edits the color of the LEDs to yellow indicating the soil is drying out
       for (int i=0; i<10; ++i) {
        CircuitPlayground.strip.setPixelColor(i, 255, 255, 0);
       }
       //Shows LEDs
       CircuitPlayground.strip.show();

      //initiates crickit  
      crickit.begin();
      //turns the growing lights off to preserve water
      crickit.pinMode(LED_1, OUTPUT);
      crickit.digitalWrite(LED_1, LOW);
    }

    //if there is not enough water
    if (voltage < .59) {
       //changes the LED lights on the playground to Red indicating not enough water
       for (int i=0; i<10; ++i) {
          CircuitPlayground.strip.setPixelColor(i, 255, 0, 0);
        }
        CircuitPlayground.strip.show();

        //plays alarm when water level is critical
        CircuitPlayground.playTone(500, 100); 
        //initiates crickit
        crickit.begin();
        //turns growing lights off
        crickit.pinMode(LED_1, OUTPUT);
        crickit.digitalWrite(LED_1, LOW);  
        //start watering cycle using servo motor
        motor_a.attach(CRICKIT_MOTOR_A1, CRICKIT_MOTOR_A2);
        motor_a.throttle(-.5);
        delay(500);
        motor_a.throttle(0);
      }   
    }
//This is a function used to get the soil moisture content from sparks fun code
int readSoil()
{

    digitalWrite(soilPower, HIGH);//turn D7 "On"

    sensorValue = analogRead(soilPin);//Read the SIG value form sensor 
    delay(100);
    digitalWrite(soilPower, LOW);//turn D7 "Off"
    return sensorValue;//send current moisture value
    }
