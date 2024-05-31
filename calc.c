/*
    @brief: Calculator for StellarisOS
    @author: Kap Petrov
    @desc: Calculator C File for StellarisOS -- A Minimal ARM Operating System,
          Emulated version, runs on a TI Stellaris LMS6965 On QEMU.
*/
#include "calc.h"

// int add(int a, int b)
// {
//     return a + b;
// }

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

        // add(a, b);
    }

    serial_puts(ANSI_COLOR_GREEN "\n\rTODO!" ANSI_COLOR_RESET);
    delay(2);
    serial_clear();
}
