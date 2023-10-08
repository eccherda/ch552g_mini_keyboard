#pragma once

#include <stdint.h>

#define NUM_CONFIGURATION 5
typedef enum 
{
  BTN_1,
  BTN_2,
  BTN_3,
  ENC_CW,
  ENC_CCW,
  BTN_ENC,
  BTN_NUM,
}keyboard_button_t;

typedef enum 
{
  BTM_PRESS,
  BTM_RELEASE,
  BTM_CLICK,
}keyboard_button_keyboard_mode_t;


typedef enum 
{
  UP,
  DOWN,
  LEFT,
  RIGH,
  LEFT_CLICK,
  RIGHT_CLICK,
  SCROLL_UP,
  SCROLL_DOWN
}mouse_event_type_t;

typedef struct 
{
  mouse_event_type_t type;
  uint8_t value;
} mouse_event_t;
 
//Send button sequence with delay, if length is 0, send release when released
typedef struct 
{
  uint8_t sequence[100]; // array of button presses 
  uint8_t length; // length of the array
  uint8_t delay; // ms delay between presses, if 0 keep all buttons pressed
}button_sequence_t;

typedef enum 
{
  BUTTON_SEQUENCE, // send button_sequence_t tyoe
  BUTTON_MOUSE,    // send button_mouse_t type
  BUTTON_AUTO_KEYBOARD,    // send continuosly button_sequence_t tyoe
  BUTTON_AUTO_MOUSE,    // send continuosly button_mouse_t type
  BUTTON_FUNCTION, // send function pointer
  BUTTON_NULL, // dont do nothing
}keyboard_button_type;



//Send button and send release when released
typedef struct 
{
  mouse_event_t mouse_event_sequence[30]; // array of mouse event sequences
  uint8_t length; // length of the array
  uint8_t delay; // ms delay between event
  uint8_t keypress; // keypress to send with the mouse event
}button_mouse_t;


typedef struct 
{
  keyboard_button_type type;
  union  // anonymous union
  {
    button_sequence_t sequence;
    button_mouse_t mouse;
    void (*functionPointer)(keyboard_button_keyboard_mode_t mode);
  }function;
}button_function_t;

typedef struct 
{
   button_function_t  button[BTN_NUM];
}keyboard_configuration_t;



// keyboard_press_button is called
void keyboard_press_button( keyboard_button_t button,  keyboard_button_keyboard_mode_t mode);

// keyboard setup 
void keyboard_setup(void);

// keyboard encoder press to enter in menu
void keyboard_press_enc(keyboard_button_keyboard_mode_t mode);

// keyboard menu scroll uo
void button_menu_up(keyboard_button_keyboard_mode_t mode);

// keyboard menu scroll down
void button_menu_down(keyboard_button_keyboard_mode_t mode);

