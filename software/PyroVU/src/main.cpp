
#include <Arduino.h>
// #include <Adafruit_SPIDevice.h>
#include <TM1637.h>

#include "data_collection.h"
void findSPI();
int mapTemperatureToValue(float temperature);
// Define your CS and DREADY pins
#define CS_PIN 10
#define DREADY_PIN 14

DataCollection tempSensor(CS_PIN, DREADY_PIN);

TM1637 tm(15, 16); // clkPin,  dataPin

void setup()
{
  Serial.begin(115200);
  Serial.println("Welcome to PyroVU");
  findSPI();

  // Initialize the sensor
  if (!tempSensor.begin())
  {
    Serial.println(tempSensor.getLastError());
    while (1)
      ;
  }
  tempSensor.setThermocoupleType(MAX31856_TCTYPE_K);
  Serial.println(tempSensor.readTemperature());

  // maxthermo.setConversionMode(MAX31856_CONTINUOUS);
  tm.begin();
  tm.setBrightnessPercent(70); // Display's brightness value between 0 and 100 percent
  tm.display("OK")->scrollLeft(1000);
}

void loop()
{
  tm.clearScreen();
  float temperature = tempSensor.readTemperature();
  if (isnan(temperature))
  {
    Serial.println(tempSensor.getLastError());
  }
  else
  {
    Serial.print(">Temperature: ");
    Serial.println(temperature);
    int value = mapTemperatureToValue(temperature);
    Serial.print(">Value: ");
    Serial.println(value);
    tm.setBrightnessPercent(value);
    tm.display(temperature);
  }

  delay(2000);
}

void findSPI() // pass by ref
{

  delay(2000);
  Serial.println("Default SPI pins for this board:");
  Serial.print("SS :");
  Serial.println(SS);
  Serial.print("MOSI : ");
  Serial.println(MOSI);
  Serial.print("bSCK :");
  Serial.println(SCK);
  Serial.print("MISO : ");
  Serial.println(MISO);
}

// void readTemperature()
// {
//   Serial.println("Reading temperature");
//   maxthermo.triggerOneShot();
//   delay(500); // replace this with whatever
//   // check for conversion complete and read temperature
//   if (maxthermo.conversionComplete())
//   {
//     Serial.println(maxthermo.readThermocoupleTemperature());
//   }
//   else
//   {
//     Serial.println("Conversion not complete!");
//   }
// }
// void redContTemparature()
// {
//   maxthermo.setConversionMode(MAX31856_CONTINUOUS);
//   Serial.println("Reading temperature with continuous mode");
//   // The DRDY output goes low when a new conversion result is available
//   int count = 0;
//   while (digitalRead(DRDY_PIN))
//   {
//     count++;
//     delay(10);
//     if (count > 100)
//     {
//       Serial.println("Timeout waiting for DRDY to go low!");
//       return;
//     }
//   }
//   Serial.println(maxthermo.readThermocoupleTemperature());
// }

int mapTemperatureToValue(float temperature)
{
  // Ensure temperature is within the expected range
  if (temperature < 27.0)
    temperature = 27.0;
  if (temperature > 34.0)
    temperature = 34.0;

  // Map the temperature to a value from 10 to 100
  int value = (int)((temperature - 27.0) / 7.0 * 90.0) + 10;

  // Round to the nearest multiple of 10
  value = (value + 5) / 10 * 10;

  return value;
}