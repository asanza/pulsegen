
#include <stdlib.h>
#include <os/os.h>
#include <os/threads.h>
#include "bsp/board.h"

static void test_thread( void* args )
{
	hal_gpio_init_out(GREEN_LED, 1);
	while(true)
	{
		hal_gpio_toggle(GREEN_LED);
		os_thread_sleep(100);
	}
}

void main( void )
{
	os_thread_new("test", test_thread, NULL, 100, 3);
	os_start();
}
