#include "U8glib.h"
#include "sheet1.h"
U8GLIB_SH1106_128X64 u8g(13, 11, 10, 9, 8);  // D0=13, D1=11, CS=10, DC=9, Reset=8
float hum =12.34; 
  float temp = 37.99; 
  int i=0;
void setup() {
 
  u8g.firstPage();  
  do {
    u8g.setFont(u8g_font_helvB10);  
    u8g.drawStr(30, 10, "Welcome "); 
    u8g.drawStr(30, 30, "To Aimsinte");
    u8g.drawStr(10, 50, "AMIT AHKE");
   
  } while( u8g.nextPage() );
  delay(2000);  
}
void loop() {
  
  u8g.firstPage();  
  do {
    u8g.setFont(u8g_font_helvB14);  
    u8g.setPrintPos(0, 15);  
    u8g.print("(1)");
    uint8_t f = pgm_read_byte(onemillm+ i);
    u8g.print(float(f/10.0), 1);
    u8g.setPrintPos(65, 15);
    uint16_t firstChar = pgm_read_word_near(sheet1x+ i);
    u8g.print(firstChar, 1);
    u8g.print((char)176);
    u8g.print("C");
    
    u8g.drawStr(0, 35, "Humi:");
    u8g.setPrintPos(65, 35);
    uint16_t secChar = pgm_read_word_near(sheet1y+ i);
    u8g.print(secChar, 1);
    u8g.print("%");
  } while( u8g.nextPage() );i++;i=(i>51)?0:i;delay(1000);
}
