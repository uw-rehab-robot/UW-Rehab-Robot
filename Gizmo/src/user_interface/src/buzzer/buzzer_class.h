
#ifndef buzzer_h
  #define buzzer_h
  
  #include "Arduino.h"
  
  class buzzer_class {
    private:
        void playTune(int melody[], int notes, int tempo);

    public:
        void victoryTune();
        void touchTune();
        //void encouragementTune(); // TO ADD
  };

#endif
