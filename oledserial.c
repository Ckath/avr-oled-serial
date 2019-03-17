/* see LICENSE file for copyright and license details. */

#include "lib/usart.h"
#include "lib/lcd.h"

void 
main (void)
{
	/* init usart, turn on display */
	USART_init(115200);
	lcd_init(LCD_DISP_ON);

	char buf[256]; /* 256 bytes ought to be enough for anyone */

	/* take and parse input from serial */
	for (;;) {
		USART_getstr(buf);
		switch (buf[0]) {
			case 'W': /* Wn str, write str to row n */
			  lcd_gotoxy(0, buf[1]-'0');
			  lcd_puts(buf+3);
			  break;
			case 'C': /* C, clear screen */
			  lcd_clrscr();
			  break;
		}
	}
}
