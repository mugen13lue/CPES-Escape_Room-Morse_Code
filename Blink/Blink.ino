
#include <TimedAction.h>

#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 40

#define TIME_UNIT 500

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 4
  
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
/*
String encode(const char *string);

String decode(String morse);

//Build a struct with the morse code mapping
static const struct {const char letter, *code;} MorseMap[] =
{
  { 'A', "01" },
  { 'B', "1000" },
  { 'C', "1010" },
  { 'D', "100" },
  { 'E', "0" },
  { 'F', "0010" },
  { 'G', "110" },
  { 'H', "0000" },
  { 'I', "00" },
  { 'J', "0111" },
  { 'K', "0101" },
  { 'L', "0100" },
  { 'M', "11" },
  { 'N', "10" },
  { 'O', "111" },
  { 'P', "0110" },
  { 'Q', "1101" },
  { 'R', "010" },
  { 'S', "000" },
  { 'T', "1" },
  { 'U', "001" },
  { 'V', "0001" },
  { 'W', "011" },
  { 'X', "1001" },
  { 'Y', "1011" },
  { 'Z', "1100" },
  { ' ', "2" }, //Gap between word, seven units 
    
  { '1', "01111" },
  { '2', "00111" },
  { '3', "00011" },
  { '4', "00001" },
  { '5', "00000" },
  { '6', "10000" },
  { '7', "11000" },
  { '8', "11100" },
  { '9', "11110" },
  { '0', "11111" },
    
  { '.', "010101" },
  { ',', "110011" },
  { '?', "001100" },
  { '!', "101011" },
  { ':', "111000" },
  { ';', "101010" },
  { '(', "10110" },
  { ')', "101101" },
  { '"', "010010" },
  { '@', "011010" },
  { '&', "01000" },
};

String encode(String str)
{
  size_t i, j;
  String morseWord = "";
  
  for( i = 0; str[i]; ++i )
  {
    for( j = 0; j < sizeof MorseMap / sizeof *MorseMap; ++j )
    {
      if( toupper(str[i]) == MorseMap[j].letter )
      {
        morseWord += MorseMap[j].code;
        break;
      }
    }
    morseWord += " "; //Add tailing space to seperate the chars
  }

  return morseWord;
}
*/



//_____________________________________________________________-all that shit____________________________________
unsigned char positions[40] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//position array
unsigned char inst[40][22] = {
  {1,0,1,0,2,0,1,1,0,2,0,2,0,0,0,4},//0
  {0,1,0,2,1,1,1,2,1,0,1,0,2,1,0,1,2,0,0,0,4},//1
  {1,1,0,0,1,0,1, 4},//2
  {0,0,1,1,1,2,1,0,0,4},//3 Step 5 "2D" 4A
  {0,1,1,0,0,0,1,1,1,  4},//4
  {0,1,1,1,0,0, 4},//5
  {0,0,0,0,0,0,0, 4},//6
  {0,0,1,0,1,0,1,0, 4},//7
  {0,0,0,1,0,1,0, 4},//8
  {0,1,0,0,1,1,1,1,0, 4},//9
  {0, 1,1,1,0,0,1,1, 4},//10
  {0,1,0,1,0, 4},//11
  {1,0,0,1,1,0,0,1, 4},//12
  {0,1,0,0,1,1,1,0,4},//13
  {0,1,1,0,1, 4},//14
  {1,1,1,1,0,2,1,0,0,4},//15 Step 1 "9D" B5
  {1,0,1,1,0,1,0,4},//16
  {1,0,0,0,0,1,1,1,1,1,4},//17
  {1,0,0,0,0,0,1,1,1,1,0,0,1,1,0,1,0,1,0,0,4},//18
  {1,1,0,0,0,1,1,0,0,1,1, 4},//19
  {0,1,1,0,0,0,1,1,1,0, 4},//20
  {0,0,0,0,1,1,1,1,1,1,1, 4},//21
  {1,0,1,1,1,1,1,0,0 ,4},//22
  {0,0,0,0,2,0,0, 4},//23
  {1,2,0,0,0,0,2,0,2,0,1,0,2,0, 4},//24
  {0,1,0,1,1,1,2,0,0,0,1,1,2,0, 4},//25
  {0,1,1,2,0,0,0,2,1,1,4},//26
  {1,0,0,0,0,2,1,0,0,4},//27 Step 3 "6D" 8C
  {0,2,0,2,1,1,2,1,2,1,0, 4},//28
  {0,0,0,2,1,1,1,0,0,0,2,0,0,0,0,0,0,4},//29
  {1,2,0,0,0,1,1,2,0,1,1,2,0,2,1, 4},//30
  {1,1,1,0,0,2,1,0,1,0,4},//31 Step 2 "8C" D9
  {0,1,2,1,0 ,4},//32
  {0,0,1,1,2,0,1,1, 4},//33
  {0,0,0,0,1,2,0,1,4},//34 Step 4 "4A" 6D
  {0,1,1,0,2,1,1,0,0,1,1, 4},//35
  {1,1,0,1,0,0,1,2,0,1,2 ,4},//36
  {0,0,1,0,0,1,1,1,1,1,1,1,1,1,1, 4},//37
  {0,2,1,0,2,1,0,0,4},//38 Step 6 "END" 2D
  {0,1,1,1,4},//39
//  {0,1,0,1,0,1,4},//40
//  {1,1,1,0,0,2,1,0,1,0,4},//41 Step 2 "8C" 2E
//  {0,0,1,0,0,0,14}, // 42
//  {0,0,0,0,2,0,0,1,2,0,0, 4},//43
//  {0,0,0,1,2,1,1,1,0,2,1,1,0,0,2,1,4},//44
//  {0,0,1,1,2,1,1,1,1,2,0,0,0, 4},//45
//  {0,1,2,1,0,4},//46
//  {0,2,1,0,1,2,0,0,0,4},//47
//  {0,2,1,0,2,1,0,0,4},//48 Step 6 "END" 9E
//  {0,1,1,1,1,0,2,1,1,2,0,0,0, 4}//49
  };

