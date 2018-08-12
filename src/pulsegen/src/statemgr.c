#include "pulsegen/statemgr.h"

#include <stdbool.h>
#include "pulsegen/systate.h"

struct limits
{
    const uint32_t max_freq;
    const uint32_t max_duty;
    const uint32_t max_level;
    const uint32_t max_pulse;
    const uint32_t max_pause;
    const uint32_t max_count;

    const uint32_t min_freq;
    const uint32_t min_duty;
    const uint32_t min_level;
    const uint32_t min_pulse;
    const uint32_t min_pause;
    const uint32_t min_count;
};

struct priv_state
{
    bool active;
    bool output;
    enum error error;
    enum mode mode;
    enum system_setting adjust_setting;
    uint32_t pulse_time;
    uint32_t pause_time;
    uint32_t frequency;
    uint32_t duty;
    uint32_t level;
    uint32_t count;
    uint32_t position;
};

static struct priv_state state;

static const struct limits limits = {
    .max_count = 999,
    .max_duty = 99,
    .max_freq = 99999,
    .max_level = 99,
    .max_pulse = 999999,
    .max_pause = 999999,

    .min_count = 1,
    .min_duty = 1,
    .min_freq = 1,
    .min_level = 1,
    .min_pulse = 1,
    .min_pause = 1,
};

static bool get_active(void)
{
    return state.active;
}

static bool get_output(void)
{
    return state.output;
}

static enum error get_error(void)
{
    return state.error;
}

static void set_error(enum error error)
{
    state.error = error;
}
static enum mode get_mode(void)
{
    return state.mode;
}

static uint32_t get_pulse_time(void)
{
    return state.pulse_time;
}

static uint32_t get_pause_time(void)
{
    return state.pause_time;
}

static uint32_t get_frequency(void)
{
    return state.frequency;
}

static uint32_t get_duty(void)
{
    return state.duty;
}

static uint32_t get_level(void)
{
    return state.level;
}

static uint32_t get_count(void)
{
    return state.count;
}

static enum system_setting get_adjust_setting(uint32_t *position)
{
    *position = state.position;
    return state.adjust_setting;
}

static void adjust_value(struct priv_state *st, enum system_event evt)
{
    uint32_t *setting = 0, lim_max = 0, lim_min = 0;
    switch (st->adjust_setting)
    {
    case PULSE_TIME:
        setting = &st->pulse_time;
        lim_max = limits.max_pulse;
        lim_min = limits.min_pulse;
        break;
    case PAUSE_TIME:
        setting = &st->pause_time;
        lim_max = limits.max_pause;
        lim_min = limits.min_pause;
        break;
    case LEVEL:
        setting = &st->level;
        lim_max = limits.max_level;
        lim_min = limits.min_level;
        break;
    case FREQUENCY:
        setting = &st->frequency;
        lim_max = limits.max_freq;
        lim_min = limits.min_freq;
        break;
    case COUNT:
        setting = &st->count;
        lim_max = limits.max_count;
        lim_min = limits.min_count;
        break;
    case DUTY:
        setting = &st->duty;
        lim_max = limits.max_duty;
        lim_min = limits.min_duty;
        break;
    case NONE:
        return;
    }
    if (evt == EVT_ENC_DOWN)
    {
        *setting -= st->position;
        if (*setting < lim_min)
        {
            *setting += st->position;
        }
    }
    else
    {
        *setting += st->position;
        if (*setting > lim_max)
        {
            *setting -= st->position;
        }
    }
}

static void adjust_setting(struct priv_state *st, enum system_setting set)
{
    uint32_t lim_max = 0;
    switch (set)
    {
    case PULSE_TIME:
        lim_max = limits.max_pulse;
        break;
    case PAUSE_TIME:
        lim_max = limits.max_pause;
        break;
    case LEVEL:
        lim_max = limits.max_level;
        break;
    case COUNT:
        lim_max = limits.max_count;
        break;
    case FREQUENCY:
        lim_max = limits.max_freq;
        break;
    case DUTY:
        lim_max = limits.max_duty;
        break;
    case NONE:
        lim_max = 0;
        break;
    }
    if (st->position >= (lim_max + 1) / 1)
    {
        st->adjust_setting = NONE;
        st->position = 0;
        return;
    }
    if (st->adjust_setting != set)
    {
        st->adjust_setting = set;
        st->position = 1;
        return;
    }
    st->position *= 10;
}

static void update(enum system_event evt, void *args)
{
    if (evt != EVT_ENC_PUSH && evt != EVT_ENC_DOWN && evt != EVT_ENC_UP)
    {
        state.active = false;
    }
    switch (evt)
    {
    case EVT_KEY_MODE:
        state.mode = !state.mode;
        state.adjust_setting = NONE;
        break;
    case EVT_KEY_FREQ:
        if (state.mode == PWM)
        {
            adjust_setting(&state, FREQUENCY);
        }
        else
        {
            adjust_setting(&state, PULSE_TIME);
        }
        break;
    case EVT_KEY_DUTY:
        if (state.mode == PWM)
        {
            adjust_setting(&state, DUTY);
        }
        else
        {
            adjust_setting(&state, PAUSE_TIME);
        }
        break;
    case EVT_KEY_COUNT:
        if (state.mode == PULSE)
        {
            adjust_setting(&state, COUNT);
        }
        break;
    case EVT_KEY_LEVEL:
        adjust_setting(&state, LEVEL);
        break;
    case EVT_ENC_DOWN:
        adjust_value(&state, EVT_ENC_DOWN);
        break;
    case EVT_ENC_UP:
        adjust_value(&state, EVT_ENC_UP);
        break;
    case EVT_ENC_PUSH:
        state.adjust_setting = NONE;
        state.active = !state.active;
        break;
    default:
        break;
    }
}

static void load_state(struct priv_state *st)
{
    st->level = 340;
    st->frequency = 1000;
    st->duty = 50;
    st->pulse_time = 1000;
    st->pause_time = 1000;
    st->adjust_setting = NONE;
    st->output = false;
}

void set_param(enum system_setting param, uint32_t value)
{
    switch (param)
    {
    case PAUSE_TIME:
        if (value < limits.max_pause)
        {
            state.pause_time = value;
        }
        break;
    case PULSE_TIME:
        if (value < limits.max_pulse)
        {
            state.pulse_time = value;
        }
        break;
    case LEVEL:
        if (value < limits.max_level)
        {
            state.level = value;
        }
        break;
    case COUNT:
        if (value < limits.max_count)
        {
            state.count = value;
        }
        break;
    case FREQUENCY:
        if (value < limits.max_freq)
        {
            state.frequency = value;
        }
        break;
    case DUTY:
        if (value < limits.max_duty)
        {
            state.duty = value;
        }
        break;
    case NONE:
        break;
    }
}

void state_init(struct system_state *st)
{
    load_state(&state);
    st->get_pulse_time = get_pulse_time;
    st->get_active = get_active;
    st->get_adjust_setting = get_adjust_setting;
    st->get_count = get_count;
    st->get_duty = get_duty;
    st->get_error = get_error;
    st->get_frequency = get_frequency;
    st->get_level = get_level;
    st->get_mode = get_mode;
    st->get_output = get_output;
    st->get_pause_time = get_pause_time;
    st->get_pulse_time = get_pulse_time;
    st->set_error = set_error;
    st->update = update;
    st->set_parameter = set_param;
}
