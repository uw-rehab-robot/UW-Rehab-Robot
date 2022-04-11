/**************************************************************************
Line Sensor Example Code
**************************************************************************/
// Local Libraries
#include "line_sensor_class.h"

// Variables
int lineSensorsAnalog[5];
uint8_t lineSensorsBinary, lineDetectCount;  // Used to temporarily store IR (line) sensor values


// Class Instantiation
line_sensor_class lineSensor;



void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
}

void loop() {
    lineSensor.get_sensors_analog(lineSensorsAnalog);
    lineSensorsBinary = lineSensor.read_line_binary();
    lineDetectCount   = lineSensor.count_line_detects(lineSensorsBinary);
    Serial.print("Analog Values: ");
    for(int i=0; i<5; i++)
    {
        Serial.print(lineSensorsAnalog[i]);
        Serial.print(" ");
    }
    Serial.println();
    Serial.print("Binary Values: ");
    Serial.print(lineSensorsBinary);
    Serial.println();
    Serial.print("Line Detections: ");
    Serial.print(lineDetectCount);
    Serial.println();
    delay(250); // Delay 1/4 second between measurements
}
