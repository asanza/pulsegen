#ifndef D60856E5_37B9_4C47_A84A_76EC587AEB7E
#define D60856E5_37B9_4C47_A84A_76EC587AEB7E

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

enum hal_uart_parity {
    /** No Parity */
    HAL_UART_PARITY_NONE = 0,
    /** Even parity */
    HAL_UART_PARITY_EVEN = 2,
    /** Odd parity */
    HAL_UART_PARITY_ODD = 3,
};

typedef void(*rx_callback_t)(uint8_t* buffer, int len);
typedef void(*tx_callback_t)( void );

/**
 * @brief Initialize the serial port instance
 * 
 * @param instance which serial port to open 
 * @param baudrate 
 * @param databits 
 * @param stopbits 
 * @param parity 
 * @param priv  Private data used on the hardware driver
 */

void 
hal_uart_init(int instance, uint32_t baudrate, uint8_t databits, 
  uint8_t stopbits, enum hal_uart_parity parity, void* priv);

void
hal_uart_config(int instance, uint32_t baudrate, uint8_t databits, 
  uint8_t stopbits, enum hal_uart_parity parity);

void
hal_uart_read_async(int instance, uint8_t* rxbuffer, int size,
  rx_callback_t cb);

void
hal_uart_write_async(int instance, uint8_t* txbuffer, int size,
  tx_callback_t cb);

void
hal_uart_write_sync(int instance, uint8_t* txbuffer, int size);

void
hal_uart_write_blocking( int instance, uint8_t c);

void
hal_uart_disable_rx(int instance);

void
hal_uart_disable_tx(int instance);

void
hal_uart_enable_rx( int instance );

void
hal_uart_enable_tx(int instance);

bool
hal_uart_rx_enabled(int instance);

bool
hal_uart_tx_enabled(int instance);

#ifdef __cplusplus
}
#endif

#endif /* D60856E5_37B9_4C47_A84A_76EC587AEB7E */
