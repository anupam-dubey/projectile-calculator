#include "U8glib.h"
#include "sheet1.h"
#include "sheet2.h"
#include <Keypad.h>
#define CLK 5
#define DT 4
#define SW 3
#define VISVOGRL 0
#define VISVOGRU 35
#define NVOGRL 36
#define NVOGRU 51
#define VISGPDRL 0
#define VISGPDRU 42
#define NGPDRL 43
#define NGPDRU 65
#define RCONST 0.1818
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
/*variables
 * Ammo Type 
 *  atype uint8_t     
 *  0 - VOG
 *  1 - GPD         
 * double ft- range select
 *  vtype uint8_t
 *  0 -visible yes  if vog 0-35 if gpd 0-42
 *  1- visible no   if vog 36-51 if gpd 43-65
 *  temp_x- temperature in C  press_x=pressure in mm
 *  stype uint8_t select C wind in deviation (d)
 *  0  3-9  in value of deviation+e
 *  1  9-3  in value of deviation-e
 *  2  nill no change in d
 *  ltype uint8_t select L wind in elevation (b)
 *  0  12-6  in value of elevation+lwind
 *  1  6-12  in value of elevation-lwind
 *  2  1-7   in value of elevation+(lwind/2)
 *  3  7-1   in value of elevation-(lwind/2)
 *  int range, rangediff  //compute by searching on corresponding tables
 *  meter to mill constant 0.1818 ,multiply to get mills 
 */
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
uint8_t atype,vtype,stype,ltype;
int range,rangediff;
int deviation;
int xwind,lwind;
int rpress,rtemp;
float rmill,elevation,pelevation;
float net_c;
double Range;
uint8_t tt;
 char skey;
