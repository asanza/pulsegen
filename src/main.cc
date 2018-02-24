#include <FreeRTOS.h>
#include <task.h>
#include <hal/gpio.h>
#include <hal/keybd.h>
#include <sys/evt.h>
#include <pulsegen/pgen.h>
#include <gfx/gfx.h>
#include <assert.h>
#include <stdint.h>
#include "controller.h"

#define POWER_HOLD 17

static Controller dev;

/* manage system events */
void device_listener( enum EventType type, uint32_t data ) {
	switch(type) {
	case KEY_POWER:         dev.power();       break;
	case KEY_MODE:          dev.mode();        break;
	case KEY_FREQ:          dev.ton();         break;
	case KEY_DUTY:          dev.toff();        break;
	case KEY_LEVEL:         dev.level();       break;
	case KEY_COUNT:         dev.count();       break;
	case ENCODER_DECREASE:  dev.decrease();    break;
	case ENCODER_INCREASE:  dev.increase();    break;
	case OUTPUT_OFF:		dev.notify_stop(); break;
	default: asm ("NOP");
	}
}

void event_loop(void* param) {
	dev.mode();
	while (1) {
		evt_loop();
		dev.periodicTasks();
	}
}

/* handle key press events */
void key_handler( enum key_type key) {
	EventType type;
	switch(key) {
	/* ontime/freq */
	case KEY_TA1: type = KEY_FREQ; break;
	/* level */
	case KEY_TA2: type = KEY_LEVEL; break;
	/* offtime duty */
	case KEY_TA3: type = KEY_DUTY; break;
	/* change mode */
	case KEY_TA4: type = KEY_MODE; break;
	/* count */
	case KEY_TA5: type = KEY_COUNT; break;
	/* power/trigger */
	case KEY_POW: type = KEY_POWER; break;
	/* encoder increment */
	case ENC_INC: type = ENCODER_INCREASE; break;
	/* encoder decrement */
	case ENC_DEC: type = ENCODER_DECREASE; break;
	}
	evt_queue_from_isr(type, 0);
}

int main(void) {
	hal_gpio_init_out(5, 0);
	hal_gpio_init_out(6, 1);
	hal_gpio_init_out(POWER_HOLD, 1);
	keybd_init(key_handler);
	evt_init();
	evt_register_listener(device_listener);
	xTaskCreate(event_loop, "evtloop", 1020, NULL, 3, NULL);
	vTaskStartScheduler();
	return 1;
}

/* os hook functions */
extern "C" {

	void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed char *pcTaskName ) {
		asm ("BKPT");
		while(1) ;
	}

	void vApplicationIdleHook( void ) {

	}

	void vApplicationMallocFailedHook( void ) {
		asm ("BKPT");
		while(1) ;
	}

}
