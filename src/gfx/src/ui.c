#include "gfx/ui.h"
#include "assert.h"
#include "stdio.h"
#include "string.h"
#include "ugui/ugui.h"
#include "hal/SSD1351.h"

#define UISIM_RGB(R, G, B) (R << 16 | G << 8 | B)

static uint32_t reftimer;
static struct system_state *state;

#define UPDATE_PERIOD 1

static UG_GUI gui;

static UG_RESULT _HW_FillFrame(UG_S16 x1, UG_S16 y1, UG_S16 x2, UG_S16 y2,
                               UG_COLOR c)
{
    // SSD1351_fillframe(x1, y1, x2, y2, c);
    // return UG_RESULT_OK;
    return UG_RESULT_FAIL;
}

static UG_RESULT _HW_DrawLine(UG_S16 x1, UG_S16 y1, UG_S16 x2, UG_S16 y2,
                              UG_COLOR c)
{

    return UG_RESULT_FAIL;
}

void ui_init(struct system_state *_state)
{
    state = _state;

    disp_init();

    UG_Init(&gui, disp_pset, 128, 128);

    UG_DriverRegister(DRIVER_FILL_FRAME, (void *)_HW_FillFrame);
    UG_DriverRegister(DRIVER_DRAW_LINE, (void *)_HW_DrawLine);

    disp_on();

    UG_FontSelect(&FONT_6X10);
    UG_SetBackcolor(UISIM_RGB(0, 0, 0));
    UG_SetForecolor(UISIM_RGB(255, 255, 255));
    UG_FontSetHSpace(0);
}

void ui_timming_tasks(void)
{
    reftimer++;
}

static char *format_str_none(const char *label, char *str, int len,
                             bool blk, uint32_t pos)
{
    int sz = strlen(str);
    char *dst, *src;
    /* we need at least 4 characters for the formatting */
    assert(sz <= len - 4 - strlen(label));
    /* move the last two characters to the end */
    dst = &str[len - 1];
    src = &str[sz - 1];
    *dst-- = '\0';
    *dst-- = blk && (pos == 1) ? '_' : *src;
    src--;
    *dst-- = blk && (pos == 10) ? '_' : *src;
    if (*label != 'D')
    {
        src--;
        if (*label == 'L')
        {
            *dst-- = '.';
        }
        *dst-- = blk && (pos == 100) ? '_' : *src;
        if (*label != 'C' && *label != 'L')
        {
            src--;
            *dst-- = blk && (pos == 1000) ? '_' : *src;
            src--;
            *dst-- = blk && (pos == 10000) ? '_' : *src;
            src--;
            *dst-- = blk && (pos == 100000) ? '_' : *src;
        }
    }

    dst -= strlen(label) - 1;
    src = (char *)label;

    do
    {
        *dst++ = *src++;
    } while (*src != '\0');
    dst -= strlen(label);
    return dst;
}

static char *format_str(const char *label, char *str, int len,
                        bool blk, uint32_t pos)
{
    int sz = strlen(str);
    char *dst, *src;
    /* we need at least 4 characters for the formatting */
    assert(sz <= len - 4 - strlen(label));
    /* move the last two characters to the end */
    dst = &str[len - 1];
    src = &str[sz - 1];
    *dst-- = '\0';
    *dst-- = blk && (pos == 1) ? '_' : *src;
    src--;
    *dst-- = blk && (pos == 10) ? '_' : *src;
    src--;
    *dst-- = '.';
    *dst-- = blk && (pos == 100) ? '_' : *src;
    src--;
    *dst-- = blk && (pos == 1000) ? '_' : *src;
    src--;
    *dst-- = blk && (pos == 10000) ? '_' : *src;
    src--;
    *dst-- = ':';
    *dst-- = blk && (pos == 100000) ? '_' : *src;
    src--;
    *dst-- = blk && (pos == 1000000) ? '_' : *src;

    dst -= strlen(label) - 1;
    src = (char *)label;

    do
    {
        *dst++ = *src++;
    } while (*src != '\0');
    dst -= strlen(label);
    return dst;
}

static void draw_pulse_screen(struct system_state *state, bool blink)
{
    assert(state->get_pulse_time() < 10000000);
    assert(state->get_pause_time() < 10000000);

    char str[20], *tmp;
    bool blk;
    uint32_t position;
    sprintf(str, "%07lu", state->get_pulse_time());

    blk = (state->get_adjust_setting(&position) == PULSE_TIME) && blink;

    tmp = format_str("Pulse: ", str, sizeof(str), blk, position);

    UG_SetBackcolor(UISIM_RGB(0, 0, 0));
    UG_SetForecolor(UISIM_RGB(255, 255, 255));
    UG_PutString(4, 10, tmp);

    sprintf(str, "%07lu", state->get_pause_time());

    blk = (state->get_adjust_setting(&position) == PAUSE_TIME) && blink;

    tmp = format_str("Pause: ", str, sizeof(str), blk, position);

    UG_PutString(4, 25, tmp);
    UG_PutString(25, 80, "Pulse Mode");
}

