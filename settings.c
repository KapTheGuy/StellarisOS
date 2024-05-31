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

    serial_puts(ANSI_COLOR_YELLOW "SETTINGS\n\r" ANSI_COLOR_RESET);

    /* Show system information */
    serial_puts(ANSI_COLOR_GREEN "\n\rDevice: Protolinker\n\rVersion: 2004B\n\rInterface: UART\n\rInterface Port: 0\n\rChip: ARM Cortex-M3\n\r" ANSI_COLOR_RESET);

    serial_puts(ANSI_COLOR_YELLOW "ENTER " ANSI_COLOR_RESET);
    serial_puts("To go back.");

    serial_gets(opt1);
}

void start_settings()
{
    char opt[64];

    serial_clear();

    serial_puts(ANSI_COLOR_YELLOW "SETTINGS\n\r" ANSI_COLOR_RESET);

    /* Options */
    serial_puts("\n\r1. SYSTEM INFORMATION\n\r");

    serial_puts("\n\rPlease choose your option: ");

    /* Get user input */
    serial_gets(opt);

    if (strcmp(opt, "1") == 0)
    {
        sysinfo();
    }

    /* Close the app */
    serial_clear();
}
