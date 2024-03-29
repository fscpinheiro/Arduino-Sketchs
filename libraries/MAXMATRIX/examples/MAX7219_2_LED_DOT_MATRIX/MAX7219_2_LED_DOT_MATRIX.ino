/**********************************************************************************************************/
/* MAX7219 LED dot matrix test sketch
 * Displays text via up to 8 daisy chained dot matrix LEDs
 * 
 * Origin Author:        Marcelo Moraes - Sorocaba - SP - Brazil - July 9th, 2013
 *                       http://www.instructables.com/id/16x8-LED-dot-matrix-with-MAX7219-module/
 *                       https://code.google.com/p/arudino-maxmatrix-library/        
 *
 * Modified by:          Olaf Meier
 *                       Changed some characters and included sketch into my master design
 * 
 * Hardware connection:  10 (13) =  CLK
 *                       8 (11)  =  Din
 *                       9 (10)  =  CS   
 *                       Vcc     =  5V * Hardware connection:    
 * 
 * 
 * ToDo:
 * 
 */
/**********************************************************************************************************/
/*
 Example of output:

 */
/**********************************************************************************************************/
/**********************************************************************************************************/
/***  Declaration of global constants and initialization of variables. Add includes.  ***/
/**********************************************************************************************************/
/***  Software release and date  ***/
const char* author                =  "Olaf Meier";
const char* revision              =  "R.0.1";
const char* date                  =  "2012/09/28";

#if ARDUINO < 100
#include <WProgram.h>                              // Add other libraries on demand as requested
#else
#include <Arduino.h>                               // Needed when working with libraries
#endif
/**********************************************************************************************************/
/***  Declare constants and variables for the optional serial monitor for debugging.  ***/
int debug                         =  1;            // Debug counter; if set to 1, will write values via serial
const unsigned int baudRate       =  9600;         // Baud rate for the serial monitor

/***  Declare constants and variables for the dot matrix display. Include Libraries  ***/
#include <MaxMatrix.h>
//#include <avr/pgmspace.h>

/***  Hardware connection. Dasiy chain DOUT with DIN of the next module  ***/
int data                          =  8;            // (13) DIN pin of MAX7219 module
int load                          =  9;            // (10) CS pin of MAX7219 module
int clock                         =  10;           // (9) CLK pin of MAX7219 module

/***  Number of used MAX7219 dot matrix modules  ***/
int maxInUse                      =  1;

/***  Initialize MAX7219 library  ***/
MaxMatrix m(data, load, clock, maxInUse); 

byte buffer[100];

