/*******************************************************************************
* Line Following Sensor Library
*
* File name:    line_sensor_class.h
*
*
*******************************************************************************/


#ifndef line_sensor_class_h
    #define line_sensor_class_h

    // System Libraries

    // Local Libraries

    // Definitions
    // Default value used without calibration (TBA)
    #define minDetectThreshold 900

    // Class Declaration
    class line_sensor_class
    {
        // Variables and Functions accessible outside of class
        public:
            // Functions
            // TO ADD: calibrate_line();
            uint8_t read_line(int minThreshold=minDetectThreshold);
            uint8_t count_line_detects(uint8_t sensorValues);
    };
#endif
