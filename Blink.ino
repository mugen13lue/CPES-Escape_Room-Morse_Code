#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 50

#define TIME_UNIT 250

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 3
//#define CLOCK_PIN 13
enum { DOT, SPACE, DASH, S_END};
int arr = DOT;
  

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() { 
       FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);  
     
       
}

 
 

void loop() {
  
    switch(arr){
      case SPACE:
        space();
        break;
      case DOT:
        dot(0);
        break;
      case DASH:
        dash(0);
        break;
      case S_END:
        sEnd();
        break;
    }
  
        
        
  
  


  FastLED.show();
}
  
  
  



void dot(int i){
// Turn the LED on, then pause
  leds[i] = CRGB::Red;
  FastLED.show();
  delay(250);
  // Now turn the LED off, then pause
  leds[i] = CRGB::Black;
  FastLED.show();
  delay(250);
}


void dash(int i){
// Turn the LED on, then pauseee
  leds[i] = CRGB::Red;
  FastLED.show();
  delay(3*TIME_UNIT);
  // Now turn the LED off, then pause
  leds[i] = CRGB::Black;
  FastLED.show();
  delay(3*TIME_UNIT);
}


void space(){
  delay(5*TIME_UNIT);
}

void sEnd(){
  delay(7*TIME_UNIT);
}
