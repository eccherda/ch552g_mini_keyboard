# USB Mini Keyboard with CH552G

## Introduction
This project began with the purchase of a compact USB keyboard with three keys from AliExpress, seemingly without any specific purpose in mind. The original software required for this keyboard was provided as a .exe file, which I downloaded from a Google Drive repository. However, since I don't have access to a Windows PC to test it, I'm quite certain that most antivirus software would not approve of it.

I decided to open it and try to program it myself.

![Keyboard](img/keyboard.jpeg)

![Menu](img/key_menu.gif?raw=true)

Change keyboard config rotating the encoder while is pressed


## What's Inside

The core of the board features a wch-ic CH552G microcontroller, three buttons, a rotary encoder, and three addressable LEDs.

![Bottom](img/bottom.jpeg?raw=true)

## CH552G microcontroller

![CH552G](img/ch552g.png?raw=true)


## How to Build

This firmware uses the Arduino platform to simplify the build process. I built it on a MacBook Pro with an M1 chip.

1. Install the Arduino IDE.
2. Add support for CH552G:
   - Go to Preferences -> Additional Board Manager.
   - Add https://raw.githubusercontent.com/DeqingSun/ch55xduino/ch55xduino/package_ch55xduino_mcs51_index.json.
3. Open the project `ch552g_mini_keyboard.ino`.
   - In the Tools menu, select CH55xDuino board.
   - In Tools, select bootloader: P3.6 (D+) Pull up.
   - In Tools, select clock source: 16MHz (internal) 3.5V or 5V.
   - In Tools, select upload method: USB.
   - In Tools, select USB Setting: USER CODE w/148B USB RAM.
4. Compile the project.
5. Set the keyboard in bootloader mode (see below).
6. Flash the project. (*Original firmware will be completed lost*)

## Setting up the Keyboard in Bootloader Mode

To enter bootloader mode, CH552G require connect pin P3.6 to vcc with a 10K pull-up resistor. To do this:
- Short the R12 on the bottom of the board and connect the board to your PC.
  ![Short](img/short.jpeg?raw=true)
- You can now proceed to flash the firmware.
- Once the firmware is successfully flashed, to *return to bootloader mode, reconnect the USB interface while either pressing the encoder button or in running mode simultaneously press all the buttons*.

```C
  // Go in bootloader more if connected with encoder button pressed
  if (!digitalRead(PIN_BTN_ENC))
  {
    NEO_writeHue(0, NEO_CYAN, NEO_BRIGHT_KEYS); // set led1 to cyan
    NEO_writeHue(1, NEO_BLUE, NEO_BRIGHT_KEYS); // set led2 to blue
    NEO_writeHue(2, NEO_MAG, NEO_BRIGHT_KEYS); //  set led3 to magenta
    NEO_update();                              // update pixels
    BOOT_now();     // jump to bootloader
  }
```



# Firmware feature

This firmware as can setup keyboard in different configuration.
Edit configuration.cpp to change it
To change configuration keep press rotary encoder and change configuration.

On configurtion is possible to send keyboard or mous event and setup automatic cycle rutine

![Menu](img/key_menu.gif?raw=true)

Current configuration
```C
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
```

## Pinout

- BUTTON 1: P16
- BUTTON 2: P17
- BUTTON 3: P11
- BUTTON R: P33
- ENCODER A: P31
- ENCODER B: P30
- LED: P34

## Additional resources

Here are the resources I used for reprogramming the firmware:

- [How to Program a Really Cheap Microcontroller](https://hackaday.com/2019/02/17/how-to-program-a-really-cheap-microcontroller/#more-345535)
- [RGB Macropad Custom Firmware](https://hackaday.io/project/189914-rgb-macropad-custom-firmware)
- [CH552G Macropad Plus](https://oshwlab.com/wagiminator/ch552g-macropad-plus)
- [ch554_sdcc on GitHub](https://github.com/Blinkinlabs/ch554_sdcc)
- [ch55xduino on GitHub](https://github.com/DeqingSun/ch55xduino)
- [CH552G Product Page](https://www.esclabs.in/product/ch552g-8-bit-usb-device-microcontroller/)
- [LCSC Product Page](https://www.lcsc.com/product-detail/Microcontroller-Units-MCUs-MPUs-SOCs_WCH-Jiangsu-Qin-Heng-CH552G_C111292.html?utm_source=digipart&utm_medium=cpc&utm_campaign=CH552G)
- [CH552G Datasheet](http://www.wch-ic.com/downloads/file/309.html)

