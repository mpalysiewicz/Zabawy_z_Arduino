#include "DHT.h"
#include <LiquidCrystal.h>
DHT dht;

LiquidCrystal lcd (12, 11, 5, 4, 3, 2);
void setup()
{
  Serial.begin(9600);
  Serial.println();
  Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)");

  dht.setup(7);
  lcd.begin(16,2);
}

void loop()
{ 
  delay(dht.getMinimumSamplingPeriod());

  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();

  Serial.print(dht.getStatusString());
  Serial.print("\t");
  Serial.print(humidity, 1);
  Serial.print("\t\t");
  Serial.print(temperature, 1);
  Serial.print("\t\t");
  Serial.println(dht.toFahrenheit(temperature), 1);

  lcd.setCursor(1, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" st. C");
  lcd.setCursor(1, 1);
  lcd.print("Hum: ");
  lcd.print(humidity);
  lcd.print(" %");

  
}
