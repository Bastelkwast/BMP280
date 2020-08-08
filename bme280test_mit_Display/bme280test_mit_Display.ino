#include <Wire.h>
#include "cactus_io_BME280_I2C.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

BME280_I2C bme(0x76); // I2C using address 0x76

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     LED_BUILTIN //4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
Serial.begin(9600);
Serial.println("BME280 Luftdruck, Luftfeuchtigkeit, Temperatur Sensor | cactus.io");
Serial.println("—————————————————————–");
Serial.println("");



// SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  // Draw a single pixel in white
  display.drawPixel(10, 10, SSD1306_WHITE);

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();
  delay(2000);
  // display.display() is NOT necessary after every single drawing command,
  // unless that's what you want...rather, you can batch up a bunch of
  // drawing operations and then update the screen all at once by calling
  // display.display(). These examples demonstrate both approaches...

  display.setTextColor(WHITE);
  display.setTextSize(5);


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

display.setCursor(83, 20);    // (x,y)
display.println(bme.getHumidity()); // Text or value to print

delay(2000);
}
