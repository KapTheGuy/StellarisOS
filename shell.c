/*
    @brief: Shell for StellarisOS
    @author: Kap Petrov
    @desc: Shell C File for StellarisOS -- A Minimal ARM Operating System,
          Emulated version, runs on a TI Stellaris LMS6965 On QEMU.
*/

#include "shell.h"

/* String compare */
int strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char *)s1 - *(const unsigned char *)s2;
}


/* Output a character */
void serial_putchar(const char c)
{
    uart_tx_byte(c);
}

/* Read a character */
uart_err serial_getchar(char* pc)
{
    uart_err retval;
    retval = uart_rx_byte(pc);
    return retval;
}


/* Output a string */
void serial_puts(const char* str)
{
    while(*str)
    {
        serial_putchar(*str);
        str++;
    }
}

/* Read a string into a buffer */
void serial_gets(char* str)
{
    char c;
    char *pstr = str;

    while(1)
    {
        if(serial_getchar(&c) == UART_OK)
        {
            if(c == '\r')
            {
                *pstr = '\0';
                break;
            }
            else
            {
                *pstr = c;
            }

            pstr++;
        }
    }
}

/* CLear the terminal screen */
void serial_clear()
{
    serial_puts("\033[2J");
    serial_puts("\033[0;0H");
}

/* Sleep function */
void delay(unsigned long seconds)
{
    unsigned long count = seconds * 200;

    while(count--)
    {
        // Insert some delay
        for(int i = 0; i < 100000; i++);
    }
}
