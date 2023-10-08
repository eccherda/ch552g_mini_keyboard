#pragma once
#include <stdint.h>

// setup encoder pins connected to the rotary encoder
void encoder_setup(uint8_t pin_a, uint8_t pin_b);

// update encoder task
void encoder_update( void );

