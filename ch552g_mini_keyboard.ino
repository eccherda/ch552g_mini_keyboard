#ifndef USER_USB_RAM
#error "Require USB RAM. Go Tools > USB Setting and pick the 2nd option in the dropdown list"
#endif

#include "src/userUsbHidMediaKeyboard/USBHIDMediaKeyboard.h"
#include "src/neo/neo.h"
#include "win-zh_util.h"

////////////// HARDWARE CONFIG //////////

//Button (Mechnical, left to right)
#define BTN_1 11
#define BTN_2 17
#define BTN_3 16
#define BTN_ENC 33

// Key colors (hue value: 0..191)
#define NEO_RED          0         // red
#define NEO_YEL          32        // yellow
#define NEO_GREEN          64        // green
#define NEO_CYAN          96        // cyan
#define NEO_BLUE          128       // blue
#define NEO_MAG          160       // magenta
#define NEO_BRIGHT_KEYS   2 

#define LED_PIN 34 //Pin for the LED strip, configure neo leds in src/neo/config.h

#define ENCODER_A 31
#define ENCODER_B 30

///////////////// RUNTIME ///////////////
//Previous button states
bool bt1ActiveState = false;
bool bt2ActiveState = false;
bool bt3ActiveState = false;
bool btEncActiveState = false;

//Current button states
bool bt1Active = false;
bool bt2Active = false;
bool bt3Active = false;
bool btEncActive = false;



// ===================================================================================
// Move to internal Bootloader
// ===================================================================================
inline void BOOT_now(void) {
  USB_CTRL = 0;
  EA       = 0;
  TMOD     = 0;
  __asm
    lcall #BOOT_LOAD_ADDR
  __endasm;
}

// Encoder selated functions 

int color_hue = 0;   


void update_color() {
  NEO_writeHue(0, color_hue, NEO_BRIGHT_KEYS);    // light up corresponding NeoPixel
  NEO_writeHue(1, color_hue, NEO_BRIGHT_KEYS);    // light up corresponding NeoPixel
  NEO_writeHue(2, color_hue, NEO_BRIGHT_KEYS);    // light up corresponding NeoPixel
  NEO_update();                             // update pixels
}

void encoder_cw() {
  color_hue += 5;   
  if (color_hue > 160){                       // increase hue by 32 (1/6 of 192)
    color_hue = 160;                          // wrap around at 192
  }
  Keyboard_write('P');
  update_color();                            // update pixels
}

void encoder_ccw() {
  color_hue -= 5;   
  if (color_hue <= 0){                       // increase hue by 32 (1/6 of 192)
    color_hue = 0;                          // wrap around at 192
  }
  Keyboard_write('M');
  update_color();                            // update pixels
}

void encoder_setup() {
  pinMode(ENCODER_A, INPUT_PULLUP);
  pinMode(ENCODER_B, INPUT_PULLUP);

}

void encoder_update() {
  if(!digitalRead(ENCODER_A)) {                    // encoder turned ?
      if(digitalRead(ENCODER_B)) {                   // clockwise ?
        encoder_cw();
        delay(5);
      }
      else {                                      // counter-clockwise ?
        encoder_ccw();
        delay(5);
      }
      while(!digitalRead(ENCODER_A));                // wait until next detent
      Keyboard_write('Q');
    } 
}

// Initialize pins
void setup() {

  NEO_init();
  delay(100);
  NEO_clearAll(); 

  // Go in bootloader more if connected with encoder pressed
  if (!digitalRead(BTN_ENC)){
    for(int i=3*NEO_COUNT; i; i--) NEO_sendByte(127);
    BOOT_now(); 
  }

  
  encoder_setup();
  USBInit();



}

void loop() {

  

  //Read the button states, default PULL HIGH (aka LOW Activate)
  bt1Active = !digitalRead(BTN_1);
  bt2Active = !digitalRead(BTN_2);
  bt3Active = !digitalRead(BTN_3);
  btEncActive = !digitalRead(BTN_ENC);


  if (bt1ActiveState != bt1Active) {
    bt1ActiveState = bt1Active;
    if (bt1Active) {
      Keyboard_write('A');
      NEO_writeHue(0, NEO_RED, NEO_BRIGHT_KEYS);    // light up corresponding NeoPixel
      NEO_update();                             // update pixels
    }
  }

  //Button 2
  if (bt2ActiveState != bt2Active) {
    bt2ActiveState = bt2Active;
    if (bt2Active) {
      Keyboard_write('B');
      NEO_writeHue(1, NEO_GREEN, NEO_BRIGHT_KEYS);    // light up corresponding NeoPixel
      NEO_update();
    }
  }


  //Button 3
  if (bt3ActiveState != bt3Active) {
    bt3ActiveState = bt3Active;
    if (bt3Active) {
      Keyboard_write('C');
      NEO_writeHue(2, NEO_BLUE, NEO_BRIGHT_KEYS);    // light up corresponding NeoPixel
      NEO_update();
    }
  }

  //Button 4
  if (btEncActiveState != btEncActive) {
    btEncActiveState = btEncActive;
    if (btEncActive) {
      Keyboard_write('D');
      NEO_clearAll();
      NEO_update();
    }
  }
  encoder_update();

  


  delay(5);  //naive debouncing
}
