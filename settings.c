/*
    @brief: Settings app for StellarisOS
    @author: Kap Petrov
    @desc: Settings app C File for StellarisOS -- A Minimal ARM Operating System,
          Emulated version, runs on a TI Stellaris LMS6965 On QEMU.
*/
#include "settings.h"

void sysinfo()
{
    char opt1[64];

    serial_clear();

    if (mode == 1)
    {
        serial_puts(ANSI_COLOR_CYAN "SETTINGS\n\r" ANSI_COLOR_RESET);

        /* Show system information */
        serial_puts(ANSI_COLOR_CYAN "\n\rDevice: Protolinker\n\rVersion: 2004B\n\rInterface: UART\n\rInterface Port: 0\n\rChip: ARM Cortex-M3\n\r" ANSI_COLOR_RESET);

        serial_puts(ANSI_COLOR_CYAN "ENTER " ANSI_COLOR_RESET);
        serial_puts(ANSI_COLOR_CYAN "To go back." ANSI_COLOR_RESET);
    }
    else
    {
        serial_puts(ANSI_COLOR_YELLOW "SETTINGS\n\r" ANSI_COLOR_RESET);

        /* Show system information */
        serial_puts(ANSI_COLOR_YELLOW "\n\rDevice: Protolinker\n\rVersion: 2004B\n\rInterface: UART\n\rInterface Port: 0\n\rChip: ARM Cortex-M3\n\r" ANSI_COLOR_RESET);

        serial_puts(ANSI_COLOR_YELLOW "ENTER " ANSI_COLOR_RESET);
        serial_puts("To go back.");
    }

    serial_gets(opt1);
}

void colorscheme()
{
    char opt2[64];

    serial_clear();

    if (mode == 1)
    {
        serial_puts(ANSI_COLOR_CYAN "SETTINGS\n\r" ANSI_COLOR_RESET);

        /* Show system information */
        serial_puts(ANSI_COLOR_CYAN "\n\rColorschemes: \n\r1. Normal\n\r2. Blue\n\r" ANSI_COLOR_RESET);

        serial_puts(ANSI_COLOR_YELLOW "Press any other key & enter " ANSI_COLOR_RESET);
        serial_puts(ANSI_COLOR_CYAN "To go back." ANSI_COLOR_RESET);

        serial_puts("\n\r> \n\r");
    }
    else
    {
        serial_puts(ANSI_COLOR_YELLOW "SETTINGS\n\r" ANSI_COLOR_RESET);

        /* Show system information */
        serial_puts(ANSI_COLOR_YELLOW "\n\rColorschemes: \n\r1. Normal\n\r2. Blue\n\r" ANSI_COLOR_RESET);

        serial_puts(ANSI_COLOR_YELLOW "Press any other key & enter " ANSI_COLOR_RESET);
        serial_puts("To go back.");
        serial_puts("\n\r> ");
    }

    serial_gets(opt2);

    if (strcmp(opt2, "1") == 0)
    {
        mode = 0;
    }
    else if (strcmp(opt2, "2") == 0)
    {
        mode = 1;
    }
}

void start_settings()
{
    char opt[64];

    serial_clear();

    if (mode == 1)
    {
        serial_puts(ANSI_COLOR_CYAN "SETTINGS\n\r" ANSI_COLOR_RESET);

        /* Options */
        serial_puts(ANSI_COLOR_CYAN "\n\r1. SYSTEM INFORMATION\n\r");
        serial_puts(ANSI_COLOR_CYAN "\n\r2. COLOR SCHEMES\n\r");

        serial_puts("\n\rPlease choose your option: " ANSI_COLOR_RESET);
    }
    else
    {
        serial_puts(ANSI_COLOR_YELLOW "SETTINGS\n\r" ANSI_COLOR_RESET);

        /* Options */
        serial_puts("\n\r1. SYSTEM INFORMATION\n\r");
        serial_puts("\n\r2. COLOR SCHEMES\n\r");

        serial_puts("\n\rPlease choose your option: ");
    }

    /* Get user input */
    serial_gets(opt);

    if (strcmp(opt, "1") == 0)
    {
        sysinfo();
    }
    else if (strcmp(opt, "2") == 0)
    {
        colorscheme();
    }

    /* Close the app */
    serial_clear();
}
