#ifndef __UART_H
#define __UART_H

#include <stddef.h>

/**
 * The PORT register for UART
 */
#ifndef UART_PORT
#define UART_PORT PORTB
#endif
/**
 * The DDR register for UART
 */
#ifndef UART_DDR
#define UART_DDR DDRB
#endif
/**
 * The bit position for the UART tx pin
 */
#ifndef UART_TX_BIT
#define UART_TX_BIT PB1
#endif
/**
 * The UART baudrate (a sane value for 1MHz would be 4800 baud)
 */
#ifndef UART_BAUDRATE
#define UART_BAUDRATE 19200
#endif
/**
 * Uncomment if parity bit shall be sent.
 * 1 = odd parity
 * 0 = even parity
 */
// #define UART_PARITY 0
/**
 * Buffer size for outgoing bytes (number of queue slots)
 */
#ifndef UART_BUFFER_SIZE
#define UART_BUFFER_SIZE 64
#endif

// DON'T CHANGE ANYTHING BELOW /////////////////////////////////////////////////
#if F_CPU/UART_BAUDRATE < 256

#define UART_TIMER1_PRESCALE_BITS _BV(CS10)
#define UART_TIMER1_CK (F_CPU)

#elif (F_CPU/2)/UART_BAUDRATE < 256

#define UART_TIMER1_PRESCALE_BITS _BV(CS11)
#define UART_TIMER1_CK (F_CPU/2)

#elif (F_CPU/4)/UART_BAUDRATE < 256

#define UART_TIMER1_PRESCALE_BITS _BV(CS11) | _BV(CS10)
#define UART_TIMER1_CK (F_CPU/4)

#elif (F_CPU/8)/UART_BAUDRATE < 256

#define UART_TIMER1_PRESCALE_BITS _BV(CS12)
#define UART_TIMER1_CK (F_CPU/8)

#elif (F_CPU/16)/UART_BAUDRATE < 256

#define UART_TIMER1_PRESCALE_BITS _BV(CS12) | _BV(CS10)
#define UART_TIMER1_CK (F_CPU/16)

#elif (F_CPU/32)/UART_BAUDRATE < 256

#define UART_TIMER1_PRESCALE_BITS _BV(CS12) | _BV(CS11)
#define UART_TIMER1_CK (F_CPU/32)

#else
#error BAUDRATE is too low
#endif
////////////////////////////////////////////////////////////////////////////////


typedef enum
{
        UART_OK,
        UART_BUSY
} uart_error_t;

/**
 * Transmit a single character (blocking until queued)
 */
void uart_putc(const char c);

/**
 * Try to transmit a single character, if UART is Busy, return UART_BUSY
 */
uart_error_t uart_try_putc(const char c);

/**
 * Transmit a series of characters (blocking until queued)
 * @param s is safe to overwrite after this function returns
 */
void uart_puts(const char *s, size_t len);

/**
 * Try to transmit a string, if UART is Busy, return UART_BUSY
 * @param s is safe to overwrite after this function returns
 */
uart_error_t uart_try_puts(const char *s, size_t len);

/**
 * Initialize UART
 * using Timer1
 */
void uart_init();

#endif // __UART_H
