#include "Arduino.h"
#include "ultrasound_class.h"

// Local Variables
int     triggerPin  = 0;
int     echoPin     = 21;
long    duration;
int     distance;

// Global Functions
// Class Functions
byte ultrasound_class::runUltrasound()
{
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);

    duration = pulseIn(echoPin, HIGH);

    distance = duration * 0.034 / 2;

    // convert the time into a distance
    return byte(distance);
}

// Class Functions
void ultrasound_class::ultrasound_setup()
{
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
}
