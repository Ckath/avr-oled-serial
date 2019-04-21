/* very basic(unsafe) implemenation of reading usart with a circular buffer
 * see CIRCULAR_LICENSE file for copyright and license details. */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "circular_usart.h"

char buf[BUFSIZE];
uint16_t rx_ptr = 0;
uint16_t tx_ptr = 0;

ISR(USART_RX_vect)
{
	/* write along buffer */
	buf[++tx_ptr%BUFSIZE] = UDR0;
}

void USART_init(unsigned long int baud)
{
	/* enable double speed */
	UCSR0A |= (1 << U2X0);

	/* set baud rate */
	int16_t ubbr = (F_CPU / (8ul * baud)) - 1;
	UBRR0H = (uint8_t) (ubbr / 256);
	UBRR0L = (uint8_t) (ubbr);

	/* enable receiver, and interrupts */
	UCSR0B = (1 << RXEN0) | (1 << RXCIE0);
	sei();
}

char USART_getch(void)
{
	/* read from buffer up until write pointer */
	while(rx_ptr == tx_ptr);
	return buf[++rx_ptr%BUFSIZE];
}

void USART_getstr(char *str)
{
	/* get \r terminated string from buffer */
	uint8_t i = 0;
	do 
	{
		str[i++] = USART_getch();

	} while (str[i-1] != '\r');

	/* return \0 terminated string */
	str[i-1] = '\0';
}
