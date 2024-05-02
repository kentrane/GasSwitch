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
    struct Gas{
      String gasName;
      int gasValve;
    };
    Gas Argon = {.gasName="Argon", .gasValve=0};
    Gas Hydrogen = {.gasName="Hydrogen", .gasValve=1};
    Gas Helium = {.gasName="Helium", .gasValve=2};
    Gas Nitrogen = {.gasName="Nitrogen", .gasValve=3};
    GasSwitch(Gas InitialGas){

    }
  private:

};