#include <unistd.h>
#include "py/mpconfig.h"
#include "baochip-sdk/baochip_sdk.h"

/*
 * Core UART functions to implement for a port
 */

// Receive single character
int mp_hal_stdin_rx_chr(void) {
    return dbs_uart_read_char();
}

// Send string of given length
mp_uint_t mp_hal_stdout_tx_strn(const char *str, mp_uint_t len) {
    // CAUTION: this is backed by a UDMA UART which depends on dbs_uart_tick()
    // being called periodically to service the DMA queue. Short strings that
    // fit in one DMA block will usually be sent immediately. But, longer
    // strings, or many rapid shorter strings, may get sent in multiple blocks.
    dbs_uart_write((const uint8_t *)str, len);
    return len;
}
