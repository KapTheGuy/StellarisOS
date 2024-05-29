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
    const char *start_msg = "Welcome to StellarisOS Beta 2001\n\r";
    char first_ip[64];

    uart_init(115200);

    serial_puts(start_msg);

    // Shell
    while(1)
    {
        serial_puts("> ");
    
        serial_gets(first_ip);

        if (strcmp(first_ip, "help") == 0)
        {
            serial_puts(ANSI_COLOR_CYAN "\n\rCommands:\n\rsysinfo - Get system information\n\rping - Ping\n\rclear - Clear the screen\n\r" ANSI_COLOR_RESET);
        }
        else if (strcmp(first_ip, "sysinfo") == 0)
        {
            serial_puts(ANSI_COLOR_GREEN "\n\rDevice: Blipper 1\n\rVersion: 2001B\n\rInterface: UART\n\rChip: ARM Cortex-M3\n\r" ANSI_COLOR_RESET);
        }
        else if (strcmp(first_ip, "ping") == 0)
        {
            serial_puts(ANSI_COLOR_MAGENTA "\n\rpong\n\r" ANSI_COLOR_RESET);
        }
        else if (strcmp(first_ip, "12213225765479766968978976788779864347998765434") == 0)
        {
            serial_puts(ANSI_COLOR_RED "\n\rwhy would you type that?\n\r" ANSI_COLOR_RESET);
            
        }
        else if (strcmp(first_ip, "clear") == 0)
        {
            for(int i = 0; i < 800; i++)
            {
            	serial_puts("\n\r \n\r");
            } 
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
