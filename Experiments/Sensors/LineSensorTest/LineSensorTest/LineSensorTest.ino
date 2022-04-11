/**************************************************************************
Line Sensor Example Code
**************************************************************************/
// Local Libraries
#include "line_sensor_class.h"

// Variables
int *tempData;  // Used to temporarily store IR (line) sensor values

// Class Instantiation
line_sensor_class lineSensor;



void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
}

void loop() {
    tempData = lineSensor.read_line();
    
    for(int i = 0; i < 5; i++){
        Serial.print(tempData[i]);
        Serial.print(" ");
    }
    Serial.println();  
    delay(250);
}
