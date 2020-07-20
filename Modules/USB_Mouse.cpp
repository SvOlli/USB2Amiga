/*
 * written by SvOlli after reading the 
 * Arduino USB Host Shield library 2.0 example code USBHIDBootKbdAndMouse
 *
 * distributed unter the terms of the GPLv3 or later
 */

#include "USB_Mouse.hpp"
#include "gpio.h"

#include "amiga_api.h"

MouseRptParser::MouseRptParser()
: MouseReportParser()
, mDx(0)
, mDy(0)
, mButtons(0)
{
}

void MouseRptParser::flush()
{
#if DEBUG
  if( mDx | mDy )
  {
    char buffer[0x10];
    sprintf( buffer, "%d:%d", mDx, mDy );
    Serial.println( buffer );
  }
#endif
  amiga_mouse_update( mButtons, mDx, mDy );
  mDx = 0;
  mDy = 0;
}

void MouseRptParser::OnMouseMove( MOUSEINFO *mi )
{
  /* TODO: this should protected against over-/underflow */
  mDx += mi->dX;
  mDy += mi->dY;
}

void MouseRptParser::OnLeftButtonDown( MOUSEINFO *mi )
{
  mButtons |= 0x01;
}

void MouseRptParser::OnLeftButtonUp( MOUSEINFO *mi )
{
  mButtons &= ~0x01;
}

void MouseRptParser::OnRightButtonDown( MOUSEINFO *mi )
{
  mButtons |= 0x02;
}

void MouseRptParser::OnRightButtonUp( MOUSEINFO *mi )
{
  mButtons &= ~0x02;
}

void MouseRptParser::OnMiddleButtonDown( MOUSEINFO *mi )
{
  mButtons |= 0x04;
}

void MouseRptParser::OnMiddleButtonUp( MOUSEINFO *mi )
{
  mButtons &= ~0x04;
}
