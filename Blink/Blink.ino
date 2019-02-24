
#include <TimedAction.h>

#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 50

#define TIME_UNIT 250

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 3
enum { DOT, SPACE, DASH, S_END};
int arr = DOT;
  

// Define the array of leds
CRGB leds[NUM_LEDS];



  



void dot(int i){
 leds[1] = CRGB::Red;

//if on turns off, if off turns on
  leds[i] = CRGB::Red;

  
}


void dash(int i){
  leds[1] = CRGB::Blue;

  leds[i] = CRGB::Red;
 

}


void space(int i){
  leds[1] = CRGB::Green;
}

void sEnd(int i){
  leds[1] = CRGB::Purple;
  
}


  TimedAction LED0 =  TimedAction(TIME_UNIT, led0);
  TimedAction LED2 = TimedAction(TIME_UNIT, led2);

  
  void setup() { 
       FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);  
     
       
}
int pos0 = 0;
void led0(){
  if( leds[0].r > 0 || leds[0].g > 0 || leds[0].b > 0){
    leds[0] = CRGB::Black;
    LED0.setInterval(TIME_UNIT);
    }else{      
    int arr[] = {0,0,0,1,1,1,0,0,0,3};
    switch( arr[pos0]){
      case 0:
        dot(0);
        LED0.setInterval(TIME_UNIT);
        break;
      case 1:
        dash(0);
        LED0.setInterval(3*TIME_UNIT);
        break;
      case 2: 
        space(0);
        LED0.setInterval(4*TIME_UNIT);
        break;
      case 3: 
        sEnd(0);
        LED0.setInterval(6*TIME_UNIT);
        break;
    }
  pos0 = (pos0 +1) %10 ;  
  }
}
int pos2 = 0;
void led2(){
  if( leds[2].r > 0 || leds[2].g > 0 || leds[2].b > 0){
    leds[2] = CRGB::Black;
    LED2.setInterval(TIME_UNIT);
    }else{
      
    int arr[] = {1,0,1,0,2};
    switch( arr[pos2]){
      case 0:
        dot(2);
        LED2.setInterval(TIME_UNIT);
        break;
      case 1:
        dash(2);
        LED2.setInterval(3*TIME_UNIT);
        break;
      case 2: 
        space(2);
        LED2.setInterval(4*TIME_UNIT);
        break;
      case 3: 
        sEnd(2);
        LED2.setInterval(6*TIME_UNIT);
        break;
    }
  pos2 = (pos2 +1) %5 ;
      
  
  }
}


 
 

void loop() {
  
//    switch(arr){
//      case SPACE:
//        space();
//        break;
//      case DOT:
//        dot(0);
//        break;
//      case DASH:
//        dash(0);
//        break;
//      case S_END:
//        sEnd();
//        break;
//    }

//    int[10] arr1 = {0, 0, 2, 1)
    
    LED0.check();

    LED2.check();
    
  
        
        
  
  


  FastLED.show();
}
  
  
