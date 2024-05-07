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
    Gas Flush = {.gasName="Flushing", .gasValve=8};

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
      if(GasSetting.gasValve == -1){
        //Turn all off
        for(int i = 2; i <= 8; i++){
          digitalWrite(i,LOW);
        }
        CurrentGas = GasSetting;
      }
      else{
        //Turn all off
        for(int i = 2; i <= 8; i++){
          digitalWrite(i,LOW);
        }
        //Turn on gas we want
        digitalWrite(GasSetting.gasValve, HIGH);
        delay(20);
        //Flush
        digitalWrite(Flush.gasValve, HIGH);
        delay(200);
        digitalWrite(Flush.gasValve, LOW);
        delay(20);
        CurrentGas = GasSetting;
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

String inputString = "";      // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
GasSwitch gs;
void setup() {
  Serial.begin(115200);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  matrix.begin();
  matrix.play(true);
} 

void loop() {  
  if (stringComplete) {
    Serial.println(inputString);
    if(inputString == "argon\n" || inputString == "Argon\n"){
      Serial.println("Setting gas Argon");
      gs.SetGas(gs.Argon);
      //gs.PrintGas(gs.Argon);
    }
    else if(inputString == "hydrogen\n" || inputString == "Hydrogen\n"){
      Serial.println("Setting gas Hydrogen");
      gs.SetGas(gs.Hydrogen);
      //gs.PrintGas(gs.Hydrogen);
    }
    else if(inputString == "helium\n" || inputString == "Helium\n"){
      Serial.println("Setting gas Helium");
      gs.SetGas(gs.Helium);
      //gs.PrintGas(gs.Helium);
    }
    else{
      Serial.println("Didn't understand...");
    }
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
  if(Serial.available() > 0) {
    while (Serial.available()) {
      // get the new byte:
      char inChar = (char)Serial.read();
      // add it to the inputString:
      inputString += inChar;
      // if the incoming character is a newline, set a flag so the main loop can
      // do something about it:
      if (inChar == '\n') {
        stringComplete = true;
      }
    }
  }
}

