/*
    @brief: Shell for StellarisOS
    @author: Kap Petrov
    @desc: Shell C File for StellarisOS -- A Minimal ARM Operating System,
          Emulated version, runs on a TI Stellaris LMS6965 On QEMU.
*/

#include "shell.h"

int mode = 0;

/* String compare */
int strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char *)s1 - *(const unsigned char *)s2;
}

/* String to number */
int stringToNumber(char *str) {
    int result = 0;
    int sign = 1;
    int i = 0;

    // Handle negative numbers
    if (str[0] == '-') {
        sign = -1;
        i++;
    }

    // Iterate through each character of the string
    while (str[i] != '\0') {
        // Check if the character is a digit
        if (str[i] >= '0' && str[i] <= '9') {
            // Convert character to digit and update result
            result = result * 10 + (str[i] - '0');
        } else {
            // If the character is not a digit, break the loop
            break;
        }
        i++;
    }

    // Apply sign
    result *= sign;

    return result;
}

#define MAX_DIGITS 20 // Maximum number of digits supported

// Function to convert a number to a string
char* number_to_string(int num) {
    static char str[MAX_DIGITS + 1]; // Static buffer to store the string
    int i = 0;
    int is_negative = 0;

    // Handle negative numbers
    if (num < 0) {
        is_negative = 1;
        num = -num;
    }

    // Convert each digit to a character in reverse order
    do {
        str[i++] = num % 10 + '0';
        num /= 10;
    } while (num > 0);

    // Add negative sign if necessary
    if (is_negative)
        str[i++] = '-';

    str[i] = '\0'; // Null-terminate the string

    // Reverse the string
    int j = 0;
    int len = i;
    for (j = 0; j < len / 2; j++) {
        char temp = str[j];
        str[j] = str[len - j - 1];
        str[len - j - 1] = temp;
    }

    return str;
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
