/*
    @brief: Settings app for StellarisOS
    @author: Kap Petrov
    @desc: Settings app C File for StellarisOS -- A Minimal ARM Operating System,
          Emulated version, runs on a TI Stellaris LMS6965 On QEMU.
*/
#include "settings.h"

void start_settings()
{
    serial_clear();

    serial_puts(ANSI_COLOR_YELLOW "SETTINGS\n\r" ANSI_COLOR_RESET);

    /* Show system information */
    serial_puts(ANSI_COLOR_GREEN "\n\rDevice: Protolinker\n\rVersion: 2003B\n\rInterface: UART\n\rInterface Port: 0\n\rChip: ARM Cortex-M3\n\r" ANSI_COLOR_RESET);
    /* Close the app */
    delay(6);
    serial_clear();
}
