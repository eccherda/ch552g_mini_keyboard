# USB Mini Keyboard with CH552G

## Introduction
This project began with the purchase of a compact USB keyboard with three keys from AliExpress, seemingly without any specific purpose in mind. The original software required for this keyboard was provided as a .exe file, which I downloaded from a Google Drive repository. However, since I don't have access to a Windows PC to test it, I'm quite certain that most antivirus software would not approve of it.

I decided to open it and try to program it myself.

![Keyboard](https://github.com/eccherda/ch552g_mini_keyboard/blob/master/image.jpg?raw=true)

## What's Inside

The core of the board features a wch-ic CH552G microcontroller, three buttons, a rotary encoder, and three addressable LEDs.

![Keyboard](https://github.com/eccherda/ch552g_mini_keyboard/blob/master/image.jpg?raw=true)

## CH552G microcontroller

![Keyboard](https://github.com/eccherda/ch552g_mini_keyboard/blob/master/image.jpg?raw=true)

## Resources

Here are the resources I found for reprogramming the firmware:

- [How to Program a Really Cheap Microcontroller](https://hackaday.com/2019/02/17/how-to-program-a-really-cheap-microcontroller/#more-345535)
- [RGB Macropad Custom Firmware](https://hackaday.io/project/189914-rgb-macropad-custom-firmware)
- [CH552G Macropad Plus](https://oshwlab.com/wagiminator/ch552g-macropad-plus)
- [ch554_sdcc on GitHub](https://github.com/Blinkinlabs/ch554_sdcc)
- [ch55xduino on GitHub](https://github.com/DeqingSun/ch55xduino)
- [CH552G Product Page](https://www.esclabs.in/product/ch552g-8-bit-usb-device-microcontroller/)
- [LCSC Product Page](https://www.lcsc.com/product-detail/Microcontroller-Units-MCUs-MPUs-SOCs_WCH-Jiangsu-Qin-Heng-CH552G_C111292.html?utm_source=digipart&utm_medium=cpc&utm_campaign=CH552G)
- [CH552G Datasheet](http://www.wch-ic.com/downloads/file/309.html)

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

To set the keyboard in bootloader mode, connect pin P3.6 to a 10K pullup to Vcc. To do this, short R12 pin and connect the board to a PC. Now you can flash the firmware. Once this firmware is flashed, to return to bootloader mode, connect the USB interface while pressing the encoder button.

See `ch552g_mini_keyboard.ino` line 70:

```cpp
  // Go into bootloader mode if connected with encoder button pressed
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
To change configuration keep press rotary ecoder and change configuration.
Corrent configuration are:
* 1 PC
   * Button 1 CTRL+c
   * Button 2 CTRL+v
   * Button 3 CTRL+q
   * Rotary encoder: mouse scroll
* 1 MAC
   * Button 1 CMD+c
   * Button 2 CMD+v
   * Button 3 CTCMDRL+q
   * Rotary encoder: mouse scroll
* 2 MAAUTOC
   * Button 1 Start auto: mouse start mooving on screen
   * Button 2 StaStoprt auto: mouse stop mooving on screen
   * Button 3 NA 
   * Rotary encoder: change mouse size

## Pinout
/* KEY MAPPING */

BUTTON 1: P16
BUTTON 2: P17
BUTTON 3: P11
BUTTON R: P33

ENCODER A: P31
ENCODER B: P30

LED: P34
