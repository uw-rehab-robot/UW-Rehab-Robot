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
uint8_t line_sensor_class::read_line(int minThreshold)
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
uint8_t line_sensor_class::count_line_detects(uint8_t sensorValues)
{
  uint8_t bitmask=0b10000000, binaryCount=0;  
  for(uint8_t i=0; i<5; i++)
  {
    if(sensorValues & bitmask)
      binaryCount++;
    bitmask = bitmask>>1;
  }
  return binaryCount;
}
