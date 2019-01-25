#include <FreeRTOS.h>
#include <task.h>
#include <hal/gpio.h>
#include <hal/keybd.h>
#include <sys/evt.h>
#include <pulsegen/systate.h>
#include <pulsegen/statemgr.h>
#include <gfx/ui.h>
#include <assert.h>
#include <stdint.h>

#define POWER_HOLD 17

static struct system_state state;

// extern unsigned long uxCriticalNesting;

/* manage system events */
void device_listener(enum system_event type, uint32_t data)
{
	state_update(&state, type, NULL);
}

void event_loop(void *param)
{
	evt_init();
	evt_register_listener(device_listener);
	while (1)
	{
		evt_loop();
		ui_update();
	}
}

/* handle key press events */
void key_handler(enum key_type key)
{
	enum system_event type;
	switch (key)
	{
	/* ontime/freq */
	case KEY_TA1:
		type = EVT_KEY_FREQ;
		break;
	/* level */
	case KEY_TA2:
		type = EVT_KEY_LEVEL;
		break;
	/* offtime duty */
	case KEY_TA3:
		type = EVT_KEY_DUTY;
		break;
	/* change mode */
	case KEY_TA4:
		type = EVT_KEY_MODE;
		break;
	/* count */
	case KEY_TA5:
		type = EVT_KEY_COUNT;
		break;
	/* power/trigger */
	case KEY_POW:
		type = EVT_ENC_PUSH;
		break;
	/* encoder increment */
	case ENC_INC:
		type = EVT_ENC_UP;
		break;
	/* encoder decrement */
	case ENC_DEC:
		type = EVT_ENC_DOWN;
		break;
	}
	evt_queue_from_isr(type, 0);
}

static void timming_tasks(void *arg)
{
	while (true)
	{
		ui_timming_tasks();
		vTaskDelay(10 / portTICK_PERIOD_MS);
	}
}

int main(void)
{
	// uxCriticalNesting = 0xaaaaaaaa;
	hal_gpio_init_out(5, 0);
	hal_gpio_init_out(6, 1);
	hal_gpio_init_out(POWER_HOLD, 1);
	keybd_init(key_handler);
	state_init(&state);
	ui_init(&state);
	xTaskCreate(event_loop, "evtloop", 1020, NULL, 3, NULL);
	xTaskCreate(timming_tasks, "tim", 100, NULL, 3, NULL);
	vTaskStartScheduler();
	return 1;
}

void vApplicationStackOverflowHook(xTaskHandle *pxTask, signed char *pcTaskName)
{
	asm("BKPT");
	while (1)
		;
}

void vApplicationIdleHook(void)
{
}

void vApplicationMallocFailedHook(void)
{
	asm("BKPT");
	while (1)
		;
}