/*
void makeinstr(){
  
   String codes[50] = {
    "000111000", 
    encode("sbs"),
    encode("three"), 
    encode("test3"),
    encode("test4"),
    encode("test0"), 
    encode("test1"),
    encode("test2"), 
    encode("test3"),
    encode("test4"),
    encode("test0"), 
    encode("test1"),
    encode("test2"), 
    encode("test3"),
    encode("test4"),
    encode("test0"), 
    encode("test1"),
    encode("test2"), 
    encode("test3"),
    encode("test4"),
    encode("test0"), 
    encode("test1"),
    encode("test2"), 
    encode("test3"),
    encode("test4"),
    encode("test0"), 
    encode("test1"),
    encode("test2"), 
    encode("test3"),
    encode("test4"),
    encode("test0"), 
    encode("test1"),
    encode("test2"), 
    encode("test3"),
    encode("test4"),
    encode("test0"), 
    encode("test1"),
    encode("test2"), 
    encode("test3"),
    encode("test4"),
    encode("test0"), 
    encode("test1"),
    encode("test2"), 
    encode("test3"),
    encode("test4"),
    encode("test0"), 
    encode("test1"),
    encode("test2"), 
    encode("test3"),
    encode("test4"),
    
   };
   int i = 0;
   for( int i = 0; i< 50; i++){
    int j = 0;
     for( int j = 0; j < codes[i].length(); j++){
      inst[i][j] = (int)codes[i].charAt(j); 
     }
     inst[i][j] = 4;
   }
}
*/
//instruction array

