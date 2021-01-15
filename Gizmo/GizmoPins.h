#pragma once
namespace PINS {

/*
|Arduino Pins   |Project Function   |Project Pin Name   |Usage Location                             |
|---------------------------------------------------------------------------------------------------|
|~D0/RXI-1      |Ultrasound Trigger |TBD                |TBD                                        |
|~D1/TXO-1      |UNUSED             |UNUSED             |UNUSED                                     |
|~D2/A6         |Motor Driver PWMB  |TBD                |TBD                                        |
|~D3            |Motor Driver BIN2  |TBD                |TBD                                        |
|~D4            |Motor Driver BIN1  |TBD                |TBD                                        |
|~D5            |Motor Driver STBY  |TBD                |TBD                                        |
|~D6            |Motor Driver AIN1  |TBD                |TBD                                        |
|~D7            |Motor Driver AIN2  |TBD                |TBD                                        |
|~D8/A8         |Motor Driver PWMA  |TBD                |TBD                                        |
|~D9/A9         |Buzzer             |buzzer_pin         |src/buzzer/buzzer_functions.cpp            |
|~D10/A10       |SD Card CS         |TBD                |TBD                                        |
|~D11/MOSI      |SD Card MOSI       |TBD                |TBD                                        |
|~D12/MISO      |SD Card MISO       |TBD                |TBD                                        |
|~D13/SCK       |SD Card SCK        |TBD                |TBD                                        |
|D14/SDA        |OLED SDA           |U8G2_R0            |src/oled_screen/oled_screen_functions.cpp  |
|~D15/SCL       |OLED SCL           |U8G2_R0            |src/oled_screen/oled_screen_functions.cpp  |
|~D16/A0        |IR Sensor 5 OUT    |TBD                |TBD                                        |
|~D17/A1        |IR Sensor 4 OUT    |TBD                |TBD                                        |
|D18/A2         |IR Sensor 3 OUT    |TBD                |TBD                                        |
|~D19/A3        |IR Sensor 2 OUT    |TBD                |TBD                                        |
|D20/A4         |IR Sensor 1 OUT    |TBD                |TBD                                        |
|~D21/A5        |Ultrasound Echo    |TBD                |TBD                                        |
|D24/TP12       |UNUSED             |UNUSED             |UNUSED                                     |
|D25/TP13       |UNUSED             |UNUSED             |UNUSED                                     |
|D26/TP14       |UNUSED             |UNUSED             |UNUSED                                     |
|D27/TP11       |UNUSED             |UNUSED             |UNUSED                                     |
|~D28/TP9       |User Button        |uiButtonPin        |src/ui_button/ui_button_functions.cpp      |
|~D29/TP8       |UNUSED             |UNUSED             |UNUSED                                     |
|---------------------------------------------------------------------------------------------------|
*/

//----------------------------------------------//
// Digital Pins
//----------------------------------------------//
// Ultrasound Trigger Pin
#define US_TRIGGER_PIN  0

// Motor Driver Pins
#define MD_AIN1_PIN     6
#define MD_BIN1_PIN     4
#define MD_AIN2_PIN     7
#define MD_BIN2_PIN     3
#define MD_PWMA_PIN     8
#define MD_PWMB_PIN     2
#define MD_STBY_PIN     5

// Passive Buzzer Pin
#define BUZZER_PIN      9

// SD Card Pins
#define SD_CS_PIN       10
#define SD_MOSI_PIN     11
#define SD_MISO_PIN     12
#define SD_SCK_PIN      13

// OLED Screen Pins
#define OLED_SDA_PIN    14
#define OLED_SCL_PIN    15

// User Interface Button Pin
#define UI_BUTTON_PIN   28

/* UNUSED Pins
#define TBD 1
#define TBD 24  // CURRENTLY UNCONNECTED SURFACE-MOUNT TEST POINT ON BOTTOM OF BOARD
#define TBD 25  // CURRENTLY UNCONNECTED SURFACE-MOUNT TEST POINT ON BOTTOM OF BOARD
#define TBD 26  // CURRENTLY UNCONNECTED SURFACE-MOUNT TEST POINT ON BOTTOM OF BOARD
#define TBD 27  // CURRENTLY UNCONNECTED SURFACE-MOUNT TEST POINT ON BOTTOM OF BOARD
#define TBD 29  // CURRENTLY UNCONNECTED SURFACE-MOUNT TEST POINT ON BOTTOM OF BOARD
*/

//----------------------------------------------//
// Analog Pins
//----------------------------------------------//
// Ultrasound Echo Pin
#define US_ECHO_PIN     A5

// IR Sensors
#define IR_1_PIN        A4  // Far Left Sensor      (Relative to foward motion)
#define IR_2_PIN        A3  // Middle Left Sensor   (Relative to foward motion)
#define IR_3_PIN        A2  // Center Sensor        (Relative to foward motion)
#define IR_4_PIN        A1  // Middle Right Sensor  (Relative to foward motion)
#define IR_5_PIN        A0  // Far Right Sensor     (Relative to foward motion)
const int IRSensor[] = {IR_1_PIN, IR_2_PIN, IR_3_PIN, IR_4_PIN, IR_5_PIN};


}//end of namespace PINS
