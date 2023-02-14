#include "U8glib.h"
#include "sheet1.h"
#include "sheet2.h"
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
  int temp_x,press_x;

 
long read_input(const char* dd)
{ uint8_t dig[5]={0,0,0,0,0};
  long number=0L;
   uint8_t pos=0;
  char key;
  u8g.firstPage();  

do {
    u8g.setFont(u8g_font_helvB12);  
    u8g.drawStr(30, 12, dd); 
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
    u8g.setFont(u8g_font_helvB12);  
    u8g.drawStr(30, 12, dd); 
    u8g.setFont(u8g_font_fub25n);  
    u8g.setPrintPos(20, 50);  
    u8g.print(number);
    } while( u8g.nextPage() );
  }
  }
  while(key!='D');
  u8g.firstPage();
    do {
   
    } while( u8g.nextPage() );
  
  return number;
}
int read_input_two(const char* dd)
{ uint8_t dig[2]={0,0};
  int number=0;
   uint8_t pos=0;
  char key;
  u8g.firstPage();  

do {
    u8g.setFont(u8g_font_helvB12);  
    u8g.drawStr(30, 12, dd); 
    u8g.setFont(u8g_font_fub25n);  
    u8g.setPrintPos(30, 50);  
    u8g.print("00");
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
     case 1:dig[1]=dig[0];dig[0]=key-'0';pos=0;break;
       }    
   number=(dig[1]*10)+dig[0];   
   u8g.firstPage();
    do {
    u8g.setFont(u8g_font_helvB12);  
    u8g.drawStr(30, 12, dd); 
    u8g.setFont(u8g_font_fub25n);    
    u8g.setPrintPos(30, 50);  
    u8g.print(number);
    } while( u8g.nextPage() );
  }
  }
  while(key!='D');
  u8g.firstPage();
    do {
   
    } while( u8g.nextPage() );
  
  return number;
}
int read_input_three(const char* dd)
{ uint8_t dig[3]={0,0,0};
  int number=0;
   uint8_t pos=0;
  char key;
  u8g.firstPage();  

do {
    u8g.setFont(u8g_font_helvB12);  
    u8g.drawStr(30, 12, dd); 
    u8g.setFont(u8g_font_fub25n);  
    u8g.setPrintPos(25, 50);  
    u8g.print("000");
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
     case 2:dig[2]=dig[1];dig[1]=dig[0];dig[0]=key-'0';pos=0;break;
       }    
   number=(dig[2]*100)+(dig[1]*10)+dig[0];   
   u8g.firstPage();
    do {
    u8g.setFont(u8g_font_helvB12);  
    u8g.drawStr(30, 12, dd); 
    u8g.setFont(u8g_font_fub25n);  
    u8g.setPrintPos(25, 50);  
    u8g.print(number);
    } while( u8g.nextPage() );
  }
  }
  while(key!='D');
  u8g.firstPage();
    do {
   
    } while( u8g.nextPage() );
  
  return number;
}
uint8_t select_msg(const char* header,const char* opt1,const char* opt2,bool isthree)
{ uint8_t rtype=0; 
  char key;
  u8g.firstPage();  
  do {
    u8g.setFont(u8g_font_helvB12);  
    u8g.drawStr(30, 12, header);
    u8g.drawBox(28, 15, 65, 19);//x1,y1,w,height
    u8g.setColorIndex(0);
    u8g.drawStr(30, 30, opt1); 
    u8g.setColorIndex(1);
    u8g.drawStr(30, 48, opt2);
    if(isthree==1)
    {
    u8g.drawStr(30, 63, "C- NILL");  
    }
      } while( u8g.nextPage() );
  do
  {
     key = keypad.getKey();// Read the key
     if(key=='A')
     {
      u8g.firstPage();  
  do {
    u8g.setFont(u8g_font_helvB12);  
    u8g.drawStr(30, 12, header);
    u8g.drawBox(28, 15, 65, 19);//x1,y1,w,height
    u8g.setColorIndex(0);
    u8g.drawStr(30, 30, opt1); 
    u8g.setColorIndex(1);
    u8g.drawStr(30, 48, opt2);
    if(isthree==1)
    {
    u8g.drawStr(30, 63, "C- NILL");  
    }
      } while( u8g.nextPage() );
      rtype=0;
     }
     else if(key=='B')
     {
       u8g.firstPage();  
  do {
    u8g.setFont(u8g_font_helvB12);  
    u8g.drawStr(30, 12, header);
    
    u8g.drawStr(30, 30, opt1); 
    u8g.drawBox(28, 33, 65, 19);//x1,y1,w,height   
    u8g.setColorIndex(0);
    u8g.drawStr(30, 48, opt2);
    u8g.setColorIndex(1);
     if(isthree==1)
    {
    u8g.drawStr(30, 63, "C- NILL");  
    }
      } while( u8g.nextPage() );
      rtype=1;
     }
     else if(key=='C' && isthree==1)
     {
       u8g.firstPage();  
  do {
    u8g.setFont(u8g_font_helvB12);  
    u8g.drawStr(30, 12, header);    
    u8g.drawStr(30, 30, opt1); 
    u8g.drawStr(30, 48, opt2);
    u8g.drawBox(28, 50, 65, 19);//x1,y1,w,height   
    u8g.setColorIndex(0);    
    u8g.drawStr(30, 63, "C- NILL");  
    u8g.setColorIndex(1);
      } while( u8g.nextPage() );
      rtype=2;
     }
  }
  while(key!='D');
  return rtype;
     
}
uint8_t select_msg4()
{ uint8_t rtype=0; 
  char key;
  u8g.firstPage();  
  do {
    u8g.setFont(u8g_font_helvB12);  
    u8g.drawStr(30, 12, "L WIND");
    u8g.drawBox(0, 15, 58, 19);//x1,y1,w,height
    u8g.setColorIndex(0);
    u8g.drawStr(0, 30, "A)12-6"); 
    u8g.setColorIndex(1);
    u8g.drawStr(0, 48, "B)6-12");
    u8g.drawStr(60, 30, "C)1-7");
    u8g.drawStr(60, 48, "#)7-1");

      } while( u8g.nextPage() );
  do
  {
     key = keypad.getKey();// Read the key
     if(key=='A')
     {
       u8g.firstPage();  
  do {
    u8g.setFont(u8g_font_helvB12);  
    u8g.drawStr(30, 12, "L WIND");
    u8g.drawBox(0, 15, 58, 19);//x1,y1,w,height
    u8g.setColorIndex(0);
    u8g.drawStr(0, 30, "A)12-6"); 
    u8g.setColorIndex(1);
    u8g.drawStr(0, 48, "B)6-12");
    u8g.drawStr(60, 30, "C)1-7");
    u8g.drawStr(60, 48, "#)7-1");

      } while( u8g.nextPage() );
      rtype=0;
     }
     else if(key=='B')
     {
       u8g.firstPage();  
     do {
          u8g.setFont(u8g_font_helvB12);  
          u8g.drawStr(30, 12, "L WIND");
          u8g.drawStr(0, 30, "A)12-6"); 
          u8g.drawBox(0, 35, 58, 19);//x1,y1,w,height
          u8g.setColorIndex(0);          
          u8g.drawStr(0, 48, "B)6-12");
          u8g.setColorIndex(1);
          u8g.drawStr(60, 30, "C)1-7");
          u8g.drawStr(60, 48, "#)7-1");

      } while( u8g.nextPage() );
      rtype=1;
     }
     else if(key=='C')
     {
       u8g.firstPage();  
     do {
          u8g.setFont(u8g_font_helvB12);  
          u8g.drawStr(30, 12, "L WIND");
          u8g.drawStr(0, 30, "A)12-6"); 
          u8g.drawStr(0, 48, "B)6-12");
          u8g.drawBox(58, 15, 58, 19);//x1,y1,w,height
          u8g.setColorIndex(0);          
          u8g.drawStr(60, 30, "C)1-7");
          u8g.setColorIndex(1);
          u8g.drawStr(60, 48, "#)7-1");

      } while( u8g.nextPage() );
      rtype=2;
     }
     else if(key=='#')
     {
       u8g.firstPage();  
     do {
          u8g.setFont(u8g_font_helvB12);  
          u8g.drawStr(30, 12, "L WIND");
          u8g.drawStr(0, 30, "A)12-6"); 
          u8g.drawStr(0, 48, "B)6-12");                   
          u8g.drawStr(60, 30, "C)1-7");
          u8g.drawBox(58, 35, 58, 19);//x1,y1,w,height
          u8g.setColorIndex(0);         
          u8g.drawStr(60, 48, "#)7-1");
          u8g.setColorIndex(1);

      } while( u8g.nextPage() );
      rtype=3;
     }
  }
  while(key!='D');
  return rtype;
     
}
void show_msg(int dly, const char* s)
{
  u8g.firstPage();  
  do {
    u8g.setFont(u8g_font_helvB14);  
    u8g.drawStr(50, 30, s);
   
  } while( u8g.nextPage() );
  delay(dly);
  u8g.firstPage();  
  do {
   } while( u8g.nextPage() );
}
int search_sheet1(uint16_t v)
{int i=0;
 uint16_t firstChar =0;
 uint16_t secChar=0;
 do
 {
  firstChar = pgm_read_word_near(sheet1y+ i);
  i++;
 }while(firstChar<v);
 return i-1; 
}
void setup() {
  long na=0L;//own gr easting
  long nb=0L;//own gr northing
  long ta=0L;//target gr easting
  long tb=0L;//target gr northing
  pinMode(CLK,INPUT);
  pinMode(DT,INPUT);
  pinMode(SW, INPUT_PULLUP); 
  u8g.firstPage();  
  do {
    u8g.setFont(u8g_font_helvB10);  
    u8g.drawStr(30, 10, "Welcome "); 
    u8g.drawStr(30, 30, "To Simputer");
    u8g.drawStr(10, 50, "-----------");
   
  } while( u8g.nextPage() );
  delay(2000); 
 // uint8_t stype=select_msg("Ammo select","A- VOG","B- GPD");
  double ft=114;
/*  int temp=search_sheet1(uint16_t (ft));
  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_helvB12);  
    u8g.setPrintPos(20, 30);
    u8g.print(temp);
  } while( u8g.nextPage() );*/
  //
  uint8_t stype;
  stype=select_msg4();
  show_msg(1000,"OK");
   u8g.firstPage();
  do {
   u8g.setFont(u8g_font_helvB12);  
    u8g.setPrintPos(20, 30);
    u8g.print(stype);
    } while( u8g.nextPage() );
    delay(1000);
 stype=select_msg("Sel C wind","A- (3-9)","B- (9-3)",1);
  show_msg(1000,"OK");
   u8g.firstPage();
  do {
   u8g.setFont(u8g_font_helvB12);  
    u8g.setPrintPos(20, 30);
    u8g.print(stype);
    } while( u8g.nextPage() );
    delay(1000);
    stype=select_msg("Ammo select","A- VOG","B- GPD",0);
  show_msg(1000,"OK");
   u8g.firstPage();
  do {
   u8g.setFont(u8g_font_helvB12);  
    u8g.setPrintPos(20, 30);
    u8g.print(stype);
    } while( u8g.nextPage() );
    delay(1000);
/*  na=read_input("OWNGR(E)"); //a
  show_msg(2000,"OK");
  nb=read_input("OWNGR(N)"); //b
  show_msg(2000,"OK");
  ta=read_input("TGTGR(E)"); //c
  show_msg(2000,"OK");
  tb=read_input("TGTGR(N)"); //d
  show_msg(2000,"OK");
  double ft =sq(tb-nb)+sq(ta-na);
  ft=sqrt(ft);
   u8g.firstPage();
  do {
    u8g.setFont(u8g_font_helvB12);  
    u8g.setPrintPos(20, 30);
    u8g.print(ft,0);
  } while( u8g.nextPage() );
  delay(2000);*/
 /* temp_x=read_input_two("Temp(C)"); //temperature
  show_msg(2000,"OK");
  press_x=read_input_three("Presre(mm)"); //pressure
  show_msg(2000,"OK");*/
 /* u8g.firstPage();
  do {
    u8g.setFont(u8g_font_helvB12);  
   // u8g.setPrintPos(20, 30);
   // u8g.print(temp_x);
   // u8g.print(press_x);
     
    u8g.setColorIndex(1);
    u8g.drawBox(0, 0, 80, 20);//x1,y1,x2,y2
    u8g.setColorIndex(0);
    u8g.drawStr( 2, 14, "Gray Level");
  } while( u8g.nextPage() );
  u8g.setColorIndex(1);
  delay(2000);*/
 /* uint8_t stype=select_msg("Sel C wind","A- (3-9)","B- (9-3)");
  show_msg(2000,"OK");
  u8g.firstPage();  
  do {
   u8g.setFont(u8g_font_helvB12);  
    u8g.setPrintPos(20, 30);
    u8g.print(stype);
    } while( u8g.nextPage() );
    delay(1000);
  stype=select_msg("Sel L wind","A- (12-6)","B- (6-12)");
  show_msg(2000,"OK");
  u8g.firstPage();  
  do {
   u8g.setFont(u8g_font_helvB12);  
    u8g.setPrintPos(20, 30);
    u8g.print(stype);
    } while( u8g.nextPage() );*/
  /*
  /*
   u8g.firstPage();  
  do {u8g.setColorIndex(1);
    u8g.setFont(u8g_font_helvB10);  
    u8g.drawStr(30, 10, "Welcome "); 
    u8g.drawStr(30, 30, "To Simputer");
    u8g.drawStr(10, 50, "-----------");
   
  } while( u8g.nextPage() );*/
}
void loop() {
  
   
}
