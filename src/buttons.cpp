#include <Arduino.h>

#include "keyboard.h"
#include "util.h"
#include "buttons.h"

// Button pins
static uint8_t pin_btn_1_s;
static uint8_t pin_btn_2_s;
static uint8_t pin_btn_3_s;
static uint8_t pin_btn_enc_s;

// Previous button states
static bool bt1ActiveState_s = false;
static bool bt2ActiveState_s = false;
static bool bt3ActiveState_s = false;
static bool btEncActiveState_s = false;

// Current button states
static bool bt1Active_s  = false;
static bool bt2Active_s  = false;
static bool bt3Active_s  = false;
static bool btEncActive_s  = false;

// Button setup
void buttons_setup(uint8_t pin_b1, uint8_t pin_b2, uint8_t pin_b3, uint8_t pin_enc)
{
    pinMode(pin_b1, INPUT_PULLUP);
    pinMode(pin_b2, INPUT_PULLUP);
    pinMode(pin_b3, INPUT_PULLUP);
    pinMode(pin_enc, INPUT_PULLUP);
    pin_btn_1_s = pin_b1;
    pin_btn_2_s = pin_b2;
    pin_btn_3_s = pin_b3;
    pin_btn_enc_s = pin_enc;
}

void buttons_update(void)
{
    // Read the button states, default PULL HIGH (aka LOW Activate)
    bt1Active_s  = !digitalRead(pin_btn_1_s);
    bt2Active_s  = !digitalRead(pin_btn_2_s);
    bt3Active_s  = !digitalRead(pin_btn_3_s);
    btEncActive_s  = !digitalRead(pin_btn_enc_s);

    if (bt1ActiveState_s != bt1Active_s)
    {
        bt1ActiveState_s = bt1Active_s;
        if (bt1Active_s)  
        {
            keyboard_press_button(BTN_1, BTM_PRESS);
        }
        else
        {
            keyboard_press_button(BTN_1, BTM_RELEASE);
        }
    }

    // Button 2
    if (bt2ActiveState_s != bt2Active_s)
    {
        bt2ActiveState_s = bt2Active_s;
        if (bt2Active_s)  
        {
            keyboard_press_button(BTN_2, BTM_PRESS);
        }
        else
        {
            keyboard_press_button(BTN_2, BTM_RELEASE);
        }
    }

    // Button 3
    if (bt3ActiveState_s != bt3Active_s)
    {
        bt3ActiveState_s = bt3Active_s;
        if (bt3Active_s)  
        {
            keyboard_press_button(BTN_3, BTM_PRESS);
        }
        else
        {
            keyboard_press_button(BTN_3, BTM_RELEASE);
        }
    }

    // Button Encoder
    if (btEncActiveState_s != btEncActive_s)
    {
        btEncActiveState_s = btEncActive_s;
        if (btEncActive_s)  
        {
            keyboard_press_button(BTN_ENC, BTM_PRESS);
        }
        else
        {
            keyboard_press_button(BTN_ENC, BTM_RELEASE);
        }
    }
    if (btEncActive_s  && bt1Active_s  && bt2Active_s  && bt3Active_s)
    {
        // go in bootloader mode if press all buttons
        BOOT_now();
    }
}