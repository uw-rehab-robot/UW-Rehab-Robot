#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include "common.h"
#include <SPI.h>
#include <Wire.h>

/*
 * This will test the ultrasound and display the time it took to reach out and interact
 */

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);
unsigned long time;
long duration;
int distance;
unsigned long elapsed;
unsigned long activateTime;
int isFirst = 1;

void setup() {

  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);

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

  byte distance = runUltrasound();
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("distance (in): ");
  display.print(distance);
  display.display();

  time = millis();

  //delay(100);
  if (distance <= 10) {
    //printDisplay(time);
    //exit(1);
  }


}

byte runUltrasound() {
  

  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  duration = pulseIn(echo, HIGH);

  distance = duration * 0.034 / 2;

  // convert the time into a distance
  return byte(distance);
}

void printStart() {

    display.clearDisplay(); 
    display.setCursor(0, 0);
    display.println("Interact");
    display.display();
}

void printDisplay(float duration) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("distance (cm): ");
  display.print(distance);
  display.display();

  delay(3000);
}
