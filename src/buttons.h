#pragma once

#include <stdint.h>

//Button setup
void buttons_setup(uint8_t pin_b1, uint8_t pin_b2, uint8_t pin_b3, uint8_t pin_enc);

// Button update task
void buttons_update();