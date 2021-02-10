/*******************************************************************************
* Line Following Library
*
* File name:    line_following_class.h
*
*
*******************************************************************************/
#ifndef line_following_class_h
    #define line_following_class_h

    // System Libraries
    // This is the library for the TB6612 that contains the class Motor and all the functions
    #include <SparkFun_TB6612.h>

    // Local Libraries
    #include "src/line_sensor/line_sensor_class.h"

    // Definitions

    // Class Declaration
    class line_following_class
    {
        // Variables and Functions not accessible outside of class
        private:
            // Variables
            long previousMillis = 0;    // Used to store previous loop time

            // Functions
            void set_motors(int leftMotorSpeed, int rightMotorSpeed);
            void rotate_acute(uint8_t side);
            void rotate(uint8_t side);
            void straight_lines(uint8_t binary);
            void angles(uint8_t binary);
        
        // Variables and Functions accessible outside of class
        public:
            // Functions
            // TO ADD: calibrate_line();
            void follow_line(int duration);
    };
#endif
