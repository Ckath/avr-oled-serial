/* very basic(unsafe) implemenation of reading usart with a circular buffer
 * see CIRCULAR_LICENSE file for copyright and license details. */

#ifndef CIRC_USART
#define CIRC_USART
#define BUFSIZE 200

void USART_init(unsigned long int baud);
char USART_getch(void);
void USART_getstr(char *string);

#endif
