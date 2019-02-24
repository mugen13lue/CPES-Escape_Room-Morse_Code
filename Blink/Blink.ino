
#include <TimedAction.h>

#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 50

#define TIME_UNIT 250

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 3
  
// Define the array of leds
CRGB leds[NUM_LEDS];

//_________________________________________________light-up fuctions____________________________________

void dot(int i, int r, int g, int b){
  leds[i] = CRGB(r,g,b);
}
void dash(int i, int r, int g, int b){
  leds[i] = CRGB(r,g,b);
}
void space(int i, int r, int g, int b){
  //do nothing
}
void sEnd(int i, int r, int g, int b){  
  //do nothing
}
//________________________________________________________________creating the timedActions and their respective functions_______________________________________

TimedAction LED0 =  TimedAction(TIME_UNIT, led0); 
int pos0 = 0;
void led0(){
  int arr[] = {0,0,0,1,1,1,0,0,0,3};
  if (arbitraryLedDo(0, 128, 0 ,0, LED0, arr[pos0]) )
    pos0 = (pos0 +1) % 10; 
}

TimedAction LED2 = TimedAction(TIME_UNIT, led2);
int pos2 = 0;
void led2(){
  int arr[] = {1,0,1,0,2};
  if (arbitraryLedDo(2, 128, 0, 0, LED2, arr[pos2]) )
    pos2 = (pos2 +1) % 5 ;
}

//____________________________________________________setup____________________________________
void setup() { 
    FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);       
}

//_________________________________________________the singular function to handle the led activations____________

boolean arbitraryLedDo(int ledNum, int r, int g, int b, TimedAction& action, int instruction){
  if( leds[ledNum].r > 0 || leds[ledNum].g > 0 || leds[ledNum].b > 0 ){
      leds[ledNum] = CRGB::Black;
      action.setInterval(TIME_UNIT);
      return false;
  }else{        
      switch(instruction){
        case 0:
          dot(ledNum, r, g, b);
          action.setInterval(TIME_UNIT);
          break;
        case 1:
          dash(ledNum, r, g, b);
          action.setInterval(3*TIME_UNIT);
          break;
        case 2: 
          space(ledNum, r, g, b);//technically useless
          action.setInterval(4*TIME_UNIT);
          break;
        case 3: 
          sEnd(ledNum, r, g, b);//technically usless
          action.setInterval(6*TIME_UNIT);
          break;
    }
    return true;
  }
}
 
 
//____________________________________main loop____________________________
void loop() {    
    LED0.check();
    LED2.check(); 
    FastLED.show();
}
  
  
