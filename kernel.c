/*
    @brief: Kernel for StellarisOS
    @author: Kap Petrov
    @desc: Kernel C File for StellarisOS -- A Minimal ARM Operating System,
          Emulated version, runs on a TI Stellaris LMS6965 On QEMU.
*/

#include "shell.h"
#include "calc.h"
#include "settings.h"
#include "dinfo.h"

/* Kernel entry point */
int main(void)
{
    /* Buffer, 64 characters long, to store the user input */
    char first_ip[64];

    /* Initialize UART. */
    uart_init(115200);

    /* Interface */
    while(1)
    {
        serial_clear();

        /* Options */
        if (mode == 0)
        {
            serial_puts("\n\r1. SETTINGS\n\r");
            serial_puts("\n\r2. DEVICE INFORMATION\n\r");
            serial_puts("\n\r3. CALCULATOR\n\r");

            serial_puts("\n\rPlease choose your option: ");
        }
        else if (mode == 1)
        {
            serial_puts(ANSI_COLOR_CYAN "\n\r1. SETTINGS\n\r");
            serial_puts(ANSI_COLOR_CYAN "\n\r2. DEVICE INFORMATION\n\r");
            serial_puts(ANSI_COLOR_CYAN "\n\r3. CALCULATOR\n\r");

            serial_puts(ANSI_COLOR_CYAN "\n\rPlease choose your option: " ANSI_COLOR_RESET);
        }

        /* Get user input */
        serial_gets(first_ip);

        if (strcmp(first_ip, "1") == 0)
        {
            start_settings();
        }
        else if (strcmp(first_ip, "2") == 0)
        {
            start_dinfo();
        }
        else if (strcmp(first_ip, "3") == 0)
        {
            start_calc();
        }
        else if (strcmp(first_ip, "12213225765479766968978976788779864347998765434") == 0)
        {
            serial_puts(ANSI_COLOR_RED "\n\rwhy would you type that?\n\r" ANSI_COLOR_RESET);
            delay(100000000);
        }
    }

    return 0;
}
