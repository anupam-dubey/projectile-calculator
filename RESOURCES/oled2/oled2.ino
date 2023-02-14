#include "U8glib.h"
#include "sheet1.h"
#include <Keypad.h>
#define CLK 5
#define DT 4
#define SW 3
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

U8GLIB_SH1106_128X64 u8g(13, 11, 10, 9, 8);  // D0=13, D1=11, CS=10, DC=9, Reset=8
byte rowPins[ROWS] = {A1, A0, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad
//Create an object of keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


  int i=0,prev_i;
  int x=0;

const uint8_t took_bitmap[] U8G_PROGMEM = {
  0x03,         // 00000011 
  0x03,         // 00000011
  0x03,         // 00000011
  0x23,         // 00100011
  0x43,         // 01000011
  0xff,         // 11111111
  0x40,         // 01000000 
  0x20          // 00100000
};
 
void read_input(uint8_t digits)
{ uint8_t dig[5]={0,0,0,0,0};
  long number=0L;
   uint8_t pos=0;
  char key;
  u8g.firstPage();  

do {
    u8g.setFont(u8g_font_helvB10);  
    u8g.drawStr(30, 12, "Enter-----"); 
    u8g.setFont(u8g_font_fub25n);  
    u8g.setPrintPos(20, 50);  
    u8g.print("00000");
  } while( u8g.nextPage() );
  do
  {
     key = keypad.getKey();// Read the key
    // Print if key pressed
   if(key>='0' && key<='9')
 {
   switch(pos)
   {
     case 0:dig[0]=key-'0';pos=1;break;
     case 1:dig[1]=dig[0];dig[0]=key-'0';pos=2;break;
     case 2:dig[2]=dig[1];dig[1]=dig[0];dig[0]=key-'0';pos=3;break;
     case 3:dig[3]=dig[2];dig[2]=dig[1];dig[1]=dig[0];dig[0]=key-'0';pos=4;break;
     case 4:dig[4]=dig[3];dig[3]=dig[2];dig[2]=dig[1];dig[1]=dig[0];dig[0]=key-'0';pos=0;break;
   }    
   number=(dig[4]*10000L)+(dig[3]*1000L)+(dig[2]*100L)+(dig[1]*10L)+dig[0];   
   u8g.firstPage();
    do {
    u8g.setPrintPos(20, 50);  
    u8g.print(number);
    } while( u8g.nextPage() );
  }
  }
  while(key!='D');
  u8g.firstPage();
    do {
   
    } while( u8g.nextPage() );
  
  
}
void setup() {
  pinMode(CLK,INPUT);
  pinMode(DT,INPUT);
  pinMode(SW, INPUT_PULLUP); 
  u8g.firstPage();  
  do {
    u8g.setFont(u8g_font_helvB10);  
    u8g.drawStr(30, 10, "Welcome "); 
    u8g.drawStr(30, 30, "To Aimsinte");
    u8g.drawStr(10, 50, "AMIT AHKE");
   
  } while( u8g.nextPage() );
  delay(2000); 
  read_input(0); 
}
void loop() {
  
   
}
