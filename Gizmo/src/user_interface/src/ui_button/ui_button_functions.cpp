#include "Arduino.h"
#include "ui_button_class.h"

// Local Variables
int ledPin      = 13;
int uiButtonPin = 28;
bool interruptsEnabled          = false;  // TO DO: Move to top-level interrupt setup

int previousState = 1;       // Used to determine button transitions
unsigned int previousPress;     // Used to time button press durations
volatile int buttonFlag;
int buttonDebounce  = 20;       // Used to debounce button input (20ms)
int selectTimer     = 500;      // Used to identify Select vs Next (500ms)

int userSelect  = 0;                // User Pressed Select
int next    = 0;                // User Pressed Next

// Global Functions
// Class Functions
int ui_button_class::checkSelect()
{
    int temp = userSelect;
    if (userSelect) {
      next = 0;
      userSelect = 0;
    }
    return temp;
}

int ui_button_class::checkNext()
{
    int temp = next;
    if (next) {
      next = 0;
      userSelect = 0;
    }
    return temp;
}

void buttonEvent()
{
  ui_button_class ui_btn;

  // Button Pushed
  if (digitalRead(uiButtonPin) == LOW && previousState == HIGH)
  {
    previousPress = millis();
    previousState = LOW;
  }

  // Button Released
  else if (digitalRead(uiButtonPin) == HIGH && previousState == LOW)
  {

    // Select
    if ((millis() - previousPress) > selectTimer)
    {
      //oled.main_menu();
      userSelect = 1;
    }

    // Next
    else
    {
      next = 1;
    }
    previousState = HIGH;
  }
}

// Button Interrupt Service Routine
void myISR(void)
{
  // Button Debouncer
  if((millis() - previousPress) > buttonDebounce)
  {
    buttonEvent();
  }
}

// Class Functions
void ui_button_class::ui_button_setup()
{
    pinMode(uiButtonPin, INPUT_PULLUP);
    pinMode(ledPin, OUTPUT);
    
    // Set Initial LED State
    digitalWrite(ledPin, OUTPUT);

    attachInterrupt(digitalPinToInterrupt(uiButtonPin), myISR, RISING);
    //attachInterrupt(digitalPinToInterrupt(uiButtonPin), myISR, FALLING);
    //  attachInterrupt(digitalPinToInterrupt(uiButtonPin), myISR, LOW);
    //  attachInterrupt(digitalPinToInterrupt(uiButtonPin), myISR, HIGH);
    //  attachInterrupt(digitalPinToInterrupt(uiButtonPin), myISR, CHANGE);

    //  // attaching a different interrupt to the same pin overwrites the existing ISR
    //  attachInterruptArg(digitalPinToInterrupt(uiButtonPinN), myISRArg, &count, RISING);

    interruptsEnabled = true;
}
