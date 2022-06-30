/** ************************************************************************
 * File Name: Qwiic_Switch_Gamepad_Software.ino 
 * Title: Qwiic Switch Gamepad Software
 * Developed by: Milador
 * Version Number: 1.0 (30/6/2022)
 * Github Link: https://github.com/milador/Qwiic-Switch-Gamepad
 ***************************************************************************/


#include <Wire.h>
#include "SparkFun_TCA9534.h"
#include "TinyUSB_Gamepad.h"
#include <Adafruit_NeoPixel.h>


//Define LED pin
#define LED_PIN 11

//***CAN BE CHANGED***/
#define SWITCH_REACTION_TIME           150                  //Reaction time for each switch action (150ms)
#define LED_BRIGHTNESS                 100                  //The mode led color brightness which is always on ( Use a low value to decrease power usage )
#define OPERATING_MODE_LED_COLOR       7                    //Teal


//***DO NOT CHANGE***//
#define INPUT_ADDR                     0x27                //TCA9534 input switch module I2C Address 
#define NUM_SWITCH                     2                   //Switch A and B
#define UPDATE_SWITCH_DELAY            200                 //100ms

// Variable Declaration
bool g_inputPinMode[NUM_SWITCH] = {GPIO_IN, GPIO_IN};

String g_switchConnectionMessage;        //Qwiic modules connection state message 
int g_moduleConnectionState;

//Declare switch state variables for each switch
bool g_switchAState,g_switchBState;


//RGB LED Color code structure 

struct rgbColorCode {
    int r;    // red value 0 to 255
    int g;   // green value
    int b;   // blue value
 };

//Color structure 
typedef struct { 
  uint8_t colorNumber;
  String colorName;
  rgbColorCode colorCode;
} colorStruct;

 //Mode structure 
typedef struct { 
  uint8_t modeNumber;
  String modeName;
  uint8_t modeColorNumber;
} modeStruct;


 //Switch structure 
typedef struct { 
  uint8_t switchNumber;
  String switchButtonName;
  uint8_t switchButtonNumber;
  uint8_t switchColorNumber;
} switchStruct;

//Color properties 
const colorStruct colorProperty[] {
    {1,"Green",{60,0,0}},
    {2,"Pink",{0,50,60}},
    {3,"Yellow",{60,50,0}},    
    {4,"Orange",{20,60,0}},
    {5,"Blue",{0,0,60}},
    {6,"Red",{0,60,0}},
    {7,"Purple",{0,50,128}},
    {8,"Teal",{128,0,128}}       
};

//Switch properties 
const switchStruct switchProperty[] {
    {1,"One",1,5},                            // Default: Press button one or button X1(Left USB)/View(Right USB) in XAC
    {2,"Two",2,3}                             // Default: Press button two or button X2(Left USB)/Menu(Right USB) in XAC
};


TCA9534 inputModule;            //Input
TinyGamepad Gamepad;

