
#ifndef ultrasound_h
  #define ultrasound_h
  
  #include "Arduino.h"
  
  class ultrasound_class {
    
    
    public:
      byte runUltrasound();
      void ultrasound_setup();
      int waitForTouch(int waitSeconds);
  };

#endif
