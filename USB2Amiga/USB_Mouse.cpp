
#include "USB_Mouse.hpp"
#include "config.h"

/* sanity check */
#if USE_CDTV_MOUSE_JOY && USE_AMIGA_MOUSE
#error Only one of USE_CDTV_MOUSE_JOY and USE_AMIGA_MOUSE may be used
#endif

#if USE_CDTV_MOUSE_JOY
#include "cdtv.h"
#endif

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
#if USE_CDTV_MOUSE_JOY
  mouse_set_state( mButtons, mDx, mDy );
#endif
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
