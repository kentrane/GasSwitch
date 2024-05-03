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
    Gas None = {.gasName="No gas", .gasValve=-1};
    Gas Argon = {.gasName="Argon", .gasValve=2};
    Gas Hydrogen = {.gasName="Hydrogen", .gasValve=3};
    Gas Helium = {.gasName="Helium", .gasValve=4};
    Gas Nitrogen = {.gasName="Nitrogen", .gasValve=5};
    Gas Oxygen = {.gasName="Oxygen", .gasValve=6};
    Gas Neon = {.gasName="Neon", .gasValve=7};

    GasSwitch(){

      /* Initialize IO */
      //Pins = 2, 3, 4, 5, 6, 7, 8 = Gas 0, 1, 2, 3, 4, 5 + vent
      for(int i = 2; i <= 8; i++){
        pinMode(i, OUTPUT);
        digitalWrite(i,LOW);
      }
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
      if(GasSetting.gasValve== -1){
        //Turn all off
        for(int i = 2; i <= 8; i++){
          digitalWrite(i,LOW);
        }
      }
      else{
        //Turn all off
        for(int i = 2; i <= 8; i++){
          digitalWrite(i,LOW);
        }
        digitalWrite(8,HIGH);
        delay(500);
        digitalWrite(8,LOW);

      }
    }
    int PrintGas(Gas GasToPrint){
      matrix.beginDraw();
      matrix.stroke(0xFFFFFFFF);
      matrix.textScrollSpeed(50);
      matrix.textFont(Font_5x7);
      matrix.beginText(0, 1, 0xFFFFFF);
      matrix.println("  " + GasToPrint.gasName);
      matrix.endText(SCROLL_LEFT);
      matrix.endDraw();
    }
    Gas GetGas(){
      return CurrentGas;
    }

  private:
    Gas CurrentGas = None;
};


GasSwitch gs;
void setup() {
  Serial.begin(115200);
      matrix.begin();
      matrix.play(true);
} 


void loop() {
  gs.PrintGas(gs.Argon);
  delay(100);
  gs.PrintGas(gs.Hydrogen);
  delay(100);
  gs.PrintGas(gs.Helium);
  delay(100);
  gs.PrintGas(gs.Nitrogen);
  delay(100);
}

