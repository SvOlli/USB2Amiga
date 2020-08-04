/*
 * written by SvOlli
 * after taking a look a https://github.com/cssvb94/AmigaUSBMouseJoystick
 *
 * distributed under the terms of the GPLv3 or later
 */

#include <Arduino.h>
#include "gpio.h"
#include <stdbool.h>

const int ADELAY = 200;

uint8_t QX = 0;
uint8_t QY = 0;


void outputX()
{
  switch( QX )
  {
    case 0:
      weak_pullup( PIN_DB9_X1 );
      weak_pullup( PIN_DB9_X2 );
      break;
    case 1:
      weak_pullup( PIN_DB9_X1 );
      pull_down( PIN_DB9_X2 );
      break;
    case 2:
      pull_down( PIN_DB9_X1 );
      pull_down( PIN_DB9_X2 );
      break;
    case 3:
      pull_down( PIN_DB9_X1 );
      weak_pullup( PIN_DB9_X2 );
      break;
    default:
      break;
  }
  delayMicroseconds(ADELAY);
}


void outputY()
{
  switch( QY )
  {
    case 0:
      weak_pullup( PIN_DB9_Y1 );
      weak_pullup( PIN_DB9_Y2 );
      break;
    case 1:
      weak_pullup( PIN_DB9_Y1 );
      pull_down( PIN_DB9_Y2 );
      break;
    case 2:
      pull_down( PIN_DB9_Y1 );
      pull_down( PIN_DB9_Y2 );
      break;
    case 3:
      pull_down( PIN_DB9_Y1 );
      weak_pullup( PIN_DB9_Y2 );
      break;
    default:
      break;
  }
  delayMicroseconds(ADELAY);
}


void db9_mouse_init()
{
#if 0
  // Disable the watchdog timer (if set in fuses)
  MCUSR &= ~(1 << WDRF);
  wdt_disable();
  // Disable the clock divider (if set in fuses)
  clock_prescale_set(clock_div_1);
#endif

  outputX();
  outputY();
  weak_pullup( PIN_DB9_LB );
  weak_pullup( PIN_DB9_RB );
#if USE_AMIGA_MOUSE_MB
  weak_pullup( PIN_DB9_MB );
#endif
}


void amiga_mouse_update( uint8_t buttons, int8_t x, int8_t y )
{
  while( x > 0 )
  {
    QX = (QX-1) & 3;
    outputX();
    --x;
  }
  while( x < 0 )
  {
    QX = (QX+1) & 3;
    outputX();
    ++x;
  }
  while( y > 0 )
  {
    QY = (QY+1) & 3;
    outputY();
    --y;
  }
  while( y < 0 )
  {
    QY = (QY-1) & 3;
    outputY();
    ++y;
  }

  if( buttons & 1 )
  {
    pull_down( PIN_DB9_LB );
  }
  else
  {
    weak_pullup( PIN_DB9_LB );
  }

  if( buttons & 2 )
  {
    pull_down( PIN_DB9_RB );
  }
  else
  {
    weak_pullup( PIN_DB9_RB );
  }

#if USE_AMIGA_MOUSE_MB
  if( buttons & 4 )
  {
    pull_down( PIN_DB9_MB );
  }
  else
  {
    weak_pullup( PIN_DB9_MB );
  }
#endif
}
