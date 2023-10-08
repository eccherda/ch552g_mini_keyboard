#ifndef USER_USB_RAM
#error "Require USB RAM. Go Tools > USB Setting and pick the 2nd option in the dropdown list"
#endif

#include "src/userUsbHidKeyboardMouse/USBHIDKeyboardMouse.h"
#include "src/neo/neo.h"
#include "win-zh_util.h"

////////////// HARDWARE CONFIG //////////

// Button (Mechnical, left to right)
#define PIN_BTN_1 11
#define PIN_BTN_2 17
#define PIN_BTN_3 16
#define PIN_BTN_ENC 33

#define ENCODER_A 31
#define ENCODER_B 30

// Key colors (hue value: 0..191)
#define NEO_RED 0     // red
#define NEO_YEL 32    // yellow
#define NEO_GREEN 64  // green
#define NEO_CYAN 96   // cyan
#define NEO_BLUE 128  // blue
#define NEO_MAG 160   // magenta
#define NEO_BRIGHT_KEYS 2

#define LED_PIN 34  // Pin for the LED strip, configure neo leds in src/neo/config.h

///////////////// RUNTIME ///////////////
// Previous button states
bool bt1ActiveState = false;
bool bt2ActiveState = false;
bool bt3ActiveState = false;
bool btEncActiveState = false;

// Current button states
bool bt1Active = false;
bool bt2Active = false;
bool bt3Active = false;
bool btEncActive = false;

enum button_t {
  BTN_1,
  BTN_2,
  BTN_3,
  BTN_ENC,
  ENC_CW,
  ENC_CCW
};

enum mode_t {
  MODE_NORMAL,
  MODE_GAME,
  MODE_AUTO,
  MODE_MENU
};

enum mode_t current_mode = MODE_NORMAL;
enum mode_t menu_mode = MODE_NORMAL;

int color_hue[3] = { 0, 0, 0 };  // hue value: 0..191 color map

// ===================================================================================
// Move to internal Bootloader
// ===================================================================================
inline void BOOT_now(void) {
  USB_CTRL = 0;
  EA = 0;
  TMOD = 0;
  __asm lcall #BOOT_LOAD_ADDR __endasm;
}

// ===================================================================================
// Menu section
// ===================================================================================

void set_menu_led() {
  switch (menu_mode) {
    case MODE_NORMAL:
      color_hue[0] = NEO_RED;
      color_hue[1] = NEO_YEL;
      color_hue[2] = NEO_YEL;
      break;
    case MODE_GAME:
      color_hue[0] = NEO_YEL;
      color_hue[1] = NEO_RED;
      color_hue[2] = NEO_YEL;
      break;
    case MODE_AUTO:
      color_hue[0] = NEO_YEL;
      color_hue[1] = NEO_YEL;
      color_hue[2] = NEO_RED;
      break;
  }
}
void enter_menu() {
  menu_mode = current_mode;
  current_mode = MODE_MENU;
  set_menu_led();
}

Keyboard_press_normal(enum button_t button) {
  switch (button) {
    case BTN_1:
      Keyboard_write('A');
      break;
    case BTN_2:
      Keyboard_write('B');
      break;
    case BTN_3:
      Keyboard_write('C');
      break;
    case BTN_ENC:
      enter_menu();
      break;
    case ENC_CW:
      Keyboard_write('E');
      break;
    case ENC_CCW:
      Keyboard_write('F');
      break;
    default:
      break;
  }
}

Keyboard_press_game(enum button_t button) {
  switch (button) {
    case BTN_1:
      Keyboard_write('1');
      break;
    case BTN_2:
      Keyboard_write('2');
      break;
    case BTN_3:
      Keyboard_write('3');
      break;
    case BTN_ENC:
      enter_menu();
      break;
    case ENC_CW:
      Keyboard_write('5');
      break;
    case ENC_CCW:
      Keyboard_write('6');
      break;
    default:
      break;
  }
}

Keyboard_press_auto(enum button_t button) {
  switch (button) {
    case BTN_1:
      Keyboard_write('q');
      break;
    case BTN_2:
      Keyboard_write('w');
      break;
    case BTN_3:
      Keyboard_write('e');
      break;
    case BTN_ENC:
      Keyboard_write('r');
      break;
    case ENC_CW:
      enter_menu();
      break;
    case ENC_CCW:
      Keyboard_write('y');
      break;
    default:
      break;
  }
}