TimedAction LED0 =  TimedAction(TIME_UNIT, led0); 
void led0(){
  if (arbitraryLedDo(0, 10, 20 , 90 , LED0, inst[0][positions[0]]) )
    ++positions[0];
}
TimedAction LED1 =  TimedAction(TIME_UNIT, led1); 
void led1(){
  if (arbitraryLedDo(1, 100, 100 ,0, LED1, inst[1][positions[1]]) )
    ++positions[1];
}
TimedAction LED2 = TimedAction(TIME_UNIT, led2);
void led2(){
  if (arbitraryLedDo(2, 32, 100, 36, LED2, inst[2][positions[2]]) )
    ++positions[2];
}
TimedAction LED3 = TimedAction(TIME_UNIT, led3);
void led3(){
  //Step 5, ORANGE
  if (arbitraryLedDo(3, 255, 69, 0, LED3, inst[3][positions[3]]) )
    ++positions[3];
}
TimedAction LED4 =  TimedAction(TIME_UNIT, led4); 
void led4(){
  if (arbitraryLedDo(4, 30,90 ,86, LED4, inst[4][positions[4]]) )
    ++positions[4];
}
TimedAction LED5 =  TimedAction(TIME_UNIT, led5); 
void led5(){
  if (arbitraryLedDo(5, 8, 11 ,85, LED5, inst[5][positions[5]]) )
    ++positions[5];
}
TimedAction LED6 = TimedAction(TIME_UNIT, led6);
void led6(){
  if (arbitraryLedDo(6, 100, 100, 0, LED6, inst[6][positions[6]]) )
    ++positions[6];
}
TimedAction LED7 = TimedAction(TIME_UNIT, led7);
void led7(){
  if (arbitraryLedDo(7, 100, 50, 11, LED7, inst[7][positions[7]]) )
    ++positions[7];
}
TimedAction LED8 = TimedAction(TIME_UNIT, led8);
void led8(){
  if (arbitraryLedDo(8, 30, 90, 0, LED8, inst[8][positions[8]]) )
    ++positions[8];
}
TimedAction LED9 = TimedAction(TIME_UNIT, led9);
void led9(){
  if (arbitraryLedDo(9, 100, 0, 0, LED9, inst[9][positions[9]]) )
    ++positions[9];
}
TimedAction LED10 =  TimedAction(TIME_UNIT, led10); 
void led10(){
  if (arbitraryLedDo(10, 100, 11 ,100, LED10, inst[10][positions[10]]) )
    ++positions[10];
}
TimedAction LED11 =  TimedAction(TIME_UNIT, led11); 
void led11(){
  if (arbitraryLedDo(11, 0, 0 ,100, LED11, inst[11][positions[11]]) )
    ++positions[11];
}
TimedAction LED12 = TimedAction(TIME_UNIT, led12);
void led12(){
  if (arbitraryLedDo(12, 30, 100, 100, LED12, inst[12][positions[12]]) )
    ++positions[12];
}
TimedAction LED13 = TimedAction(TIME_UNIT, led13);
void led13(){
  if (arbitraryLedDo(13, 56, 100, 91, LED13, inst[13][positions[13]]) )
    ++positions[13];
}
TimedAction LED14 =  TimedAction(TIME_UNIT, led14); 
void led14(){
  if (arbitraryLedDo(14, 100, 0 ,0, LED14, inst[14][positions[14]]) )
    ++positions[14];
}
TimedAction LED15 =  TimedAction(TIME_UNIT, led15); 
void led15(){
  //step 1 START GREEN
  if (arbitraryLedDo(15, 0, 255 ,0, LED15, inst[15][positions[15]]) )
    ++positions[15];
}
TimedAction LED16 = TimedAction(TIME_UNIT, led16);
void led16(){
  if (arbitraryLedDo(16, 8, 100, 13, LED16, inst[16][positions[16]]) )
    ++positions[16];
}
TimedAction LED17 = TimedAction(TIME_UNIT, led17);
void led17(){
  if (arbitraryLedDo(17, 0, 0, 94, LED17, inst[17][positions[17]]) )
    ++positions[17];
}
TimedAction LED18 = TimedAction(TIME_UNIT, led18);
void led18(){
  if (arbitraryLedDo(18, 90, 0, 0, LED18, inst[18][positions[18]]) )
    ++positions[18];
}
TimedAction LED19 = TimedAction(TIME_UNIT, led19);
void led19(){
  if (arbitraryLedDo(19, 8, 95, 95, LED19, inst[19][positions[19]]) )
    ++positions[19];
}
TimedAction LED20 =  TimedAction(TIME_UNIT, led20); 
void led20(){
  if (arbitraryLedDo(20, 20, 89 ,23, LED20, inst[20][positions[20]]) )
    ++positions[20];
}
TimedAction LED21 =  TimedAction(TIME_UNIT, led21); 
void led21(){
  if (arbitraryLedDo(21, 28, 100 ,40, LED21, inst[21][positions[21]]) )
    ++positions[21];
}
TimedAction LED22 = TimedAction(TIME_UNIT, led22);
void led22(){
  if (arbitraryLedDo(22, 56, 19, 100, LED22, inst[22][positions[22]]) )
    ++positions[22];
}
TimedAction LED23 = TimedAction(TIME_UNIT, led23);
void led23(){
  if (arbitraryLedDo(23, 38, 0, 84, LED23, inst[23][positions[23]]) )
    ++positions[23];
}
TimedAction LED24 =  TimedAction(TIME_UNIT, led24); 
void led24(){
  if (arbitraryLedDo(24, 100, 30 ,60, LED24, inst[24][positions[24]]) )
    ++positions[24];
}
TimedAction LED25 =  TimedAction(TIME_UNIT, led25); 
void led25(){
  if (arbitraryLedDo(25, 89, 0 ,0, LED25, inst[25][positions[25]]) )
    ++positions[25];
}
TimedAction LED26 = TimedAction(TIME_UNIT, led26);
void led26(){
  if (arbitraryLedDo(26, 0, 20, 36, LED26, inst[26][positions[26]]) )
    ++positions[26];
}
TimedAction LED27 = TimedAction(TIME_UNIT, led27);
void led27(){
  //step 3, RED
  if (arbitraryLedDo(27, 255, 0, 0, LED27, inst[27][positions[27]]) )
    ++positions[27];
}
TimedAction LED28 = TimedAction(TIME_UNIT, led28);
void led28(){
  if (arbitraryLedDo(28, 69, 0, 0, LED28, inst[28][positions[28]]) )
    ++positions[28];
}
TimedAction LED29 = TimedAction(TIME_UNIT, led29);
void led29(){
  if (arbitraryLedDo(29, 11, 37, 95, LED29, inst[29][positions[29]]) )
    ++positions[29];
}
TimedAction LED30 =  TimedAction(TIME_UNIT, led30); 
void led30(){
  if (arbitraryLedDo(30, 100, 57 ,9, LED30, inst[30][positions[30]]) )
    ++positions[30];
}
TimedAction LED31 =  TimedAction(TIME_UNIT, led31); 
void led31(){
  //STEP 2 PURPLE
  if (arbitraryLedDo(31, 255, 0 ,255, LED31, inst[31][positions[31]]) )
    ++positions[31];
}
TimedAction LED32 = TimedAction(TIME_UNIT, led32);
void led32(){
  if (arbitraryLedDo(32, 100, 45, 13, LED32, inst[32][positions[32]]) )
    ++positions[32];
}
TimedAction LED33 = TimedAction(TIME_UNIT, led33);
void led33(){
  if (arbitraryLedDo(33, 45, 99, 16, LED33, inst[33][positions[33]]) )
    ++positions[33];
}
TimedAction LED34 =  TimedAction(TIME_UNIT, led34); 
void led34(){
  //step 4, BLUE
  if (arbitraryLedDo(34, 0, 0 ,255, LED34, inst[34][positions[34]]) )
    ++positions[34];
}
TimedAction LED35 =  TimedAction(TIME_UNIT, led35); 
void led35(){
  if (arbitraryLedDo(35, 8, 70 ,100, LED35, inst[35][positions[35]]) )
    ++positions[35];
}
TimedAction LED36 = TimedAction(TIME_UNIT, led36);
void led36(){
  if (arbitraryLedDo(36, 64, 0, 0, LED36, inst[36][positions[36]]) )
    ++positions[36];
}
TimedAction LED37 = TimedAction(TIME_UNIT, led37);
void led37(){
  if (arbitraryLedDo(37, 100, 50, 17, LED37, inst[37][positions[37]]) )
    ++positions[37];
}
TimedAction LED38 = TimedAction(TIME_UNIT, led38);
void led38(){
  //STEP 6 blue
  if (arbitraryLedDo(38, 0, 0, 255, LED38, inst[38][positions[38]]) )
    ++positions[38];
}
TimedAction LED39 = TimedAction(TIME_UNIT, led39);
void led39(){
  if (arbitraryLedDo(39, 100, 62, 10, LED39, inst[39][positions[39]]) )
    ++positions[39];
}
/*RIP Sweet prince
TimedAction LED40 =  TimedAction(TIME_UNIT, led40); 
void led40(){
  if (arbitraryLedDo(40, 84, 17 ,19 , LED40, inst[40][positions[40]]) )
    ++positions[40];
}
TimedAction LED41 =  TimedAction(TIME_UNIT, led41); 
void led41(){
  //step 2, PURPLE
  if (arbitraryLedDo(41, 255, 255 ,255, LED41, inst[41][positions[41]]) )
    ++positions[41];
}
TimedAction LED42 = TimedAction(TIME_UNIT, led42);
void led42(){
  if (arbitraryLedDo(42, 70, 20, 30, LED42, inst[42][positions[42]]) )
    ++positions[42];
}
TimedAction LED43 = TimedAction(TIME_UNIT, led43);
void led43(){
  if (arbitraryLedDo(43, 40, 0, 100, LED43, inst[43][positions[43]]) )
    ++positions[43];
}
TimedAction LED44 =  TimedAction(TIME_UNIT, led44); 
void led44(){
  if (arbitraryLedDo(44, 90, 89 ,0, LED44, inst[44][positions[44]]) )
    ++positions[44];
}
TimedAction LED45 =  TimedAction(TIME_UNIT, led45); 
void led45(){
  if (arbitraryLedDo(45, 100, 50 ,11, LED45, inst[45][positions[45]]) )
    ++positions[45];
}
TimedAction LED46 = TimedAction(TIME_UNIT, led46);
void led46(){
  if (arbitraryLedDo(46, 12, 100, 10, LED46, inst[46][positions[46]]) )
    ++positions[46];
}
TimedAction LED47 = TimedAction(TIME_UNIT, led47);
void led47(){
  if (arbitraryLedDo(47, 61, 100, 13, LED47, inst[47][positions[47]]) )
    ++positions[47];
}
TimedAction LED48 = TimedAction(TIME_UNIT, led48);
void led48(){
  //step 6, END, BLUE
  if (arbitraryLedDo(48, 0, 0, 255, LED48, inst[48][positions[48]]) )
    ++positions[48];
}
TimedAction LED49 = TimedAction(TIME_UNIT, led49);
void led49(){
  if (arbitraryLedDo(49, 39, 100, 49, LED49, inst[49][positions[49]]) )
    ++positions[49];
}
*/

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
          //space(ledNum, r, g, b);//technically useless
          action.setInterval(4*TIME_UNIT);
          break;
        case 3: 
          //sEnd(ledNum, r, g, b);//technically usless
          action.setInterval(6*TIME_UNIT);
          break;
        case 4://needed at end of each instuctionlist
          positions[ledNum] = 0;
          action.setInterval(6*TIME_UNIT);
          return false;//needed so the loop does not increment after being set to 0, stops eating first instruction
          break;
    }
    if(positions[ledNum] > 21){
      positions[ledNum] = 0;
    }
    return true;
  }
}
 
 
//____________________________________main loop____________________________
void loop() {    
    LED0.check();
    LED1.check();
    LED2.check();
    LED3.check();
    LED4.check();
    LED5.check();
    LED6.check();
    LED7.check();
    LED8.check();
    LED9.check();
    LED10.check();
    LED11.check();
    LED12.check();
    LED13.check();
    LED14.check();
    LED15.check();
    LED16.check();
    LED17.check();
    LED18.check();
    LED19.check();
    LED20.check();
    LED21.check();
    LED22.check();
    LED23.check();
    LED24.check();
    LED25.check();
    LED26.check();
    LED27.check();
    LED28.check();
    LED29.check();
    LED30.check();
    LED31.check();
    LED32.check();
    LED33.check();
    LED34.check();
    LED35.check();
    LED36.check();
    LED37.check();
    LED38.check();
    LED39.check();
//    LED40.check();
//    LED41.check();
//    LED42.check();
//    LED43.check();
//    LED44.check();
//    LED45.check();
//    LED46.check();
//    LED47.check();
//    LED48.check();
//    LED49.check();
//    leds[40] = CRGB(255,255,0);
    FastLED.show();
}
 
  