static void draw_pwm_screen(struct system_state *state, bool blink)
{
    assert(state->get_frequency() < 1000000);
    assert(state->get_frequency() > 0);
    assert(state->get_duty() < 100);
    assert(state->get_duty() > 0);

    char str[20], *tmp;
    bool blk;
    uint32_t position;
    sprintf(str, "%06lu", state->get_frequency());

    blk = (state->get_adjust_setting(&position) == FREQUENCY) && blink;

    tmp = format_str_none("Freq: ", str, sizeof(str), blk, position);

    UG_SetBackcolor(UISIM_RGB(0, 0, 0));
    UG_SetForecolor(UISIM_RGB(255, 255, 255));
    UG_PutString(4, 10, tmp);

    sprintf(str, "%02lu", state->get_duty());

    blk = (state->get_adjust_setting(&position) == DUTY) && blink;

    tmp = format_str_none("Duty: ", str, sizeof(str), blk, position);

    UG_PutString(4, 25, tmp);
    UG_PutString(25, 80, "PWM Mode");
}

static void draw_level(struct system_state *state, bool blink)
{
    assert(state->get_level() < 600);
    assert(state->get_level() > 250);

    char str[20], *tmp;
    bool blk;
    uint32_t position;

    UG_SetBackcolor(UISIM_RGB(0, 0, 0));
    UG_SetForecolor(UISIM_RGB(255, 255, 255));

    sprintf(str, "%03lu", state->get_level());

    blk = (state->get_adjust_setting(&position) == LEVEL) && blink;

    tmp = format_str_none("Level: ", str, sizeof(str), blk, position);

    UG_PutString(4, 65, tmp);
}

static void draw_count(struct system_state *state, bool blink)
{
    assert(state->get_count() < 1000);

    char str[20], *tmp;
    bool blk;
    uint32_t position;
    sprintf(str, "%03lu", state->get_count());

    blk = (state->get_adjust_setting(&position) == COUNT) && blink;

    tmp = format_str_none("Count: ", str, sizeof(str), blk, position);

    UG_SetBackcolor(UISIM_RGB(0, 0, 0));
    UG_SetForecolor(UISIM_RGB(255, 255, 255));
    UG_PutString(4, 50, tmp);
}

static void draw_active(struct system_state *state, bool force_redraw)
{
    static bool last_state = true;
    if (last_state == state->get_active() && !force_redraw)
    {
        return;
    }
    last_state = state->get_active();
    if (state->get_active())
    {
        UG_FillFrame(0, 127, 127, 110, UISIM_RGB(255, 0, 0));
        UG_SetBackcolor(UISIM_RGB(255, 0, 0));
        UG_SetForecolor(UISIM_RGB(255, 255, 255));
        UG_PutString(40, 114, "Active!");
    }
    else
    {
        UG_FillFrame(0, 127, 127, 110, UISIM_RGB(0, 255, 0));
        UG_SetBackcolor(UISIM_RGB(0, 255, 0));
        UG_SetForecolor(UISIM_RGB(255, 255, 255));
        UG_PutString(40, 114, "Inactive!");
    }
    if (state->get_output())
    {
        UG_FillRoundFrame(2, 125, 15, 112, 5, UISIM_RGB(0, 255, 0));
    }
}

void ui_update(void)
{
    static bool blink = false;
    static enum mode old_mode;
    assert(state != NULL);
    /* check if it is time to refresh the display */
    if (reftimer < UPDATE_PERIOD)
    {
        return;
    }
    if (old_mode != state->get_mode())
    {
        /* clear screen */
        UG_FillFrame(0, 0, 128, 108, UISIM_RGB(0, 0, 0));
        old_mode = state->get_mode();
    }
    blink = !blink;
    reftimer = 0;
    if (state->get_mode() == PULSE)
    {
        draw_pulse_screen(state, blink);
        draw_count(state, blink);
    }
    else if (state->get_mode() == PWM)
    {
        draw_pwm_screen(state, blink);
    }
    else
    {
        assert(0);
    }
    draw_level(state, blink);
    draw_active(state, false);
}
