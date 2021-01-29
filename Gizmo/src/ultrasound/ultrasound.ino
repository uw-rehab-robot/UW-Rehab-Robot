#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include "ultrasound_class.h"
#include <SPI.h>
#include <Wire.h>


ultrasound_class ultrasound;

/*
 * This will test the ultrasound and display the time it took to reach out and interact
 */

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);
unsigned long time;
unsigned long elapsed;
unsigned long activateTime;
int isFirst = 1;

void setup() {

  ultrasound.ultrasound_setup();

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // begins display, displays arduino logo by default
  display.clearDisplay(); //This will clear the adafruit logo

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  display.print("Starting");
  display.display();
  delay(3000);
  display.clearDisplay();
}

void loop() {

  byte distance = ultrasound.runUltrasound();
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("distance (cm): ");
  display.print(distance);
  display.display();

  time = millis();

  //delay(100);
  if (distance <= 10) {
    //printDisplay(time);
    //exit(1);
  }


}
