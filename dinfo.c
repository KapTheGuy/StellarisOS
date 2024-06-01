/*
    @brief: Device info app for StellarisOS
    @author: Kap Petrov
    @desc: Device info app C File for StellarisOS -- A Minimal ARM Operating System,
          Emulated version, runs on a TI Stellaris LMS6965 On QEMU.
*/
#include "dinfo.h"

void start_dinfo()
{
    serial_clear();

    serial_puts(ANSI_COLOR_CYAN "DEVICE INFORMATION\n\r" ANSI_COLOR_RESET);

    /* Show system information */
    serial_puts(ANSI_COLOR_CYAN "\n\rINT:[31/05/24]C5:2004B\n\rDYSON:[27/05/24]:UART\n\r" ANSI_COLOR_RESET);
    /* Close the app */
    delay(6);
    serial_clear();
}
