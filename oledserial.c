/* see LICENSE file for copyright and license details. */

#include <string.h>
#include "lib/circular_usart.h"
#include "lib/lcd.h"

void 
main (void)
{
	/* init usart, turn on display */
	USART_init(115200);
	lcd_init(LCD_DISP_ON);

	char buf[256]; /* 256 bytes ought to be enough for anyone */
	uint8_t inverted = !INVERTED;

	/* take and parse input from serial */
	for (;;) {
		USART_getstr(buf);
		switch (buf[0]) {
			case 'W': /* Wn str, write str to row n */
				lcd_gotoxy(0, buf[1]-'0');
				lcd_puts(buf+3);
				break;
			case 'P':; /* Px,y str, write str to position x,y */
				uint8_t x = 0, y = 0;
				sscanf(buf, "P%d,%d", &x, &y);
				lcd_gotoxy(x, y);
				lcd_puts(strchr(buf, ' ')+1);
				break;
			case 'I': /* I, invert screen */
				lcd_invert((inverted=!inverted));
				break;
			case 'C': /* C, clear screen */
				lcd_clrscr();
				break;
		}
	}
}
