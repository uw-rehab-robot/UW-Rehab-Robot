/**************************************************************************
  Gizmo Project Code
**************************************************************************/

// Include Libraries
#include "GizmoPins.h"
#include "src/user_interface/user_interface_class.h"
#include "src/line_following/line_following_class.h"
#include "src/ultrasound/ultrasound_class.h"
//#include ...Need SD Card code 

// Class Instantiations
user_interface_class  ui;
oled_screen_class screen;
buzzer_class buzzer;
line_following_class lineFollow;
ultrasound_class ultrasound;

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

unsigned int  sessionMinutes = 3.25;  // in minutes
int           score;
int           stops;

unsigned int sessionTime;
unsigned int gameStartTime;
unsigned int gameEndTime;
int touchResult = 0;

//----------------------------------------------//
// Setup Function (One Time At Startup)
//----------------------------------------------//
void setup()
{
  // User Interface Setup
  ui.ui_setup();  // Button, OLED screen, Speaker Setup

  // Ultrasound Setup
  ultrasound.ultrasound_setup();

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
        // local variables
        sessionTime     = sessionMinutes*60*1000; // Convert to seconds, then miliseconds
        gameStartTime   = millis();
        gameEndTime     = sessionTime + gameStartTime;
        touchResult     = 0;
        stops           = 0;
        score           = 0;
    
        screen.countdown();
        // wait specified time (30 sec default) or until ultrasound sensor to read <=10
        while(millis() < gameEndTime)
        {
          // Start line following
          lineFollow.follow_line(10000); // units in ms
          
          // Wait For Touch
          touchResult = 0;
          screen.print_text((char*)"Waiting \nFor \nTouch...", 2);
          touchResult = ultrasound.waitForTouch(20); // units in sec
          if (touchResult == 1)
          {
              screen.eyes_happy();
              buzzer.touchTune();
              score++;
              // Increase the score by one
          }
          else
          {
              screen.eyes_resting();
          }
          stops++;

        }
        current_state = MENU; // No game code so moving back to menu...
        screen.update_score(score);
        screen.update_stops(stops);
        screen.victory();
        buzzer.victoryTune();
        screen.display_final_result();
        delay(5000);  // To Do: replace with milis based wait...
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
