// System Libraries
#include "Arduino.h"

// Local Libraries
#include "line_following_class.h"

// Class Instantiations
line_sensor_class lineSensor;

// Local Variables
// These constants are used to allow you to make your motor configuration line up with function names like forward.
// Values can be 1 or -1 depending on polarity of motor driver connections to the motors
// As of 02/09/21
const int offsetA = -1;
const int offsetB = 1;
uint8_t lineSensors, lineDetectCount;   // Used to temporarily store IR (line) sensor values
uint8_t leftMotorSpeed = 0;             // Used to keep track of motor speed last state
uint8_t rightMotorSpeed = 0;            // Used to keep track of motor speed last state

// Motor Driver Pins (As of 02/09/21)
#define MD_AIN1_PIN     6
#define MD_BIN1_PIN     4
#define MD_AIN2_PIN     7
#define MD_BIN2_PIN     3
#define MD_PWMA_PIN     8
#define MD_PWMB_PIN     2
#define MD_STBY_PIN     5

#define LEFT            0
#define RIGHT           1
#define ROTATE_SPEED    100
#define MAXSPEED        400


// Initializing motors.  The library will allow you to initialize as many
// motors as you have memory for.  If you are using functions like forward
// that take 2 motors as arguements you can either write new functions or
// call the function more than once.
Motor leftMotor   = Motor(MD_AIN1_PIN, MD_AIN2_PIN, MD_PWMA_PIN, offsetA, MD_STBY_PIN);
Motor rightMotor  = Motor(MD_BIN1_PIN, MD_BIN2_PIN, MD_PWMB_PIN, offsetB, MD_STBY_PIN);


void line_following_class::set_motors(int leftMotorValue, int rightMotorValue)
{
    leftMotorSpeed = leftMotorValue;
    rightMotorSpeed = rightMotorValue;
    leftMotor.drive(leftMotorValue);
    rightMotor.drive(rightMotorValue);
}

// Global Functions
void line_following_class::straight_lines(uint8_t binary)
{
    uint8_t binaryCount = lineSensor.count_line_detects(binary);
    switch(binaryCount)
    {
        // There is no line detected
        case 0:
            // Do Nothing
        
        // There was only a single diode detect
        case 1:
            // Hard Right (Only using top 5 bits)
            if(binary == 0b00001000)
                set_motors((1.00 * MAXSPEED), (-1.00 * MAXSPEED));

            // Right (Only using top 5 bits)
            else if (binary == 0b00010000)
                set_motors((0.80 * MAXSPEED), (-0.30 * MAXSPEED));

            // Straight
            else if (binary == 0b00100000)
                set_motors((0.50 * MAXSPEED), (0.50 * MAXSPEED));

            // Left
            else if (binary == 0b01000000)
                set_motors((-0.30 * MAXSPEED), (0.80 * MAXSPEED));
            
            // Hard Left
            else if(binary == 0b10000000)
                set_motors((-1.00 * MAXSPEED), (1.00 * MAXSPEED));
            break;

        // There were two diode detects, check for straight lines
        case 2:
            // Right (Only using top 5 bits)
            if(binary == 0b00011000)
                set_motors((0.90 * MAXSPEED), (-0.60 * MAXSPEED));

            // Right (Only using top 5 bits)
            else if(binary == 0b00110000)
                set_motors((0.60 * MAXSPEED), (0.10 * MAXSPEED));

            // Left (Only using top 5 bits)
            else if(binary == 0b01100000)
                set_motors((0.10 * MAXSPEED), (0.60 * MAXSPEED));

            // Left (Only using top 5 bits)
            else if(binary == 0b11000000)
                set_motors((-0.60 * MAXSPEED), (0.90 * MAXSPEED));

        // There were three diode detects, check for straight lines
        case 3:
            // Right (Only using top 5 bits)
            if(binary == 0b00111000)
                set_motors((0.80 * MAXSPEED), (-0.30 * MAXSPEED));

            // Straight (Only using top 5 bits)
            else if(binary == 0b01110000)
                set_motors((0.30 * MAXSPEED), (0.30 * MAXSPEED));

            // Left (Only using top 5 bits)
            else if(binary == 0b11100000)
                set_motors((-0.30 * MAXSPEED), (0.80 * MAXSPEED));

        // There were four diode detects, check for straight lines
        case 4:
            // Right (Only using top 5 bits)
            if(binary == 0b01111000)
              set_motors((0.50 * MAXSPEED), (0.00 * MAXSPEED));

            // Left (Only using top 5 bits)
            else if (binary == 0b11110)
              set_motors((0.00 * MAXSPEED), (0.50 * MAXSPEED));
    }
}