/***  Table according ASCII chart 32..127  ***/
/***  Initialize Sprite starting with number of rows from total.  ***/
PROGMEM prog_uchar CH[] = {
3, 8, B00000000, B00000000, B00000000, B00000000, B00000000, // space
1, 8, B01011111, B00000000, B00000000, B00000000, B00000000, // !
3, 8, B00000011, B00000000, B00000011, B00000000, B00000000, // "
5, 8, B00010100, B00111110, B00010100, B00111110, B00010100, // #
4, 8, B00100100, B01101010, B00101011, B00010010, B00000000, // $
5, 8, B01100011, B00010011, B00001000, B01100100, B01100011, // %
5, 8, B00110110, B01001001, B01010110, B00100000, B01010000, // &
1, 8, B00000011, B00000000, B00000000, B00000000, B00000000, // '
3, 8, B00011100, B00100010, B01000001, B00000000, B00000000, // (
3, 8, B01000001, B00100010, B00011100, B00000000, B00000000, // )
5, 8, B00101000, B00011000, B00001110, B00011000, B00101000, // *
5, 8, B00001000, B00001000, B00111110, B00001000, B00001000, // +
2, 8, B10110000, B01110000, B00000000, B00000000, B00000000, // ,
4, 8, B00001000, B00001000, B00001000, B00001000, B00000000, // -
2, 8, B01100000, B01100000, B00000000, B00000000, B00000000, // .
4, 8, B01100000, B00011000, B00000110, B00000001, B00000000, // /
4, 8, B00111110, B01000001, B01000001, B00111110, B00000000, // 0
3, 8, B01000010, B01111111, B01000000, B00000000, B00000000, // 1
4, 8, B01100010, B01010001, B01001001, B01000110, B00000000, // 2
4, 8, B00100010, B01000001, B01001001, B00110110, B00000000, // 3
4, 8, B00011000, B00010100, B00010010, B01111111, B00000000, // 4
4, 8, B00100111, B01000101, B01000101, B00111001, B00000000, // 5
4, 8, B00111110, B01001001, B01001001, B00110000, B00000000, // 6
4, 8, B01100001, B00010001, B00001001, B00000111, B00000000, // 7
4, 8, B00110110, B01001001, B01001001, B00110110, B00000000, // 8
4, 8, B00000110, B01001001, B01001001, B00111110, B00000000, // 9
2, 8, B01010000, B00000000, B00000000, B00000000, B00000000, // :
2, 8, B10000000, B01010000, B00000000, B00000000, B00000000, // ;
3, 8, B00010000, B00101000, B01000100, B00000000, B00000000, // <
3, 8, B00010100, B00010100, B00010100, B00000000, B00000000, // =
3, 8, B01000100, B00101000, B00010000, B00000000, B00000000, // >
4, 8, B00000010, B01011001, B00001001, B00000110, B00000000, // ?
5, 8, B00111110, B01001001, B01010101, B01011101, B00001110, // @
4, 8, B01111110, B00010001, B00010001, B01111110, B00000000, // A
4, 8, B01111111, B01001001, B01001001, B00110110, B00000000, // B
4, 8, B00111110, B01000001, B01000001, B00100010, B00000000, // C
4, 8, B01111111, B01000001, B01000001, B00111110, B00000000, // D
4, 8, B01111111, B01001001, B01001001, B01000001, B00000000, // E
4, 8, B01111111, B00001001, B00001001, B00000001, B00000000, // F
4, 8, B00111110, B01000001, B01001001, B01111010, B00000000, // G
4, 8, B01111111, B00001000, B00001000, B01111111, B00000000, // H
3, 8, B01000001, B01111111, B01000001, B00000000, B00000000, // I
4, 8, B00110000, B01000000, B01000001, B00111111, B00000000, // J
4, 8, B01111111, B00001000, B00010100, B01100011, B00000000, // K
4, 8, B01111111, B01000000, B01000000, B01000000, B00000000, // L
5, 8, B01111111, B00000010, B00001100, B00000010, B01111111, // M
5, 8, B01111111, B00000100, B00001000, B00010000, B01111111, // N
4, 8, B00111110, B01000001, B01000001, B00111110, B00000000, // O
4, 8, B01111111, B00001001, B00001001, B00000110, B00000000, // P
4, 8, B00111110, B01000001, B01000001, B10111110, B00000000, // Q
4, 8, B01111111, B00001001, B00001001, B01110110, B00000000, // R
4, 8, B01000110, B01001001, B01001001, B00110010, B00000000, // S
5, 8, B00000001, B00000001, B01111111, B00000001, B00000001, // T
4, 8, B00111111, B01000000, B01000000, B00111111, B00000000, // U
5, 8, B00001111, B00110000, B01000000, B00110000, B00001111, // V
5, 8, B00111111, B01000000, B00111000, B01000000, B00111111, // W
5, 8, B01100011, B00010100, B00001000, B00010100, B01100011, // X
5, 8, B00000111, B00001000, B01110000, B00001000, B00000111, // Y
4, 8, B01100001, B01010001, B01001001, B01000111, B00000000, // Z
2, 8, B01111111, B01000001, B00000000, B00000000, B00000000, // [
4, 8, B00000001, B00000110, B00011000, B01100000, B00000000, // \ backslash
2, 8, B01000001, B01111111, B00000000, B00000000, B00000000, // ]
3, 8, B00000010, B00000001, B00000010, B00000000, B00000000, // hat
4, 8, B01000000, B01000000, B01000000, B01000000, B00000000, // _
2, 8, B00000001, B00000010, B00000000, B00000000, B00000000, // `
4, 8, B00100000, B01010100, B01010100, B01111000, B00000000, // a
4, 8, B01111110, B01001000, B01001000, B00110000, B00000000, // b
4, 8, B00111000, B01000100, B01000100, B00101000, B00000000, // c
4, 8, B00111000, B01000100, B01000100, B01111111, B00000000, // d
4, 8, B00111000, B01010100, B01010100, B00011000, B00000000, // e
3, 8, B00001000, B01111100, B00001010, B00000000, B00000000, // f
4, 8, B10011000, B10100100, B10100100, B01111000, B00000000, // g
4, 8, B01111111, B00000100, B00000100, B01111000, B00000000, // h
3, 8, B01000100, B01111101, B01000000, B00000000, B00000000, // i
4, 8, B01000000, B10000000, B10000100, B01111101, B00000000, // j
4, 8, B01111111, B00010000, B00101000, B01000100, B00000000, // k
3, 8, B01000001, B01111111, B01000000, B00000000, B00000000, // l
5, 8, B01111100, B00000100, B01111100, B00000100, B01111000, // m
4, 8, B01111100, B00000100, B00000100, B01111000, B00000000, // n
4, 8, B00111000, B01000100, B01000100, B00111000, B00000000, // o
4, 8, B11111100, B00100100, B00100100, B00011000, B00000000, // p
4, 8, B00011000, B00100100, B00100100, B11111100, B00000000, // q
4, 8, B01111100, B00001000, B00000100, B00000100, B00000000, // r
4, 8, B01001000, B01010100, B01010100, B00100100, B00000000, // s
3, 8, B00000100, B00111111, B01000100, B00000000, B00000000, // t
4, 8, B00111100, B01000000, B01000000, B01111100, B00000000, // u
5, 8, B00011100, B00100000, B01000000, B00100000, B00011100, // v
5, 8, B00111100, B01000000, B00111100, B01000000, B00111100, // w
5, 8, B01000100, B00101000, B00010000, B00101000, B01000100, // x
4, 8, B10011100, B10100000, B10100000, B01111100, B00000000, // y
3, 8, B01100100, B01010100, B01001100, B00000000, B00000000, // z
3, 8, B00001000, B00110110, B01000001, B00000000, B00000000, // {
1, 8, B01111111, B00000000, B00000000, B00000000, B00000000, // |
3, 8, B01000001, B00110110, B00001000, B00000000, B00000000, // }
4, 8, B00001000, B00000100, B00001000, B00000100, B00000000, // ~
4, 8, B00001000, B00000100, B00001000, B00000100, B00000000, // ~
};

