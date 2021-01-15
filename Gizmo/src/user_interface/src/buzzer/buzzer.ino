#include "buzzer_class.h"

buzzer_class buzzer;
void setup() {
  buzzer.victoryTune();
  delay(1000);
  buzzer.touchTune();
}

void loop() {
  // Empty Loop
}
