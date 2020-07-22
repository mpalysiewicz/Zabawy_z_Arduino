#include "Wire.h"       //For communicate
#include <ADXL345.h>

ADXL345 accelerometer;

int ledPin = 13;
int buzzerPin = 6;
int gndPin = 3;

int ledTreshold = 15;
int buzzerTreshold = 30;

void setup() {
  pinMode(gndPin, OUTPUT);
  digitalWrite(gndPin, LOW);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin,OUTPUT);
  Serial.begin(9600);
  Wire.begin();
  
  // Initialize ADXL345
  Serial.println("Initialize ADXL345");

  if (!accelerometer.begin())
  {
    Serial.println("Could not find a valid ADXL345 sensor, check wiring!");
    delay(500);
  }

  // Set measurement range
  // +/-  2G: ADXL345_RANGE_2G
  // +/-  4G: ADXL345_RANGE_4G
  // +/-  8G: ADXL345_RANGE_8G
  // +/- 16G: ADXL345_RANGE_16G
  accelerometer.setRange(ADXL345_RANGE_16G);
}

void loop() {
  // Read normalized values
  Vector norm = accelerometer.readNormalize();
  
  // Low Pass Filter to smooth out data. 0.1 - 0.9
  Vector filtered = accelerometer.lowPassFilter(norm, 0.5);

    // Calculate Pitch & Roll (Low Pass Filter)
  int fpitch = -(atan2(filtered.XAxis, sqrt(filtered.YAxis*filtered.YAxis + filtered.ZAxis*filtered.ZAxis))*180.0)/M_PI;
  int froll  = (atan2(filtered.YAxis, filtered.ZAxis)*180.0)/M_PI;

  boolean shakey = (fpitch > ledTreshold || (fpitch * -1) > ledTreshold || froll > ledTreshold || (froll * -1) > ledTreshold);
  boolean lost = (fpitch > buzzerTreshold || (fpitch * -1) > buzzerTreshold || froll > buzzerTreshold || (froll * -1) > buzzerTreshold);
  Serial.print(" (filter)Pitch = ");
  Serial.print(fpitch);
  Serial.print(" (filter)Roll = ");
  Serial.print(froll);
  Serial.println();
  
  digitalWrite(ledPin, shakey);

  if(lost){
    tone(buzzerPin, 400);
    delay(3000);
  }else{
    noTone(buzzerPin);
  }

  delay(100);
}
