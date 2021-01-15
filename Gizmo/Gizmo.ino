/**************************************************************************
  Gizmo Project Code
**************************************************************************/

// Include Libraries
#include "GizmoPins.h"
#include "src/user_interface/user_interface_class.h"
//#include ...Need line following code (Should include motor control and sensors)
//#include ...Need ultrasound code  (Needs simple function calls with an optional threshold input and returns "touch/no touch")
//#include ...Need SD Card code 

// Class Instantiations
user_interface_class  ui;
oled_screen_class screen;

// Import Definitions from GizmoPins.h
using namespace PINS;


// State Definitions
enum gizmo_state_enum { INACTIVE,
                        MENU,
                        GAME,
                        CALIBRATION};

// Variables
uint8_t current_state = MENU;
String user_selection = "";


//----------------------------------------------//
// Setup Function (One Time At Startup)
//----------------------------------------------//
void setup()
{
  // User Interface Setup
  ui.ui_setup();  // Button, OLED screen, Speaker Setup

  startup();
}


//----------------------------------------------//
// Local Functions //
//----------------------------------------------//
// Startup routine, separated from setup() for code cleanliness
void startup()
{
  screen.menu_start();
  delay(1000);  // To Do: Replace with milis-based wait function
}


//----------------------------------------------//
// Main Program (Loop Indefinitely)
//----------------------------------------------//
void loop()
{
    // Run code based on current state
    switch(current_state)
    {
      // Handle an inactive state
      case INACTIVE:
      {
        // Need to determine what this state should be used for
        // and how to leave it... For now going to MENU...
        current_state = MENU;
        break;
      }

      // Menu screen for user to select next action
      case MENU:
        user_selection = ui.ui_menu();
        // User chose to start the game
        if (user_selection = "START")
        {
          current_state = GAME;
        }
        // User chose to run calibration
        else if (user_selection = "CALIBRATION")
        {
          current_state = CALIBRATION;
        }
        // Something went wrong
        else
        {
          current_state = INACTIVE; // Replace if INACTIVE not used for error state...
        }
        break;

      // Run through the game
      case GAME:
        // ADD GAME CODE HERE //
        screen.countdown();   // To Do: Remove once real game routine is ready
        screen.eyes_open();   // To Do: Remove once real game routine is ready
        current_state = MENU; // No game code so moving back to menu...
        break;

      // Run through the calibration
      case CALIBRATION:
        // ADD CALIBRATION CODE HERE //
        screen.calibrate();       // To Do: Remove once real calibration routine is ready
        screen.eyes_resting_2();  // To Do: Remove once real calibration routine is ready
        screen.eyes_happy_2();    // To Do: Remove once real calibration routine is ready
        screen.eyes_open_2();     // To Do: Remove once real calibration routine is ready
        current_state = MENU;     // No calibration code so moving back to menu...
        break;
    }
}
