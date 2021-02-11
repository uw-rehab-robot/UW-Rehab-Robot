#include "Arduino.h"
#include "line_sensor_class.h"

// Local Variables
//Analog
//sensor pins, reflects current wiring (01/28/2021)
int farLeftSensor       = 20;
int middleLeftSensor    = 19;
int centerSensor        = 18;
int middleRightSensor   = 17;
int farRightSensor      = 16;
const int IRSensor[] = {farLeftSensor, middleLeftSensor, centerSensor, middleRightSensor, farRightSensor};

// Global Functions
//  Reads analog values from the sensors into an array
void line_sensor_class::get_sensors_analog(int *sensorValues, int numberOfSensors)
{
    // Run for every sensor position (left to right)
    for(int i=0; i<numberOfSensors; i++)
    {
        // Read sensor value
        sensorValues[i] = analogRead(IRSensor[i]);
    }
}

uint8_t line_sensor_class::read_line_binary(int minThreshold)
{
    int sensorVal;
    uint8_t lineDetects=0, bitmask=0b10000000;
    // Run for every sensor position (left to right)
    for(int i=0; i<5; i++)
    {
        // Read sensor value
        sensorVal = analogRead(IRSensor[i]);
        // Check if larger than line detect threshold
        if (sensorVal > minThreshold)
        {
            lineDetects |= bitmask;
        }
        else
        {
            lineDetects |= 0;
        }
        bitmask = bitmask>>1;
    }
    return lineDetects;
}


/*  Counts and returns the number of sensors that are over the line.
 */
uint8_t line_sensor_class::count_line_detects(uint8_t lineDetects)
{
  uint8_t bitmask=0b10000000, lineDetectCount=0;  
  for(uint8_t i=0; i<5; i++)
  {
    if(lineDetects & bitmask)
      lineDetectCount++;
    bitmask = bitmask>>1;
  }
  return lineDetectCount;
}
