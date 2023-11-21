//Header declaration Start
#include <OneWire.h> // One wire library
#include <DallasTemperature.h> // Library for DS18B20 Sensor
#include <math.h> // Library for math function 
//Header Declaration End

//Pin Assignment and declaration Start
#define ONE_WIRE_BUS 5 //data pin DQ pin of DS18B20 connected to digital pin D5

OneWire oneWire(ONE_WIRE_BUS); // Set up one wire instance
DallasTemperature sensors(&oneWire); // pass one wire reference to DS18B20 library

long phTot;
float phAvg;
int x;
const float C = 21.34; // Constant of straight line (Y = mx + C)
const float m = -5.70; // Slope of straight line (Y = mx + C)
const float calibrationOffset = 5.0; // Calibration offset to adjust pH readings
//Pin Assignment and declaration end

//Setup Function Start 
void setup() {
  Serial.begin(9600); // Initialize serial communication
  sensors.begin(); // Start the DS18B20 Library
}
//Setup Function End

//Main function Start
void loop() {
  phTot = 0;
  phAvg = 0;

  //taking 10 samples and adding with 10 milliseconds delay
  for (x = 0; x < 10; x++) {
    int analogValue = analogRead(A0);
    phTot += analogValue;
    Serial.print("Analog Value: ");
    Serial.println(analogValue);
    delay(10);
  }

  float phAvg = phTot / 10;
  float phVoltage = phAvg * (5.0 / 1023.0); //convert sensor reading into millivolt
  float pHValue = phVoltage * m + C + calibrationOffset; // Adjusted for calibration

  Serial.print("Adjusted PH Value of Solution: ");
  Serial.print(pHValue);
  Serial.println(" PH");

  delay(1000);
}