Keyboard_press_menu(enum button_t button) {
  switch (button) {
    case BTN_1:

      break;
    case BTN_2:

      break;
    case BTN_3:

      break;
    case BTN_ENC:
      current_mode = menu_mode;
      color_hue[0] = NEO_GREEN;
      color_hue[1] = NEO_GREEN;
      color_hue[2] = NEO_GREEN;
      return;
      break;
    case ENC_CW:
      if (menu_mode >= MODE_AUTO) {
        menu_mode = MODE_AUTO;
      } else {
        menu_mode++;
      }
      break;
    case ENC_CCW:
      if (menu_mode <= MODE_NORMAL) {
        menu_mode = MODE_NORMAL;
      } else {
        menu_mode--;
      }

      break;
    default:
      break;
  }

  set_menu_led();
}

void pressButton(enum button_t button) {
  switch (current_mode) {
    case MODE_NORMAL:
      Keyboard_press_normal(button);
      break;
    case MODE_GAME:
      Keyboard_press_game(button);
      break;
    case MODE_AUTO:
      Keyboard_press_auto(button);
      break;
    case MODE_MENU:
      Keyboard_press_menu(button);
      break;
  }
}

// ===================================================================================
// Encoder section
// ============================================================================

void encoder_cw() {
  pressButton(ENC_CW);
}

void encoder_ccw() {
  pressButton(ENC_CCW);
}

void encoder_setup() {
  pinMode(ENCODER_A, INPUT_PULLUP);
  pinMode(ENCODER_B, INPUT_PULLUP);
}

void encoder_update() {
  if (!digitalRead(ENCODER_A)) {
    if (digitalRead(ENCODER_B)) {
      encoder_cw();
      delay(5);  // debounce
    } else {
      encoder_ccw();
      delay(5);  // debounce
    }
    while (!digitalRead(ENCODER_A))
      ;
  }
}

// ===================================================================================
// Color section
// ============================================================================

void update_color() {
  NEO_writeHue(0, color_hue[0], NEO_BRIGHT_KEYS);  // light up corresponding NeoPixel
  NEO_writeHue(1, color_hue[1], NEO_BRIGHT_KEYS);  // light up corresponding NeoPixel
  NEO_writeHue(2, color_hue[2], NEO_BRIGHT_KEYS);  // light up corresponding NeoPixel
  NEO_update();                                    // update pixels
}

// ===================================================================================
// Main section
// ============================================================================
// Initialize pins
void setup() {

  NEO_init();
  delay(100);
  NEO_clearAll();

  // Go in bootloader more if connected with encoder pressed
  if (!digitalRead(PIN_BTN_ENC)) {
    for (int i = 3 * NEO_COUNT; i; i--)
      NEO_sendByte(127);
    BOOT_now();
  }

  encoder_setup();
  USBInit();
}

void loop() {

  // Read the button states, default PULL HIGH (aka LOW Activate)
  bt1Active = !digitalRead(PIN_BTN_1);
  bt2Active = !digitalRead(PIN_BTN_2);
  bt3Active = !digitalRead(PIN_BTN_3);
  btEncActive = !digitalRead(PIN_BTN_ENC);

  if (bt1ActiveState != bt1Active) {
    bt1ActiveState = bt1Active;
    if (bt1Active) {
      pressButton(BTN_1);  // update pixels
    }
  }

  // Button 2
  if (bt2ActiveState != bt2Active) {
    bt2ActiveState = bt2Active;
    if (bt2Active) {
      pressButton(BTN_2);
    }
  }

  // Button 3
  if (bt3ActiveState != bt3Active) {
    bt3ActiveState = bt3Active;
    if (bt3Active) {
      pressButton(BTN_3);
    }
  }

  // Button Encoder
  if (btEncActiveState != btEncActive) {
    btEncActiveState = btEncActive;
    if (btEncActive) {
      pressButton(BTN_ENC);
    }
  }
  encoder_update();
  update_color();
  delay(5);  // debouncing
}
