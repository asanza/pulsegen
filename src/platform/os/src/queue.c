#include <os/queue.h>
#include <FreeRTOS.h>
#include <queue.h>
#include <hal/sys.h>

#define portVECTACTIVE_MASK 0xFFUL

os_queue_t os_queue_new( uint32_t length, uint32_t item_size ) {
	return (os_queue_t) xQueueCreate(length, item_size);
}


bool os_queue_post(os_queue_t queue, void* message, uint32_t timeout){
	TickType_t to = (timeout == OS_FOREVER) ? portMAX_DELAY
					: timeout / portTICK_PERIOD_MS;
	portBASE_TYPE temp;
	bool ret;
	if(hal_sys_is_irq() == false)
	{
		ret = xQueueSend(queue, message, to);
	}
	else
	{
		ret = xQueueSendFromISR(queue, message, &temp);
		portEND_SWITCHING_ISR(temp);
	}
	return ret;
}

bool os_queue_fetch(os_queue_t queue, void* message, uint32_t timeout){
	TickType_t to = (timeout == OS_FOREVER) ? portMAX_DELAY
					: timeout / portTICK_PERIOD_MS;
	portBASE_TYPE temp;
	bool ret;
	if( hal_sys_is_irq() == false )
	{
		ret = xQueueReceive(queue, message, to);
	}
	else
	{
		ret = xQueueReceiveFromISR(queue, message, &temp);
		portEND_SWITCHING_ISR(temp);
	}
	return ret;
}
