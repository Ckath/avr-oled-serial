//****main.c****//
#include "lcd.h"


int main(void){
  lcd_init(LCD_DISP_ON);    // init lcd and turn on
  
  lcd_puts("twitch.tv/ck8t");  // put string from RAM to display (TEXTMODE) or buffer (GRAPHICMODE)
  lcd_gotoxy(0,1);          // set cursor to first column at line 3
  lcd_puts("suh dude");  // puts string form flash to display (TEXTMODE) or buffer (GRAPHICMODE)

  lcd_gotoxy(0,3);          // set cursor to first column at line 3
  uint8_t i = 0;
  char buf[100];
  for(;;) {
      lcd_gotoxy(0,3);
	  sprintf(buf, "test #%d", i++);
	  lcd_puts(buf);
	  int ii;
	  for(ii = 0; ii < 1000; ++ii);
  }
  return 0;
}
