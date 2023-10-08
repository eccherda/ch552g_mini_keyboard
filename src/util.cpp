#include <Arduino.h>
#include "util.h"


// ===================================================================================
// Move to internal Bootloader
// ===================================================================================
void BOOT_now(void)
{
  USB_CTRL = 0;
  EA = 0;
  TMOD = 0;
  __asm lcall #BOOT_LOAD_ADDR __endasm;
}