void line_following_class::rotate_acute(uint8_t side)
{
    uint8_t binary;
    do
    {
        // Sample line sensors
        binary = lineSensor.read_line_binary();

        // Check if not actually an acute angle
        if((side == LEFT && (binary & 0b00001000)) || (side == RIGHT && (binary & 0b10000000)))
            return;

        //Follow the line until the middle sensor is off the line.
        straight_lines(binary);
    } while(binary & 0b00100000);

    if(side == RIGHT)
        right(leftMotor, rightMotor, ROTATE_SPEED);
    else
        left(leftMotor, rightMotor, ROTATE_SPEED);

    // Rotate until the the middle sensor is on? the line.
    while(binary & 0b00100000)
    {
        binary = lineSensor.read_line_binary();
    }
}

void line_following_class::rotate(uint8_t side)
{
    uint8_t binary;
    do
    {
        // Sample line sensors
        binary = lineSensor.read_line_binary();
        if(side == RIGHT)
            right(leftMotor, rightMotor, ROTATE_SPEED);
        else
            left(leftMotor, rightMotor, ROTATE_SPEED);
    } while(not(binary & 0b00100000));
}

void line_following_class::angles(uint8_t binary)
{
    uint8_t binaryCount = lineSensor.count_line_detects(binary);
    switch(binaryCount)
    {
        // There were two diode detects, check for acute angles
        case 2:
            // Acute Right Turn
            if(binary == 0b00101000)
                rotate_acute(RIGHT);
  
            // Acute Right Turn
            else if (binary == 0b01001000)
                rotate_acute(RIGHT);
  
            // Acute Left Turn
            else if (binary == 0b10010000)
                rotate_acute(LEFT);
  
            // Acute Left Turn
            else if (binary == 0b10100000)
                rotate_acute(LEFT);

        // There were thtree diode detects, check for acute and 90 degree angles
        case 3:
            if (binary == 0b01011000)
                rotate_acute(RIGHT);
  
            // Acute Right Turn
            else if (binary == 0b01101000)
                rotate_acute(RIGHT);
  
            // Acute Left Turn
            else if (binary == 0b10110000)
                rotate_acute(LEFT);
  
            // Acute Left Turn
            else if (binary == 0b11010000)
                rotate_acute(LEFT);

        // There were four diode detects, check for acute angles and 90 degree angles
        case 4:        
            // Acute Left Turn
            if (binary == 0b10111000)
                rotate_acute(LEFT);

            // Acute Right Turn
            else if (binary == 0b11101000)
                rotate_acute(RIGHT);
    }
}


void line_following_class::follow_line(int duration)
{
    // Initialize timer
    unsigned long currentMillis = millis();
    previousMillis = currentMillis;

    // Loop until duration is hit
    while(currentMillis - previousMillis < duration)
    {
        // Check sensors
        lineSensors    = lineSensor.read_line_binary();
        // Count sensors over the line
        lineDetectCount = lineSensor.count_line_detects(lineSensors);
        Serial.print(lineDetectCount);
        switch(lineDetectCount)
        {
            // Zero diode detections means loss of line
            case 0:
                // If motors were already moving, keep doing whatever was being done before to reaquire line
                if (leftMotorSpeed + rightMotorSpeed > 0)
                    set_motors(leftMotorSpeed, rightMotorSpeed);
                // Else motors were stationary, try rotating left to find the edge of the line
                else
                    rotate(LEFT);
                break;
            
            // Single diode detection must mean straight line
            case 1:
                straight_lines(lineSensors);
                break;

            // Two diode detections, could large straight line or acute angle
            case 2:
                // Try for straight lines first
                straight_lines(lineSensors);
                // Now check if it's an angle
                angles(lineSensors);
                break;

            // Three diode detections, could large straight line or acute angle
            case 3:
                // Try for straight lines first
                straight_lines(lineSensors);
                // Now check if it's an angle
                angles(lineSensors);
                break;

            // Four diode detections, don't change anything
            case 4:
                // Try for straight lines first
                straight_lines(lineSensors);
                // Now check if it's an angle
                angles(lineSensors);
                break;

            case 5:
                // Try rotating left to find the edge of the line
                rotate(LEFT);
                break;            
        }
        // Update current time
        currentMillis = millis();
    }
    
    // Done following line, stop robot. Don't use set_motors() to preserve motor speed last state
    leftMotor.drive(0);
    rightMotor.drive(0);
}
