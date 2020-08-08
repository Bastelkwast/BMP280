/*
  Das ist ein Beispiel um ein OLED 128x64 I2C mit SSD1306 Treiber in verbindung mit einem 
  BME280 I2C anzusteuern

  Pins:
   GND = GND
   VCC = 3,3V
   SCL = A5
   SDA = A4

  Benötigte Libraries:
  https://github.com/adafruit/Adafruit_SSD1306
  https://github.com/adafruit/Adafruit-GFX-Library
  http://cactus.io/hookups/sensors/barometric/bme280/hookup-arduino-to-bme280-barometric-pressure-sensor

  List of fonts that support right alignment:
  FreeMono9pt7b.h
  FreeMono12pt7b.h
  FreeMono18pt7b.h
  FreeMono24pt7b.h
  FreeMonoBold9pt7b.h
  FreeMonoBold12pt7b.h
  FreeMonoBold18pt7b.h
  FreeMonoBold24pt7b.h
  FreeMonoBoldOblique9pt7b.h
  FreeMonoBoldOblique12pt7b.h
  FreeMonoBoldOblique18pt7b.h
  FreeMonoBoldOblique24pt7b.h
  FreeMonoOblique9pt7b.h
  FreeMonoOblique12pt7b.h
  FreeMonoOblique18pt7b.h
  FreeMonoOblique24pt7b.h

*/

#include <Adafruit_GFX.h>  // Include core graphics library for the display
#include <Adafruit_SSD1306.h>  // Include Adafruit_SSD1306 library to drive the display
#include <Wire.h>
#include "cactus_io_BME280_I2C.h"

BME280_I2C bme(0x76); // I2C using address 0x76

Adafruit_SSD1306 display(128, 64);  // Create display

#include <Fonts/FreeMonoBold9pt7b.h>  // Add a custom font
#include <Fonts/FreeMono9pt7b.h>  // Add a custom font

void setup()  // Start of setup
{
  delay(100);  // This delay is needed to let the display to initialize

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // Initialize display with the I2C address of 0x3C

  display.clearDisplay();  // Clear the buffer

  display.setTextColor(WHITE);  // Set color of the text

  display.setRotation(0);  // Set orientation. Goes from 0, 1, 2 or 3

  display.setTextWrap(false);  // By default, long lines of text are set to automatically “wrap” back to the leftmost column.
  // To override this behavior (so text will run off the right side of the display - useful for
  // scrolling marquee effects), use setTextWrap(false). The normal wrapping behavior is restored
  // with setTextWrap(true).

  display.dim(0);  //Set brightness (0 is maximun and 1 is a little dim)


  if (!bme.begin()) {
    Serial.println("Es konnte kein BME280 Sensor gefunden werden!");
    Serial.println("Bitte überprüfen Sie die Verkabelung!");
    while (1);
  }

  bme.setTempCal(-1);
  delay(100);  // This delay is needed to let the display to initialize
}  // End of setup

void loop()  // Start of loop
{
  bme.readSensor();

  display.clearDisplay();  // Clear the display so we can refresh
  display.setFont(&FreeMonoBold9pt7b);  // Set a custom font
  display.setTextSize(0);  // Set text size. We are using a custom font so you should always use the text size of 0

  // Print text:
  display.setCursor(0, 20);  // (x,y)
  display.print("Temp: ");  // Text or value to print
  display.setCursor(60, 20);  // (x,y)
  display.print(bme.getTemperature_C());
  display.setCursor(0, 40);  // (x,y)
  display.print("Hum:  ");
  display.setCursor(60, 40);  // (x,y)
  display.print(bme.getHumidity());

  display.display();  // Print everything we set previously

delay (2000);

}  // End of loop
