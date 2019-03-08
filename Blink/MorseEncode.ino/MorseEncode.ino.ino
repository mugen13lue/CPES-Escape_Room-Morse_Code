

void setup() {
  // put your setup code here, to run once:
  pinMode( 0, OUTPUT );
  digitalWrite( 1, LOW );
  Serial.begin(9600);
}

//Define the LED Pin
#define PIN_OUT        9
//Define unit length in ms
#define UNIT_LENGTH    250

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

void loop()
{
  delay(5000);
  String morseWord = encode( "SOS " );
  Serial.print(morseWord);
  /*for(int i=0; i<=morseWord.length(); i++)
  {
    switch( morseWord[i] )
    {
      case '.': //dit
        digitalWrite( PIN_OUT, HIGH );
        delay( UNIT_LENGTH );
        digitalWrite( PIN_OUT, LOW );
        delay( UNIT_LENGTH );
          
        break;

      case '-': //dah
        digitalWrite( PIN_OUT, HIGH );
        delay( UNIT_LENGTH*3 );
        digitalWrite( PIN_OUT, LOW );
        delay( UNIT_LENGTH );
          
        break;

      case ' ': //gap
        delay( UNIT_LENGTH );
    }
  
  }*/
}

String encode(const char *string)
{
  size_t i, j;
  String morseWord = "";
  
  for( i = 0; string[i]; ++i )
  {
    for( j = 0; j < sizeof MorseMap / sizeof *MorseMap; ++j )
    {
      if( toupper(string[i]) == MorseMap[j].letter )
      {
        morseWord += MorseMap[j].code;
        break;
      }
    }
    morseWord += " "; //Add tailing space to seperate the chars
  }

  return morseWord;  
}

String decode(String morse)
{
  String msg = "";
  
  int lastPos = 0;
  int pos = morse.indexOf(' ');
  while( lastPos <= morse.lastIndexOf(' ') )
  {    
    for( int i = 0; i < sizeof MorseMap / sizeof *MorseMap; ++i )
    {
      if( morse.substring(lastPos, pos) == MorseMap[i].code )
      {
        msg += MorseMap[i].letter;
      }
    }

    lastPos = pos+1;
    pos = morse.indexOf(' ', lastPos);
    
    // Handle white-spaces between words (7 spaces)
    while( morse[lastPos] == ' ' && morse[pos+1] == ' ' )
    {
      pos ++;
    }
  }

  return msg;
}
