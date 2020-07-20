/*
 * written by SvOlli
 * after taking a look a https://github.com/cssvb94/AmigaUSBMouseJoystick
 *
 * distributed unter the terms of the GPLv3 or later
 */

#include <Arduino.h>
#include "config.h"
#include <stdbool.h>

#if USE_AMIGA_MOUSE
const int ADELAY = 200;
bool HQ[4] = { false, true, true, false };
bool H[4] =  { false, false, true, true };

uint8_t QX = 3;
uint8_t QY = 3;
uint8_t XSTEPS;
uint8_t YSTEPS;
uint8_t XSIGN;
uint8_t YSIGN;

#define X1PIN (4)
#define X2PIN (5)
#define Y1PIN (6)
#define Y2PIN (7)
#define LBPIN (8)
#define RBPIN (9)
#if USE_AMIGA_MOUSE_MB
#define MBPIN (1)
#endif


void amims_init()
{
  // Disable the watchdog timer (if set in fuses)
  MCUSR &= ~(1 << WDRF);
  wdt_disable();
  // Disable the clock divider (if set in fuses)
  clock_prescale_set(clock_div_1);

  AMIGAHorizontalMove();
  AMIGAVerticalMove();
  weak_pullup( LBPIN );
  weak_pullup( RBPIN );
#if USE_AMIGA_MOUSE_MB
  weak_pullup( MBPIN );
#endif
}


void AMIGAHorizontalMove()
{
  if( H[QX] )
  {
    weak_pullup( X1PIN );
  }
  else
  {
    pull_down( X1PIN );
  }
  if( HQ[QX] )
  {
    weak_pullup( X2PIN );
  }
  else
  {
    pull_down( X2PIN );
  }
  delayMicroseconds(ADELAY);
}


void AMIGAVerticalMove()
{
  if( H[QX] )
  {
    weak_pullup( Y1PIN );
  }
  else
  {
    pull_down( Y1PIN );
  }
  if( HQ[QX] )
  {
    weak_pullup( Y2PIN );
  }
  else
  {
    pull_down( Y2PIN );
  }
  delayMicroseconds(ADELAY);
}


void AMIGALeft()
{
  QX = (QX+1) & 3;
  AMIGAHorizontalMove();
}

void AMIGARight()
{
  QX = (QX-1) & 3;
  AMIGAHorizontalMove();
}

void AMIGADown()
{
  QY = (QY+1) & 3;
  AMIGAVerticalMove();
}

void AMIGAUp()
{
  QY = (QY-1) & 3;
  AMIGAVerticalMove();
}


void mouse_set_state( uint8_t buttons, int8_t x, int8_t y )
{
  while( x > 0 )
  {
    AmigaRight();
    --x;
  }
  while( x < 0 )
  {
    AmigaLeft();
    ++x;
  }
  while( y > 0 )
  {
    AmigaDown();
    --y;
  }
  while( y < 0 )
  {
    AmigaUp();
    ++y;
  }

  if( buttons & 1 )
  {
    pull_down( LBPIN );
  }
  else
  {
    weak_pullup( LBPIN );
  }

  if( buttons & 2 )
  {
    pull_down( RBPIN );
  }
  else
  {
    weak_pullup( RBPIN );
  }

#if USE_AMIGA_MOUSE_MB
  if( buttons & 4 )
  {
    pull_down( MBPIN );
  }
  else
  {
    weak_pullup( MBPIN );
  }
#endif
}
#endif
