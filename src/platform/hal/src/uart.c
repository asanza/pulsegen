#include <hal/uart.h>

void 
hal_uart_init(int instance, uint32_t baudrate, uint8_t databits, 
  uint8_t stopbits, enum hal_uart_parity parity, void* priv)
{

}

void
hal_uart_config(int instance, uint32_t baudrate, uint8_t databits, 
  uint8_t stopbits, enum hal_uart_parity parity)
{

}

void
hal_uart_read_async(int instance, uint8_t* rxbuffer, int size,
  rx_callback_t cb)
{

}

void
hal_uart_write_async(int instance, uint8_t* txbuffer, int size,
  tx_callback_t cb)
{

}

void
hal_uart_write_sync(int instance, uint8_t* txbuffer, int size)
{

}

void
hal_uart_write_blocking( int instance, uint8_t c)
{

}

void
hal_uart_disable_rx(int instance)
{

}

void
hal_uart_disable_tx(int instance)
{

}

void
hal_uart_enable_rx( int instance )
{

}

void
hal_uart_enable_tx(int instance)
{

}

bool
hal_uart_rx_enabled(int instance)
{

}

bool
hal_uart_tx_enabled(int instance)
{
    
}
