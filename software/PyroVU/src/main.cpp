
#include <Arduino.h>
// #include <Adafruit_SPIDevice.h>


#include "data_collection.h"
void findSPI();


// Define your CS and DREADY pins
#define CS_PIN 10
#define DREADY_PIN 14

DataCollection tempSensor(CS_PIN, DREADY_PIN);

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

}

void loop()
{
  float temperature = tempSensor.readTemperature();
  if (isnan(temperature))
  {
    Serial.println(tempSensor.getLastError());
  }
  else
  {
    Serial.print(">Temperature: ");
    Serial.println(temperature);
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