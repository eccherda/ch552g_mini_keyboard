// ===================================================================================
// Encoder section
// nice encoder tutorial: https://daniellethurow.com/blog/2021/8/30/how-to-use-quadrature-rotary-encoders
// ============================================================================

#include <Arduino.h>

#include "keyboard.h"

static int prevVal_s = 0;
static int newVal_s;
static unsigned int clockState_s = 0;
static unsigned int counterClockState_s  = 0;

// lookup table for encoder
static int lookupTable_s[4][4] = {{0, -1, 1, 2},
                                  {1, 0, 2, -1},
                                  {-1, 2, 0, 1},
                                  {2, 1, -1, 0}};

static uint8_t encoder_a_s = 0;
static uint8_t encoder_b_s = 0;

static void encoder_cw(void);
static void encoder_ccw(void);

static void encoder_cw(void)
{
    keyboard_press_button(ENC_CW, BTM_CLICK);
}

static void encoder_ccw(void)
{
    keyboard_press_button(ENC_CCW, BTM_CLICK);
}

void encoder_setup(uint8_t pin_a, uint8_t pin_b)
{
    encoder_a_s = pin_a;
    encoder_b_s = pin_b;
    pinMode(pin_a, INPUT_PULLUP);
    pinMode(pin_b, INPUT_PULLUP);
    int valA = digitalRead(encoder_a_s);
    int valB = digitalRead(encoder_b_s);
    prevVal_s = (valA << 1) + valB;
}

void encoder_update()
{
    int valA = digitalRead(encoder_a_s);
    int valB = digitalRead(encoder_b_s);
    newVal_s = (valA << 1) + valB;

    int info = lookupTable_s[prevVal_s][newVal_s];

    if (info == 1)
    {
        clockState_s |= (1 << newVal_s); // set the bit to 1
    }
    else if (info == -1)
    {
        counterClockState_s |= (1 << newVal_s);
    }
    else if (info == 2)
    {
    }

    if (prevVal_s != newVal_s && newVal_s == 3)
    {
        // changed to the non moving state, lets figure out what direction we went!

        // for each clockwise and counterclockwise, the encoder state goes through 4 distinct states
        // make sure it's gone through at least 3 of those (and assume if one is missing it's because I didn't read fast enough)
        if (clockState_s == 0b1011 || clockState_s == 0b1101 || clockState_s == 0b1110 || clockState_s == 0b1111)
        {
            encoder_cw();
        }
        if (counterClockState_s == 0b1011 || counterClockState_s == 0b1101 || counterClockState_s == 0b1110 || counterClockState_s == 0b1111)
        {
            encoder_ccw();
        }

        clockState_s = 0;
        counterClockState_s = 0;
    }
    prevVal_s = newVal_s;
}