/**************************************************************************
Line Sensor Example Code
**************************************************************************/
// Local Libraries
#include "line_sensor_class.h"

// Variables
uint8_t lineSensors, lineDetectCount;  // Used to temporarily store IR (line) sensor values


// Class Instantiation
line_sensor_class lineSensor;



void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
}

void loop() {
    lineSensors    = lineSensor.read_line();
    lineDetectCount = lineSensor.count_line_detects(lineSensors);
    Serial.println(lineDetectCount);
    Serial.println(lineSensors);
    /*for(int i = 0; i < 5; i++){
        
        Serial.print(" ");
    }
    Serial.println();  */
    delay(250);
}
