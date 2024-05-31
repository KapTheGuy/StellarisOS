/*
    @brief: Calculator for StellarisOS
    @author: Kap Petrov
    @desc: Calculator C File for StellarisOS -- A Minimal ARM Operating System,
          Emulated version, runs on a TI Stellaris LMS6965 On QEMU.
*/
#include "calc.h"

int add(int a, int b)
{
    return a + b;
}

int sub(int a, int b)
{
    return a - b;
}

int mul(int a, int b)
{
    return a * b;
}

int div(int a, int b)
{
    return a / b;
}

void start_calc()
{
    serial_clear();

    serial_puts(ANSI_COLOR_YELLOW "CALCULATOR\n\r" ANSI_COLOR_RESET);

    char operator[64];

    serial_puts("Please choose operator (+, -, *, /) > ");

    serial_gets(operator);

    if (strcmp(operator, "+") == 0)
    {
        char a[64];
        char b[64];

        serial_puts("\n\rNumber A > ");
        serial_gets(a);

        serial_puts("\n\rNumber B > ");
        serial_gets(b);

        serial_puts("\n\r");
        serial_puts(number_to_string(add(stringToNumber(a), stringToNumber(b))));
        serial_puts("\n\r");
    }
    else if (strcmp(operator, "-") == 0)
    {
        char a[64];
        char b[64];

        serial_puts("\n\rNumber A > ");
        serial_gets(a);

        serial_puts("\n\rNumber B > ");
        serial_gets(b);

        serial_puts("\n\r");
        serial_puts(number_to_string(sub(stringToNumber(a), stringToNumber(b))));
        serial_puts("\n\r");
    }
    else if (strcmp(operator, "*") == 0)
    {
        char a[64];
        char b[64];

        serial_puts("\n\rNumber A > ");
        serial_gets(a);

        serial_puts("\n\rNumber B > ");
        serial_gets(b);

        serial_puts("\n\r");
        serial_puts(number_to_string(mul(stringToNumber(a), stringToNumber(b))));
        serial_puts("\n\r");
    }
    else if (strcmp(operator, "/") == 0)
    {
        char a[64];
        char b[64];

        serial_puts("\n\rNumber A > ");
        serial_gets(a);

        serial_puts("\n\rNumber B > ");
        serial_gets(b);

        serial_puts("\n\r");
        serial_puts(number_to_string(div(stringToNumber(a), stringToNumber(b))));
        serial_puts("\n\r");
    }
    delay(2);
    serial_clear();
}