//Setup NeoPixel LED
Adafruit_NeoPixel ledPixels = Adafruit_NeoPixel(1, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {

  Serial.begin(115200);  
  delay(5);
  ledPixels.begin();                                                           //Start NeoPixel
  delay(5);
  Gamepad.begin();
  delay(5);  
  busExpandSetup();                                                            //Setup bus expander
  delay(1000);
  initLedFeedback();
  //Initialize the LED pin as an output
  pinMode(LED_PIN, OUTPUT);                                                

};

void loop() {

  //Update status of switch inputs
  g_switchAState = inputModule.digitalRead(0);
  g_switchBState = inputModule.digitalRead(1);

  gamepadAction(g_switchAState,g_switchBState); 

  ledPixels.show(); 
  delay(SWITCH_REACTION_TIME);
}



//***BUS EXPANDER SETUP FUNCTION***//
void busExpandSetup() {
  //Initialize the switch pins as inputs
  Wire.begin();
  while (1) { //Both input and output modules are successfully detected 
    if (inputModule.begin(Wire,INPUT_ADDR) == true ) {
      g_switchConnectionMessage = "Success: I2C is detected";
      Serial.println(g_switchConnectionMessage);
      g_moduleConnectionState = 1;
      break;
    } else {
      g_switchConnectionMessage = "Success: I2C not detected";
      Serial.println(g_switchConnectionMessage);
      g_moduleConnectionState = 0;
      delay(3000);
    }
  }
  inputModule.pinMode(g_inputPinMode);
}


//***ADAPTIVE SWITCH GAMEPAD FUNCTION***//
void gamepadAction(int switchA,int switchB) {
    if(!switchA) {
      // Button A
      if(switchB) { setLedColor(switchProperty[0].switchColorNumber-1,LED_BRIGHTNESS); }
      Gamepad.press(switchProperty[0].switchButtonNumber-1);
    } else
    {
      setLedColor(OPERATING_MODE_LED_COLOR,LED_BRIGHTNESS);
      Gamepad.release(switchProperty[0].switchButtonNumber-1);
    }
    
    if(!switchB) {
      //Button B
      if(switchA) { setLedColor(switchProperty[1].switchColorNumber-1,LED_BRIGHTNESS); }
      Gamepad.press(switchProperty[1].switchButtonNumber-1);
    } else
    {
      setLedColor(OPERATING_MODE_LED_COLOR,LED_BRIGHTNESS);
      Gamepad.release(switchProperty[1].switchButtonNumber-1);
    }
    Gamepad.send();
    delay(5);

}


//***RGB LED FUNCTION***//

void setLedBlink(int numBlinks, int delayBlinks, int ledColor,uint8_t ledBrightness) {
  if (numBlinks < 0) numBlinks *= -1;

      for (int i = 0; i < numBlinks; i++) {
        ledPixels.setPixelColor(0, ledPixels.Color(colorProperty[ledColor-1].colorCode.g,colorProperty[ledColor-1].colorCode.r,colorProperty[ledColor-1].colorCode.b));
        ledPixels.setBrightness(ledBrightness);
        ledPixels.show(); 
        delay(delayBlinks);
        ledPixels.setBrightness(ledBrightness);
        ledPixels.setPixelColor(0, ledPixels.Color(0,0,0));
        ledPixels.setBrightness(ledBrightness);
        ledPixels.show(); 
        delay(delayBlinks);
      }
}

//***UPDATE RGB LED COLOR FUNCTION***//

void updateLedColor(int ledColor, uint8_t ledBrightness) {
    ledPixels.setPixelColor(0, ledPixels.Color(colorProperty[ledColor-1].colorCode.g,colorProperty[ledColor-1].colorCode.r,colorProperty[ledColor-1].colorCode.b));
    ledPixels.setBrightness(ledBrightness);
    ledPixels.show();
}


//***GET RGB LED BRIGHTNESS FUNCTION***//

uint8_t getLedBrightness() {
  return (ledPixels.getBrightness());
}

//***SET RGB LED COLOR FUNCTION***//

void setLedColor (uint32_t ledColor, uint8_t ledBrightness){
    
  ledPixels.setPixelColor(0, ledColor);
  ledPixels.setBrightness(ledBrightness);
  ledPixels.show(); 

}

//***SET RGB LED BRIGHTNESS FUNCTION***//

void setLedBrightness(uint8_t ledBrightness) {
  ledPixels.setBrightness(ledBrightness);
  ledPixels.show();
}

//***CLEAR RGB LED FUNCTION***//

void ledClear() {
  ledPixels.setPixelColor(0, ledPixels.Color(0,0,0));
  ledPixels.show(); 
}

//***INIT LED FEEDBACK FUNCTION***//
void initLedFeedback(){
  setLedBlink(2,500,OPERATING_MODE_LED_COLOR,LED_BRIGHTNESS);
  delay(5);
  updateLedColor(OPERATING_MODE_LED_COLOR,LED_BRIGHTNESS);
  delay(5);
}
