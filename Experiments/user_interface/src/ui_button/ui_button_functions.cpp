#include "Arduino.h"
#include "ui_button_class.h"

// Local Variables
char buttonPin                  = RX1;  // TO DO: Move Pin Assignment To Global Pin Assignment List
int ledPin                      = 13;
int buttonSelect                      = 0;
int selectDetect                = 0;
int next                        = 0;
int currentButtonState          = 1;
int lastButtonState             = 1;    // Used to determine button transitions
unsigned long lastDebounceTime  = 0;    // Used to time button press durations
int minDebounceTime             = 20;   // Used to debounce button input (20ms)
int selectTimer                 = 500;  // Used to identify Select vs Next (500ms)


// Class Functions
int ui_button_class::checkSelect()
{
    int temp = buttonSelect;
    buttonSelect = 0;
    return temp;
    
}

int ui_button_class::checkNext()
{
    int temp = next;
    next = 0;
    buttonSelect = 0;
    return temp;
}

void ui_button_class::ui_button_setup()
{
    pinMode(buttonPin, INPUT);
    pinMode(ledPin, OUTPUT);
    
    // Set Initial LED State
    digitalWrite(ledPin, OUTPUT);


    // ---------------------------------------------
    // MOVE LINES BELOW TO TOP-LEVEL INTERRUPT SETUP
    // ---------------------------------------------
    cli();          // stop interrupts
    
    // Set timer0 interrupt at 1kHz
    TCCR0A  = 0;    // set entire TCCR0A register to 0
    TCCR0B  = 0;    // same for TCCR0B
    
    // Set compare match register for 2kHz increments
    OCR0A   = 249;  // = (16*10^6) / (1000*64) - (must be <256)
    
    // Turn on CTC mode
    TCCR0A  |= (1 << WGM01);
    
    // Set CS01 and CS00 bits for 64 prescaler
    TCCR0B  |= (1 << CS01) | (1 << CS00);
    
    // Enable timer compare interrupt
    TIMSK0  |= (1 << OCIE0A);

    sei();          // Allow interrupts
}


// Global Functions
void buttonCheck()
{
    // Read button value into local varaiable
    int buttonValue = digitalRead(buttonPin);

    // If the button changed (due to noise or pressing)
    if (buttonValue != lastButtonState)
    {
        // Reset debounce timer
        lastDebounceTime = millis();
    }
    
    // Only check button state after debounce timer elapsed
    if ((millis() - lastDebounceTime) > minDebounceTime)
    {
        // If button state changed:
        if (buttonValue != currentButtonState)
        {
            currentButtonState = buttonValue;
            
            // Button Pushed, do nothing
            //if (buttonState == LOW)
            //{
            //    
            //}
            
            // Button Released
            if (buttonState == HIGH)
            {
                // Check for select detect
                if (selectDetect == HIGH)
                {
                    selectDetect    = 0;
                }
                // Otherwise next was desired
                else
                {
                    next            = 1;
                }
            }
        }

        // Check for button being held down once per press
        if (buttonState == LOW && selectDetect == 0)
        {
            // Check Select timer
            if ((millis() - lastDebounceTime) > selectTimer)
            {
                buttonSelect          = 1;
                selectDetect    = 1;
            }
        }
    }
}


// Timer0 interrupt 1kHz calls buttonCheck
ISR(TIMER0_COMPA_vect)
{
  buttonCheck();
}
