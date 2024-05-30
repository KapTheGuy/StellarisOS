/*
    @brief: Kernel for StellarisOS
    @author: Kap Petrov
    @desc: Kernel C File for StellarisOS -- A Minimal ARM Operating System,
          Emulated version, runs on a TI Stellaris LMS6965 On QEMU.
*/

#include "uart_drv.h"

/* ANSI escape codes for text colors */
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

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

/* Kernel entry point */
int main(void)
{
    /* Welcome the user */
    const char *start_msg = "Welcome to StellarisOS Beta 2002\n\r";

    /* Buffer, 64 characters long, to store the user input */
    char first_ip[64];

    /* Initialize UART. */
    uart_init(115200);

    /* Print the welcome message. */
    serial_puts(start_msg);

    /* Shell */
    while(1)
    {
        /* Classic, if thisnotpresent: user == mad */
        serial_puts("> ");

        /* Get user input */
        serial_gets(first_ip);

        /* Show command entered so user doesn't go mald. */
        serial_puts("\n\rCommand issued: ");
        serial_puts(ANSI_COLOR_BLUE);
        serial_puts(first_ip);
        serial_puts(ANSI_COLOR_RESET);

        /* aint no way im gon comment all dis */
        if (strcmp(first_ip, "help") == 0)
        {
            serial_puts(ANSI_COLOR_CYAN "\n\rCommands:\n\rsysinfo - Get system information\n\rping - Ping\n\r" ANSI_COLOR_RESET);
        }
        else if (strcmp(first_ip, "sysinfo") == 0)
        {
            serial_puts(ANSI_COLOR_GREEN "\n\rDevice: Protolinker\n\rVersion: 2002B\n\rInterface: UART\n\rInterface Port: 0\n\rChip: ARM Cortex-M3\n\r" ANSI_COLOR_RESET);
        }
        else if (strcmp(first_ip, "ping") == 0)
        {
            serial_puts(ANSI_COLOR_MAGENTA "\n\rpong\n\r" ANSI_COLOR_RESET);
        }
        else if (strcmp(first_ip, "12213225765479766968978976788779864347998765434") == 0)
        {
            serial_puts(ANSI_COLOR_RED "\n\rwhy would you type that?\n\r" ANSI_COLOR_RESET);
        }
        else
        {
            serial_puts("\n\r");
            serial_puts(first_ip);
            serial_puts(" is not a known command. Please use " ANSI_COLOR_YELLOW "help" ANSI_COLOR_RESET " for known commands for the system.");
            serial_putchar('\n');
            serial_putchar('\r');
        }
    }

    return 0;
}
