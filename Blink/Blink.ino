
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


//_____________________________________________________________-all that shit____________________________________

int positions[50] = {};
//position array
/*
int inst[50][50] = {
  {0,0,0,2,1,1,1,2,0,0,0}, //0
  {0,0,0,2,1,1,1,2,0,0,0}, //1
  {0,0,0,2,1,1,1,2,0,0,0}, //2 
  {0,0,0,2,1,1,1,2,0,0,0}, //3
  {0,0,0,2,1,1,1,2,0,0,0}, //4
  {0,0,0,2,1,1,1,2,0,0,0}, //5
  {0,0,0,2,1,1,1,2,0,0,0}, //6
  {0,0,0,2,1,1,1,2,0,0,0}, //7
  {0,0,0,2,1,1,1,2,0,0,0}, //8
  {0,0,0,2,1,1,1,2,0,0,0}, //9
  {0,0,0,2,1,1,1,2,0,0,0}, //10
  {0,0,0,2,1,1,1,2,0,0,0}, //11
  {0,0,0,2,1,1,1,2,0,0,0}, //12 
  {0,0,0,2,1,1,1,2,0,0,0}, //13
  {0,0,0,2,1,1,1,2,0,0,0}, //14
  {0,0,0,2,1,1,1,2,0,0,0}, //15
  {0,0,0,2,1,1,1,2,0,0,0}, //16
  {0,0,0,2,1,1,1,2,0,0,0}, //17
  {0,0,0,2,1,1,1,2,0,0,0}, //18
  {0,0,0,2,1,1,1,2,0,0,0}, //19
  {0,0,0,2,1,1,1,2,0,0,0}, //20
  {0,0,0,2,1,1,1,2,0,0,0}, //21
  {0,0,0,2,1,1,1,2,0,0,0}, //22 
  {0,0,0,2,1,1,1,2,0,0,0}, //23
  {0,0,0,2,1,1,1,2,0,0,0}, //24
  {0,0,0,2,1,1,1,2,0,0,0}, //25
  {0,0,0,2,1,1,1,2,0,0,0}, //26
  {0,0,0,2,1,1,1,2,0,0,0}, //27
  {0,0,0,2,1,1,1,2,0,0,0}, //28
  {0,0,0,2,1,1,1,2,0,0,0}, //29
  {0,0,0,2,1,1,1,2,0,0,0}, //30
  {0,0,0,2,1,1,1,2,0,0,0}, //31
  {0,0,0,2,1,1,1,2,0,0,0}, //32 
  {0,0,0,2,1,1,1,2,0,0,0}, //33
  {0,0,0,2,1,1,1,2,0,0,0}, //34
  {0,0,0,2,1,1,1,2,0,0,0}, //35
  {0,0,0,2,1,1,1,2,0,0,0}, //36
  {0,0,0,2,1,1,1,2,0,0,0}, //37
  {0,0,0,2,1,1,1,2,0,0,0}, //38
  {0,0,0,2,1,1,1,2,0,0,0}, //39
  {0,0,0,2,1,1,1,2,0,0,0}, //40
  {0,0,0,2,1,1,1,2,0,0,0}, //41
  {0,0,0,2,1,1,1,2,0,0,0}, //42 
  {0,0,0,2,1,1,1,2,0,0,0}, //43
  {0,0,0,2,1,1,1,2,0,0,0}, //44
  {0,0,0,2,1,1,1,2,0,0,0}, //45
  {0,0,0,2,1,1,1,2,0,0,0}, //46
  {0,0,0,2,1,1,1,2,0,0,0}, //47
  {0,0,0,2,1,1,1,2,0,0,0}, //48
  {0,0,0,2,1,1,1,2,0,0,0}, //49
 
  };
*/
/*
void makeinstr(){
   String codes[50] = {
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
    encode("test0"), 
    encode("test1"),
    encode("test2"), 
    encode("test3"),
    encode("test4"),
    
   };
   for( int i = 0; i< 50; i++){
     for( int j = 0; j < codes[i].length(); j++){
      inst[i][j] = codes[i].charAt(j); 
     }
   }

}
//instruction array
*/
TimedAction LED0 =  TimedAction(TIME_UNIT, led0); 
void led0(){
  int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(0, 128, 0 ,0, LED0, arr[positions[0]]) )
    ++positions[0];
}
TimedAction LED1 =  TimedAction(TIME_UNIT, led1); 
void led1(){
  int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(1, 128, 0 ,0, LED1, arr[positions[1]]) )
    ++positions[1];
}
TimedAction LED2 = TimedAction(TIME_UNIT, led2);
void led2(){
  int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(2, 128, 0, 0, LED2, arr[positions[2]]) )
    ++positions[2];
}
TimedAction LED3 = TimedAction(TIME_UNIT, led3);
void led3(){
  int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(3, 128, 0, 0, LED3, arr[positions[3]]) )
    ++positions[3];
}
TimedAction LED4 =  TimedAction(TIME_UNIT, led4); 
void led4(){
  int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(4, 128, 0 ,0, LED4, arr[positions[4]]) )
    ++positions[4];
}
TimedAction LED5 =  TimedAction(TIME_UNIT, led5); 
void led5(){
  int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(5, 128, 0 ,0, LED5, arr[positions[5]]) )
    ++positions[5];
}
TimedAction LED6 = TimedAction(TIME_UNIT, led6);
void led6(){
  int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(6, 128, 0, 0, LED6, arr[positions[6]]) )
    ++positions[6];
}
TimedAction LED7 = TimedAction(TIME_UNIT, led7);
void led7(){
  int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(7, 128, 0, 0, LED7, arr[positions[7]]) )
    ++positions[7];
}
TimedAction LED8 = TimedAction(TIME_UNIT, led8);
void led8(){
  int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(8, 128, 0, 0, LED8, arr[positions[8]]) )
    ++positions[8];
}
TimedAction LED9 = TimedAction(TIME_UNIT, led9);
void led9(){
  int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(9, 128, 0, 0, LED9, arr[positions[9]]) )
    ++positions[9];
}
TimedAction LED10 =  TimedAction(TIME_UNIT, led10); 
void led10(){
  int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(10, 128, 0 ,0, LED10, arr[positions[10]]) )
    ++positions[10];
}
TimedAction LED11 =  TimedAction(TIME_UNIT, led11); 
void led11(){
  int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(11, 128, 0 ,0, LED11, arr[positions[11]]) )
    ++positions[11];
}
TimedAction LED12 = TimedAction(TIME_UNIT, led12);
void led12(){
  int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(12, 128, 0, 0, LED12, arr[positions[12]]) )
    ++positions[12];
}
TimedAction LED13 = TimedAction(TIME_UNIT, led13);
void led13(){
  int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(13, 128, 0, 0, LED13, arr[positions[13]]) )
    ++positions[13];
}
TimedAction LED14 =  TimedAction(TIME_UNIT, led14); 
void led14(){
  int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(14, 128, 0 ,0, LED14, arr[positions[14]]) )
    ++positions[14];
}
TimedAction LED15 =  TimedAction(TIME_UNIT, led15); 
void led15(){
  int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(15, 128, 0 ,0, LED15, arr[positions[15]]) )
    ++positions[15];
}
TimedAction LED16 = TimedAction(TIME_UNIT, led16);
void led16(){
  int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(16, 128, 0, 0, LED16, arr[positions[16]]) )
    ++positions[16];
}
TimedAction LED17 = TimedAction(TIME_UNIT, led17);
void led17(){
  int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(17, 128, 0, 0, LED17, arr[positions[17]]) )
    ++positions[17];
}
TimedAction LED18 = TimedAction(TIME_UNIT, led18);
void led18(){
  int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(18, 128, 0, 0, LED18, arr[positions[18]]) )
    ++positions[18];
}
TimedAction LED19 = TimedAction(TIME_UNIT, led19);
void led19(){
  int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(19, 128, 0, 0, LED19, arr[positions[19]]) )
    ++positions[19];
}
TimedAction LED20 =  TimedAction(TIME_UNIT, led20); 
void led20(){
  int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(20, 128, 0 ,0, LED20, arr[positions[20]]) )
    ++positions[20];
}
TimedAction LED21 =  TimedAction(TIME_UNIT, led21); 
void led21(){
  int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(21, 128, 0 ,0, LED21, arr[positions[21]]) )
    ++positions[21];
}
TimedAction LED22 = TimedAction(TIME_UNIT, led22);
void led22(){
  int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(22, 128, 0, 0, LED22, arr[positions[22]]) )
    ++positions[22];
}
TimedAction LED23 = TimedAction(TIME_UNIT, led23);
void led23(){
  int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(23, 128, 0, 0, LED23, arr[positions[23]]) )
    ++positions[23];
}
TimedAction LED24 =  TimedAction(TIME_UNIT, led24); 
void led24(){
  int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(24, 128, 0 ,0, LED24, arr[positions[24]]) )
    ++positions[24];
}
TimedAction LED25 =  TimedAction(TIME_UNIT, led25); 
void led25(){
  int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(25, 128, 0 ,0, LED25, arr[positions[25]]) )
    ++positions[25];
}
TimedAction LED26 = TimedAction(TIME_UNIT, led26);
void led26(){
  int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(26, 128, 0, 0, LED26, arr[positions[26]]) )
    ++positions[26];
}
TimedAction LED27 = TimedAction(TIME_UNIT, led27);
void led27(){
  int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(27, 128, 0, 0, LED27, arr[positions[27]]) )
    ++positions[27];
}
TimedAction LED28 = TimedAction(TIME_UNIT, led28);
void led28(){
 int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(28, 128, 0, 0, LED28, arr[positions[28]]) )
    ++positions[28];
}
TimedAction LED29 = TimedAction(TIME_UNIT, led29);
void led29(){
  int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(29, 128, 0, 0, LED29, arr[positions[29]]) )
    ++positions[29];
}
TimedAction LED30 =  TimedAction(TIME_UNIT, led30); 
void led30(){
  int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(30, 128, 0 ,0, LED30, arr[positions[30]]) )
    ++positions[30];
}
TimedAction LED31 =  TimedAction(TIME_UNIT, led31); 
void led31(){
  int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(31, 128, 0 ,0, LED31, arr[positions[31]]) )
    ++positions[31];
}
TimedAction LED32 = TimedAction(TIME_UNIT, led32);
void led32(){
  int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(32, 128, 0, 0, LED32, arr[positions[32]]) )
    ++positions[32];
}
TimedAction LED33 = TimedAction(TIME_UNIT, led33);
void led33(){
  int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(33, 128, 0, 0, LED33, arr[positions[33]]) )
    ++positions[33];
}
TimedAction LED34 =  TimedAction(TIME_UNIT, led34); 
void led34(){
  int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(34, 128, 0 ,0, LED34, arr[positions[34]]) )
    ++positions[34];
}
TimedAction LED35 =  TimedAction(TIME_UNIT, led35); 
void led35(){
  int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(35, 128, 0 ,0, LED35, arr[positions[35]]) )
    ++positions[35];
}
TimedAction LED36 = TimedAction(TIME_UNIT, led36);
void led36(){
  int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(36, 128, 0, 0, LED36, arr[positions[36]]) )
    ++positions[36];
}
TimedAction LED37 = TimedAction(TIME_UNIT, led37);
void led37(){
  int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(37, 128, 0, 0, LED37, arr[positions[37]]) )
    ++positions[37];
}
TimedAction LED38 = TimedAction(TIME_UNIT, led38);
void led38(){
  int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(38, 128, 0, 0, LED38, arr[positions[38]]) )
    ++positions[38];
}
TimedAction LED39 = TimedAction(TIME_UNIT, led39);
void led39(){
  int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(39, 128, 0, 0, LED39, arr[positions[39]]) )
    ++positions[39];
}
TimedAction LED40 =  TimedAction(TIME_UNIT, led40); 
void led40(){
  int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(40, 128, 0 ,0, LED40, arr[positions[40]]) )
    ++positions[40];
}
TimedAction LED41 =  TimedAction(TIME_UNIT, led41); 
void led41(){
  int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(41, 128, 0 ,0, LED41, arr[positions[41]]) )
    ++positions[41];
}
TimedAction LED42 = TimedAction(TIME_UNIT, led42);
void led42(){
  int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(42, 128, 0, 0, LED42, arr[positions[42]]) )
    ++positions[42];
}
TimedAction LED43 = TimedAction(TIME_UNIT, led43);
void led43(){
  int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(43, 128, 0, 0, LED43, arr[positions[43]]) )
    ++positions[43];
}
TimedAction LED44 =  TimedAction(TIME_UNIT, led44); 
void led44(){
  int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(44, 128, 0 ,0, LED44, arr[positions[44]]) )
    ++positions[44];
}
TimedAction LED45 =  TimedAction(TIME_UNIT, led45); 
void led45(){
  int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(45, 128, 0 ,0, LED45, arr[positions[45]]) )
    ++positions[45];
}
TimedAction LED46 = TimedAction(TIME_UNIT, led46);
void led46(){
  int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(46, 128, 0, 0, LED46, arr[positions[46]]) )
    ++positions[46];
}
TimedAction LED47 = TimedAction(TIME_UNIT, led47);
void led47(){
  int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(47, 128, 0, 0, LED47, arr[positions[47]]) )
    ++positions[47];
}
TimedAction LED48 = TimedAction(TIME_UNIT, led48);
void led48(){
  int arr[] = {0,0,0,2,1,1,1,2,0,0,0,9};
  if (arbitraryLedDo(48, 128, 0, 0, LED48, arr[positions[48]]) )
    ++positions[48];
}
TimedAction LED49 = TimedAction(TIME_UNIT, led49);
void led49(){
  int arr[] = {0,2,1,3,9};
  if (arbitraryLedDo(49, 128, 0, 0, LED49, arr[positions[49]]) )
    ++positions[49];
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
          //space(ledNum, r, g, b);//technically useless
          action.setInterval(4*TIME_UNIT);
          break;
        case 3: 
          //sEnd(ledNum, r, g, b);//technically usless
          action.setInterval(6*TIME_UNIT);
          break;
        case 9://needed at end of each instuctionlist
          positions[ledNum] = 0;
          action.setInterval(0);
          return false;//needed so the loop does not increment after being set to 0, stops eating first instruction
          break;
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
    LED40.check();
    LED41.check();
    LED42.check();
    LED43.check();
    LED44.check();
    LED45.check();
    LED46.check();
    LED47.check();
    LED48.check();
    LED49.check();
    FastLED.show();
}
 
  
