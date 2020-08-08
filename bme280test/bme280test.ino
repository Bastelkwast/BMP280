#include <Wire.h>
#include "cactus_io_BME280_I2C.h"

BME280_I2C bme(0x76); // I2C using address 0x76

void setup() {
Serial.begin(9600);
Serial.println("BME280 Luftdruck, Luftfeuchtigkeit, Temperatur Sensor | cactus.io");
Serial.println("—————————————————————–");
Serial.println("");

if (!bme.begin()) {
Serial.println("Es konnte kein BME280 Sensor gefunden werden!");
Serial.println("Bitte überprüfen Sie die Verkabelung!");
while (1);
}

bme.setTempCal(-1);

Serial.println("Luftdruck\tLuftfeuchtigkeit\t\tTemperatur(Celsius)\t\tTemperatur(Fahrenheit)");
}

void loop() {
bme.readSensor();

Serial.print(bme.getPressure_MB()); Serial.print("\t\t"); // Pressure in millibars
Serial.print(bme.getHumidity()); Serial.print("%\t\t\t\t");
Serial.print(bme.getTemperature_C()); Serial.print(" °C\t\t\t");
Serial.print(bme.getTemperature_F()); Serial.println(" °F");

delay(2000);
}
