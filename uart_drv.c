#include "uart_drv.h"

// We are using UART0, from the many ports.
static volatile uart_regs *uart0 = (uart_regs*)0x4000C000u;

// Baud rate
#define UART_DFLT_SYSCLK 12500000u

static void set_clk_uart0(void)
{
    uint32_t *pRCGC1 = (uint32_t*)0x400FE104u;

    *pRCGC1 |= 0x00000001u;
}

// Enabling the UART
static void uart_enable(void)
{
	// Set UARTEN in UARTCTL
	uart0->CTL |= UARTCTL_UARTEN;
}

// Disabling the UART
static void uart_disable(void)
{
    /* clear UARTEN in UARTCTL*/
    uart0->CTL &= ~UARTCTL_UARTEN;

    /* Allow any ongoing transfers to finish */
    while(uart0->FR & UARTFR_BUSY);
    
    /* Flush the FIFOs by (disabling) clearing FEN */
    uart0->LCRH &= ~UARTLCRH_FEN;
}
/* Set the uart baudrate of the uart device*/
static void uart_set_baudrate(uint32_t baudrate)
{
    uint32_t brdi, brdf, dvsr, remd;

    /* Refer http://www.ti.com/lit/ds/symlink/lm3s6965.pdf 12.3.2 */
    
    dvsr = (baudrate * 16u);

    /* integer part of the baud rate */
    brdi = UART_DFLT_SYSCLK/dvsr;

    /* fractional part of the baudrate */
    remd = UART_DFLT_SYSCLK - dvsr * brdi;
    brdf = ((remd << 6u) + (dvsr >> 1))/dvsr;

    uart0->IBRD = (uint16_t)(brdi & 0xffffu);
    uart0->FBRD = (uint8_t)(brdf & 0x3ffu);
}

/* Set the line uart controls as in the example
 * example settings: 8-bit word length, no parity, one stop bit, FIFOs disabled
 */
static void uart_set_example_line_ctrls(void)
{
    uart0->LCRH = UARTLCRH_EXAMPLE;
}

/* Initialize the uart device 
 * This is assumed to be called once following reset.
 * NOTE: Since uart0 is being used, we don't have to turn on
 * the corresponding AFSEL bits in GPIOAFSEL for PortA. 
 * These pins are set to uart0 rx/tx by default.
 * Refer http://www.ti.com/lit/ds/symlink/lm3s6965.pdf 12.2
 */
void uart_init(uint32_t baudrate)
{

    uart_disable();
    set_clk_uart0();
    uart_set_baudrate(baudrate);
    uart_set_example_line_ctrls();
    uart_enable();
}

/* Output a byte of data */
void uart_tx_byte(uint8_t byte)
{
    /* if tx register is full, wait until it isn't */
    while(uart0->FR & UARTFR_TXFF);
    
    uart0->DR = (uint32_t)byte;
}

/* Poll for an input byte of data */
uart_err uart_rx_byte(uint8_t* byte)
{
    /* if the rx register is empty, reply 
     * indicating that there is no data
     */
    if(uart0->FR & UARTFR_RXFE)
    {
        return UART_NO_DATA;
    }

    /* Received data is 12-bits in length, with the first 4-bits
     * representing the error flags and the last 8-bits, the data. 
     */
    *byte = uart0->DR & UARTDR_DATA_MASK;
    
    if(uart0->RSRECR & UARTRSRECR_ERR_MASK)
    {
        /* the received data had an error
         * write to ECR to clear the error flags
         */
        uart0->RSRECR &= UARTRSRECR_ERR_MASK;
        return UART_RX_ERR;
    }
    
    return UART_OK;
}
