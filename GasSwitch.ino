#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"
ArduinoLEDMatrix matrix;  

class GasSwitch {
  public:
    //Define needed parameters for a Gas
    struct Gas{
      String gasName;
      int gasValve;
    };
    //Define different gases and the valves they are attched to.
    const Gas None = {.gasName="none", .gasValve=-1};
    const Gas Argon = {.gasName="Argon", .gasValve=0};
    const Gas Hydrogen = {.gasName="Hydrogen", .gasValve=1};
    const Gas Helium = {.gasName="Helium", .gasValve=2};
    const Gas Nitrogen = {.gasName="Nitrogen", .gasValve=3};
    const Gas Oxygen = {.gasName="Oxygen", .gasValve=4};
    const Gas Neon = {.gasName="Neon", .gasValve=5};
    
    GasSwitch(){
      /* Initialize IO */
      //Pins = 2, 3, 4, 5, 6, 7, 8 = Gas 0, 1, 2, 3, 4, 5 + vent

      /* Set the gas to the be closed */
      SetGas(None);
    }
    int SetGas(Gas GasSetting){
        /*  
        *   To set the gas:
        *     1.  Turn off current gas 
        *     2.  Vent gas
        *     3.  Turn on next gas
        */


    }
    int WriteGas(Gas GasToWrite){
      matrix.beginDraw();
      matrix.stroke(0xFFFFFFFF);
      matrix.textScrollSpeed(50);
      matrix.textFont(Font_5x7);
      matrix.beginText(0, 1, 0xFFFFFF);
      matrix.println("  " + GasToWrite.gasName);
      matrix.endText(SCROLL_LEFT);
      matrix.endDraw();
    }
    Gas GetGas(){
      return CurrentGas;
    }

  private:
    Gas CurrentGas = None;
};


static String text = "  Gas to print    ";

GasSwitch GS;
void setup() {

  Serial.begin(115200);

  matrix.begin();

  matrix.play(true);
  

} 


void loop() {
  GS.WriteGas(GS.Argon);

  delay(1000);

  GS.WriteGas(GS.Hydrogen);
}

