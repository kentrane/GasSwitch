#include "Arduino_LED_Matrix.h"   //Include the LED_Matrix library
ArduinoLEDMatrix matrix;  


void setup() {

  Serial.begin(115200);

  // you can also load frames at runtime, without stopping the refresh

  matrix.loadSequence(LEDMATRIX_ANIMATION_HEARTBEAT_LINE);

  matrix.begin();

  matrix.play(true);

}


void loop() {

}

class GasSwitch {
  public:
    struct {
      string gasName;
      int gasValve;
    } 
    Argon = {.gasName="Argon", .gasValve=0},
    Hydrogen = {.gasName="Hydrogen", .gasValve=1},
    Helium = {.gasName="Helium", .gasValve=2},
    Nitrogen = {.gasName="Nitrogen", .gasValve=3};
    GasSwitch(Gas InitialGas)
  private:

};