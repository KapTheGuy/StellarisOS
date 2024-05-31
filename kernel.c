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
        serial_puts("\n\r1. SETTINGS\n\r");
        serial_puts("\n\r2. DEVICE INFORMATION\n\r");
        serial_puts("\n\r3. CALCULATOR\n\r");

        serial_puts("\n\rPlease choose your option: ");

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
        }
    }

    return 0;
}
