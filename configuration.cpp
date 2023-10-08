#include "configuration.h"
#include "src/userUsbHidKeyboardMouse/USBHIDKeyboardMouse.h"

const keyboard_configuration_t configurations[NUM_CONFIGURATION] = {
    {
        .button = { // Configuration copy paste keyboard
            [BTN_1] = {
                .type = BUTTON_SEQUENCE,
                .function.sequence = {
                    .sequence = {KEY_LEFT_CTRL, 'c'}, // ctrl + c
                    .length = 2,            // Lengh of sequence
                    .delay = 0             // no delay
                }
            },
            [BTN_2] = {
                .type = BUTTON_SEQUENCE,
                .function.sequence = {
                    .sequence = {KEY_LEFT_CTRL, 'v'}, // ctrl + v
                    .length = 2,            // Lengh of sequence
                    .delay = 0             // no delay
                }
            },
            [BTN_3] = {
                .type = BUTTON_SEQUENCE,
                .function.sequence = {
                    .sequence = {KEY_LEFT_CTRL, 'z'}, // ctrl + z
                    .length = 2,            // Lengh of sequence
                    .delay = 0             // no delay
                }
            },
            [ENC_CW] = { // scroll up
                .type = BUTTON_MOUSE,
                .function.mouse = {
                    .mouse_event_sequence = {
                        {
                            .type = SCROLL_DOWN,
                            .value = 2
                        }
                    },
                    .length = 1,
                    .delay = 0,
                    .keypress = 0 // Valore della pressione del tasto del mouse
                }
            },
            [ENC_CCW] = {   // scroll down
                .type = BUTTON_MOUSE,
                .function.mouse = {
                    .mouse_event_sequence = {
                        {
                            .type = SCROLL_UP,
                            .value = 2
                        }
                    },
                    .length = 1,
                    .delay = 0,
                    .keypress = 0 // Valore della pressione del tasto del mouse
                }
            },
            [BTN_ENC] = {
                .type = BUTTON_FUNCTION,
                .function.functionPointer = keyboard_press_enc,
            },
        }
    },
    {   // Configuration photoshop
        .button = { // 
            [BTN_1] = {
                .type = BUTTON_SEQUENCE,
                .function.sequence = {
                    .sequence = {'e'}, // e
                    .length = 1,            // Lengh of sequence
                    .delay = 0             // no delay
                }
            },
            [BTN_2] = {
                .type = BUTTON_SEQUENCE,
                .function.sequence = {
                    .sequence = {'s'}, // s
                    .length = 1,            // Lengh of sequence
                    .delay = 0             // no delay
                }
            },
            [BTN_3] = {
                .type = BUTTON_MOUSE,
                .function.mouse = {
                    .mouse_event_sequence = {
                        {
                            .type = LEFT_CLICK,
                            .value = 1
                        }
                    },
                    .length = 1,
                    .delay = 0,
                    .keypress = KEY_LEFT_ALT // Valore della pressione del tasto del mouse
                }
            },
            [ENC_CW] = {
                .type = BUTTON_MOUSE,
                .function.mouse = {
                    .mouse_event_sequence = {
                        {
                            .type = SCROLL_UP,
                            .value = 1
                        }
                    },
                    .length = 1,
                    .delay = 0,
                    .keypress = KEY_LEFT_ALT // Valore della pressione del tasto del mouse
                }
            },
            [ENC_CCW] = {
                .type = BUTTON_MOUSE,
                .function.mouse = {
                    .mouse_event_sequence = {
                        {
                            .type = SCROLL_DOWN,
                            .value = 1
                        }
                    },
                    .length = 1,
                    .delay = 0,
                    .keypress = KEY_LEFT_ALT // Valore della pressione del tasto del mouse
                }
            },
            [BTN_ENC] = {
                .type = BUTTON_FUNCTION,
                .function.functionPointer = keyboard_press_enc,
            },
        }
    },
    {   // Configuration game
        .button = { // 
            [BTN_1] = {
                .type = BUTTON_SEQUENCE,
                .function.sequence = {
                    .sequence = {'a','a','a','a'}, // multi a
                    .length = 4,            // Lengh of sequence
                    .delay = 50             // no delay
                }
            },
            [BTN_2] = {
                .type = BUTTON_SEQUENCE,
                .function.sequence = {
                    .sequence = {'b','b','b','b','b','b','b','b'}, // multi b
                    .length = 8,            // Lengh of sequence
                    .delay = 50             // no delay
                }
            },
            [BTN_3] = {
                .type = BUTTON_MOUSE,
                .function.mouse = { //multi click
                    .mouse_event_sequence = {
                        {
                            .type = LEFT_CLICK,
                            .value = 1
                        },
                        {
                            .type = LEFT_CLICK,
                            .value = 1
                        },
                        {
                            .type = LEFT_CLICK,
                            .value = 1
                        },
                        {
                            .type = LEFT_CLICK,
                            .value = 1
                        },
                        {
                            .type = LEFT_CLICK,
                            .value = 1
                        }
                    },
                    .length = 5,
                    .delay = 0,
                    .keypress = KEY_LEFT_ALT // Valore della pressione del tasto del mouse
                }
            },
            [ENC_CW] = {
                .type = BUTTON_MOUSE,
                .function.mouse = {
                    .mouse_event_sequence = {
                        {
                            .type = SCROLL_UP,
                            .value = 1
                        }
                    },
                    .length = 1,
                    .delay = 0,
                    .keypress = KEY_LEFT_ALT // Valore della pressione del tasto del mouse
                }
            },
            [ENC_CCW] = {
                .type = BUTTON_MOUSE,
                .function.mouse = {
                    .mouse_event_sequence = {
                        {
                            .type = SCROLL_DOWN,
                            .value = 1
                        }
                    },
                    .length = 1,
                    .delay = 0,
                    .keypress = KEY_LEFT_ALT // Valore della pressione del tasto del mouse
                }
            },
            [BTN_ENC] = {
                .type = BUTTON_FUNCTION,
                .function.functionPointer = keyboard_press_enc,
            },
        }
    },
    {   // Automatic keyboard
        .button = { // 
            [BTN_1] = {
                .type = BUTTON_AUTO_KEYBOARD,
                .function.sequence = {
                    .sequence = {'#', 'i', 'n', 'c', 'l', 'u', 'd', 'e', ' ', '<', 's', 't', 'd', 'i', 'o', '.', 'h', '>', '\n', '\n', 'i', 'n', 't', ' ', 'm', 'a', 'i', 'n', '(', ')', '\n', '{', '\n', ' ', ' ', ' ', 'p', 'r', 'i', 'n', 't', 'f', '(', '"', 'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '"', ')', ';', '\n', '\n', ' ', ' ', ' ', 'r', 'e', 't', 'u', 'r', 'n', ' ', '0', ';', '\n', '}', '\n'}, // multi a
                    .length = 73,            // Lengh of sequence
                    .delay = 50             // no delay
                }
            },
            [BTN_2] = {
                .type = BUTTON_AUTO_MOUSE,
                .function.mouse = { //multi click
                    .mouse_event_sequence = {
                        {
                            .type = UP,
                            .value = 40
                        },
                        {
                            .type = RIGH,
                            .value = 40
                        },
                        {
                            .type = DOWN,
                            .value = 40
                        },
                        {
                            .type = LEFT,
                            .value = 40
                        }
                    },
                    .length = 4,
                    .delay = 50,
                    .keypress = 0 // Valore della pressione del tasto del mouse
                }
            },
            [BTN_3] = {
                .type = BUTTON_NULL,
            },
            [ENC_CW] = {
                .type = BUTTON_MOUSE,
                .function.mouse = {
                    .mouse_event_sequence = {
                        {
                            .type = SCROLL_UP,
                            .value = 1
                        }
                    },
                    .length = 1,
                    .delay = 0,
                    .keypress = 0 // Valore della pressione del tasto del mouse
                }
            },
            [ENC_CCW] = {
                .type = BUTTON_MOUSE,
                .function.mouse = {
                    .mouse_event_sequence = {
                        {
                            .type = SCROLL_DOWN,
                            .value = 1
                        }
                    },
                    .length = 1,
                    .delay = 0,
                    .keypress = 0 // Valore della pressione del tasto del mouse
                }
            },
            [BTN_ENC] = {
                .type = BUTTON_FUNCTION,
                .function.functionPointer = keyboard_press_enc,
            },
        }
    },
    {   //Menu configuration
        .button = { // Configurtion copy paste keyboard
            [BTN_1] = {
                .type = BUTTON_NULL,
            },
            [BTN_2] = {
                .type = BUTTON_NULL,
            },
            [BTN_3] = {
                .type = BUTTON_NULL,
            },
            [ENC_CW] = {
                .type = BUTTON_FUNCTION,
                .function.functionPointer = button_menu_up,
            },
            [ENC_CCW] = {
                .type = BUTTON_FUNCTION,
                .function.functionPointer = button_menu_down,
            },
            [BTN_ENC] = {
                .type = BUTTON_FUNCTION,
                .function.functionPointer = keyboard_press_enc,
            },
        }
    },
};