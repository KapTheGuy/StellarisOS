/*
    @brief: Shell for StellarisOS
    @author: Kap Petrov
    @desc: Shell C Header File for StellarisOS -- A Minimal ARM Operating System,
          Emulated version, runs on a TI Stellaris LMS6965 On QEMU.
*/
#ifndef SHELL_H
#define SHELL_H

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
int strcmp(const char *s1, const char *s2);

/* String to number */
int stringToNumber(char *str);

#define MAX_DIGITS 20 // Maximum number of digits supported

// Function to convert a number to a string
char* number_to_string(int num);

/* Output a character */
void serial_putchar(const char c);

/* Read a character */
uart_err serial_getchar(char* pc);

/* Output a string */
void serial_puts(const char* str);

/* Read a string into a buffer */
void serial_gets(char* str);

/* CLear the terminal screen */
void serial_clear();

/* Sleep function */
void delay(unsigned long count);

#endif