int tempvar;

  //int i=0,prev_i;
 // int x=0;
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
    u8g.drawStr(0, 63, " *)NILL");

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
    u8g.drawStr(0, 63, " *)NILL");

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
          u8g.drawStr(0, 63, " *)NILL");

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
           u8g.drawStr(0, 63, " *)NILL");

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
           u8g.drawStr(0, 63, " *)NILL");
      } while( u8g.nextPage() );
      rtype=3;
     }
     else if(key=='*')
     {
       u8g.firstPage();  
     do {
          u8g.setFont(u8g_font_helvB12);  
          u8g.drawStr(30, 12, "L WIND");
          u8g.drawStr(0, 30, "A)12-6"); 
          u8g.drawStr(0, 48, "B)6-12");                   
          u8g.drawStr(60, 30, "C)1-7");              
          u8g.drawStr(60, 48, "#)7-1");         
           u8g.drawBox(0, 50, 58, 19);//x1,y1,w,height
          u8g.setColorIndex(0);    
          u8g.drawStr(0, 63, " *)NILL");
         u8g.setColorIndex(1);
      } while( u8g.nextPage() );
      rtype=4;
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
    u8g.drawStr(20, 30, s);
   
  } while( u8g.nextPage() );
  delay(dly);
  u8g.firstPage();  
  do {
   } while( u8g.nextPage() );
}
int search_sheet_row(uint16_t v)
{int i=0;
 uint16_t firstChar =0;
 uint16_t lastChar =0;
 uint16_t secChar=0;
 uint8_t lowerlimit,upperlimit;
 if(atype==0 && vtype==0)//vog visible
 {
  lowerlimit=VISVOGRL;
  upperlimit=VISVOGRU;
 }
 else if(atype==0 && vtype==1)//vog not visible
 {
  lowerlimit=NVOGRL;
  upperlimit=NVOGRU;
 }
 else if(atype==1 && vtype==0)//GPD visible
 {
  lowerlimit=VISGPDRL;
  upperlimit=VISGPDRU;
 }
 else if(atype==1 && vtype==1)//GPD not visible
 {
  lowerlimit=NGPDRL;
  upperlimit=NGPDRU;
 }
 for(i=lowerlimit;i<=upperlimit;i++)
 {
  if(atype==0)//vog sheet1
  {firstChar = pgm_read_word_near(sheet1x+ i);
  }
  else
  {
   firstChar = pgm_read_word_near(sheet2x+ i); 
  }
  if(firstChar==v)
  {
   range=v;
   rangediff=0;
   break; 
   
  }
  if(vtype==0)//progressive
  {
    if(firstChar>v)
    { if(i==lowerlimit)
      {
      range=firstChar;
      rangediff=firstChar-v;
      break;
      }
      else
      {
        range= (lastChar+firstChar)/2;
        if(range>=v)
        {
         range=lastChar;
         rangediff=v-lastChar;
         i=i-1;
         break; 
        }
        else
        {
         range=firstChar;
         rangediff=firstChar-v; 
         break;
        }
      }
    }
  }
    else           //decessive not visible case
  {
    if(firstChar<v)
    { if(i==lowerlimit)
      {
      range=firstChar;
      rangediff=firstChar-v;
      break;
      }
      else
      {
        range= (lastChar+firstChar)/2;
        if(range<=v)
        {
         range=firstChar;
         rangediff=firstChar-v; 
         break;
        }
        else
        {         
         range=lastChar;
         rangediff=v-lastChar;
         i=i-1;
         break; 
        }
      }
    }
  }
  lastChar=firstChar;
 }
 if(i>upperlimit)
 return 200;
 else
 return i; 
}
void from_row(uint8_t v) //dev
{ int ff;
 
  if(atype==0)//vog sheet1
  { elevation = pgm_read_word_near(sheet1y+ v);
    deviation = pgm_read_byte(devmils+ v);
    xwind = pgm_read_byte(xwindmils+ v);
    lwind = pgm_read_byte(lwindm+ v);
    rtemp = pgm_read_byte(tempm+ v);
    rpress = pgm_read_byte(pressm+ v);
    rmill  = pgm_read_byte(onemillm+ v);
    rmill =rmill/10.0;
  }
  else //GPD sheet2
  { elevation = pgm_read_word_near(sheet2y+ v);
    deviation = pgm_read_byte(devmils2+ v); 
    xwind = pgm_read_byte(xwindmils2+ v);
    lwind = pgm_read_byte(lwindm2+ v);
    rtemp = pgm_read_byte(tempm2+ v);
    rpress = pgm_read_byte(pressm2+ v);
    rmill  = pgm_read_byte(onemillm2+ v);
    rmill =rmill/10.0;
  } 
  
}
void compute()
{
  if(stype==0)//3-9 xcrosswind
  {
    deviation=deviation+xwind;
  }
  else if(stype==1)
  {
    deviation=deviation-xwind;
  }
  if(ltype==0)
  {
   pelevation=lwind; 
  }
  else if(ltype==1)
  {
   pelevation=-lwind; 
  }
  else if(ltype==2)
  {
   pelevation=(lwind); 
   pelevation=pelevation*0.5; 
  }
  else if(ltype==3)
  {
   pelevation=-(lwind); 
   pelevation=pelevation*0.5; 
  }
  //temp_x press_x input temperature and pressure
  //rtemp and rpress row selected temperature and pressure
  //standard temp 15deg pressure 760
  if(temp_x==15)
  {rtemp=0;}
  else if(temp_x>15) 
  {rtemp=rtemp*1;}
  else if(temp_x<15) 
  {rtemp=rtemp*(-1);}
  
  if(press_x==760)
  {rpress=0;}
  else if(press_x>760) 
  {rpress=rpress*1;}
  else if(press_x<760) 
  {rpress=rpress*(-1);}
  
  net_c=pelevation+rtemp+rpress;
  net_c=net_c*(1.0/rmill);
  elevation=elevation+net_c;
  elevation=elevation+rangediff*(1.0/rmill);
}
void taskone()
{ 
  long na=0L;//own gr easting
  long nb=0L;//own gr northing
  long ta=0L;//target gr easting
  long tb=0L;//target gr northing
   atype=select_msg("Ammo select","A- VOG","B- GPD",0); 
  show_msg(1000,"OK");
  vtype=select_msg("TGT Visible","A- YES","B- NO ",0); 
  show_msg(1000,"OK");

  stype=select_msg("Sel C wind","A- (3-9)","B- (9-3)",1);
  show_msg(1000,"OK");
  ltype=select_msg4();
  show_msg(1000,"OK");
   temp_x=read_input_two("Temp(C)"); //temperature
  show_msg(2000,"OK");
  press_x=read_input_three("Presre(mm)"); //pressure
  show_msg(2000,"OK");
  na=read_input("OWNGR(E)"); //a
  show_msg(2000,"OK");
  nb=read_input("OWNGR(N)"); //b
  show_msg(2000,"OK");
  ta=read_input("TGTGR(E)"); //c
  show_msg(2000,"OK");
  tb=read_input("TGTGR(N)"); //d
  show_msg(2000,"OK");
  Range =sq(tb-nb)+sq(ta-na);
  Range=sqrt(Range);
  Range=round(Range);
  tempvar=(int)Range;
  tt=search_sheet_row(tempvar);
  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_helvB12);  
    u8g.setPrintPos(10, 15);
    u8g.print("Range=");
    u8g.print(tempvar);
    u8g.setPrintPos(10, 30);
    u8g.print("Row=");
    u8g.print(tt);
    
  } while( u8g.nextPage() );
  delay(2000);
  if(tt==200)
  show_msg(2000,"ERROR102");
  from_row(tt);
  compute();
     u8g.firstPage();
  do {
    u8g.setFont(u8g_font_helvB12);  
    u8g.setPrintPos(20, 12);
    u8g.print("(RESULTS)");
    u8g.setPrintPos(0, 30);
    u8g.print("(DEV)= ");u8g.print(deviation);
    u8g.setPrintPos(0, 47);
    u8g.print("(ELE)= ");u8g.print(elevation,2);
    u8g.setPrintPos(0, 60);
    u8g.print("(Range)= ");u8g.print(Range);
  } while( u8g.nextPage() );
  
}
void setup() {
  
  pinMode(CLK,INPUT);
  pinMode(DT,INPUT);
  pinMode(SW, INPUT_PULLUP); 
  u8g.setRot180();
  u8g.firstPage();  
  do {
    u8g.setFont(u8g_font_helvB10);  
    u8g.drawStr(30, 10, "Welcome "); 
    u8g.drawStr(30, 30, "To target");
    u8g.drawStr(10, 50, "Calculator");
   
  } while( u8g.nextPage() );
  delay(2000); 
 
  
}
void loop() {
  taskone();
   do{
  skey = keypad.getKey();// Read the key
  }while(skey!='*'); 
}
