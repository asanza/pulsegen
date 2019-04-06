#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <sys/evt.h>
#include <assert.h>

static int index = 0;
static event_listener_t fn[5];
static QueueHandle_t evtq;

struct Event
{
    enum system_event type;
    uint32_t data;
};

void evt_init(void)
{
    evtq = xQueueCreate(10, sizeof(struct Event));
}

void evt_register_listener(event_listener_t listener)
{
    if (index < sizeof(fn) / sizeof(struct Event))
    {
        fn[index++] = listener;
    } else {
        assert(0);
    }
}

void evt_queue(enum system_event type, uint32_t data)
{
    struct Event evt = {.type = type, .data = data};
    xQueueSend(evtq, &evt, portMAX_DELAY);
}

void evt_queue_from_isr(enum system_event type, uint32_t data)
{
    struct Event evt = {.type = type, .data = data};
    portBASE_TYPE woken;
    xQueueSendFromISR(evtq, &evt, &woken);
    portYIELD_FROM_ISR(woken);
}

void evt_loop(void)
{
    int i;
    struct Event evt;
    if (xQueueReceive(evtq, &evt, 10 / portTICK_PERIOD_MS))
    {
        do
        {
            for (i = 0; i < index; i++)
            {
                if (fn[i])
                {
                    fn[i](evt.type, evt.data);
                }
            }
        } while (xQueueReceive(evtq, &evt, 0));
    }
}