/***  Create the needed sentenses  ***/
char string1[] = " Hello, my name is Marcelo Moraes and...     ";
char string2[] = " I am glad to show you my Arduino scrolling dot Matrix     ";
char string3[] = " using MAX7219 IC     ";
char string4[] = " Visit my blog at:     http://arduinobymyself.blogspot.com.br     ";
char string5[] = " There you will find a lot of projects with Arduino.   ";
char string6[] = " Thanks for watching =)          ";
char string100[] = " A B C D E F G H I J K L M N O P Q R S T U V W X Y Z ";
char string101[] = " a b c d e f g h i j k l m n o p q r s t u v w x y z ";
char string102[] = " 1 2 3 4 5 6 7 8 9 0 - = ";
char string103[] = " ! @ # $ % ¨ & * ( ) _ + ";
char string104[] = " ' , . ; ~ ] ´ [ | < > : ^ } ` { / ?  ";
char string105[] = " b g f q ";
/**********************************************************************************************************/
/**********************************************************************************************************/

void setup() {
  /***  Optional Debug routine via serial monitor  ***/
  if (debug) {                                     // If you want to see some values for debugging in general...
    /***  Start class Serial with function/method begin(9600)  ***/
    /***  Instance variable .dot operator. method  ***/
    Serial.begin(baudRate);                        // ...set up the serial output
    Serial.println("Debugging activated");
  }                                                // End of debug
  /***  Show software release  ***/
  Serial.println();
  Serial.print(author);
  Serial.print("\t");
  Serial.print(revision);                         
  Serial.print("\t");
  Serial.println(date);  
  Serial.println();
/**********************************************************************************************************/
 
  m.init();                                        // Initialize module
  m.setIntensity(0);                               // Dot matix intensity 0-15
  
}                                                  // End of void setup() 
/**********************************************************************************************************/
/**********************************************************************************************************/
void loop() {

  /***  Optional Debug routine via serial monitor  ***/
  if (debug) {                                     // If TRUE 
    debug += 1;                                    // Increment the debug counter
    if (debug > 100)                               // Print only each 1xx loop
    {
      debug = 1;                                   // Reset the counter
      /***  Display your debug values here  **/
      /*
      Serial.print("abc ");
      Serial.println(variable);                    // Display value of the ADC where the buttons are connected
      */
    }


  }                                                // End of if (debug)
  /***  End of optional Debug routine via serial monitor  ***/

/*
  // this is the code if you want to entering a message via serial console
  while (Serial.available() > 0){
    byte c = Serial.read();
    Serial.println(c, DEC);
    printCharWithShift(c, 100);
  }
  delay(100);
  m.shiftLeft(false, true);
*/

  /***  Display the active sentences. printStringWithShift(string_, delay)  ***/
  //printStringWithShift(string1, 100);
  //printStringWithShift(string2, 100);
  //printStringWithShift(string3, 100);
  //printStringWithShift(string4, 100);
  //printStringWithShift(string5, 100);
  //printStringWithShift(string6, 100);

  //print sentences just for tests
  //printStringWithShift(string7, 250);
  //printStringWithShift(string8, 250);
  //printStringWithShift(string9, 250);
  //printStringWithShift(string10, 250);
  //printStringWithShift(string11, 250);
    printStringWithShift(string105, 250);
 
}                                                  // End of void loop()
/**********************************************************************************************************/
/**********************************************************************************************************/
/***  Optional functions  ***/

void printCharWithShift(char c, int shift_speed){
  if (c < 32) return;
  c -= 32;
  memcpy_P(buffer, CH + 7*c, 7);
  m.writeSprite(32, 0, buffer);
  m.setColumn(32 + buffer[0], 0);
  for (int i=0; i<buffer[0]+1; i++) 
  {
    delay(shift_speed);
    m.shiftLeft(false, false);
  }
}
/**********************************************************************************************************/
void printStringWithShift(char* s, int shift_speed){
  while (*s != 0){
    printCharWithShift(*s, shift_speed);
    s++;
  }
}
/**********************************************************************************************************/
/**********************************************************************************************************/




