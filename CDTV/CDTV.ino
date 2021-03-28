/*
 * USB to CDTV Keyboard Mouse Joystick converter
 * =============================================
 * 
 * written by SvOlli
 * 
 * distributed unter the terms of the GPLv3 or any later version
 */ 

#ifndef DEBUG
#define DEBUG   (0)
#endif

#include "gpio.h"

#include <Arduino.h>
#include <stdint.h>
#include "cdtv.h"
#include "amiga_keyb.h"
#include "USB_Mouse.hpp"
#include "USB_Keyboard.hpp"

USB    Usb;
USBHub Hub(&Usb);

HIDBoot<USB_HID_PROTOCOL_KEYBOARD | USB_HID_PROTOCOL_MOUSE> HidComposite(&Usb);
HIDBoot<USB_HID_PROTOCOL_KEYBOARD>                          HidKeyboard(&Usb);
HIDBoot<USB_HID_PROTOCOL_MOUSE>                             HidMouse(&Usb);

KbdRptParser   KbdPrs;
MouseRptParser MousePrs;

class KbdRptParserCDTV : public KeyRptParserCallback
{
public:
  bool handle( uint8_t &mod, uint8_t &key, bool press );
};


bool KbdRptParserCDTV::handle( uint8_t &mod, uint8_t &key, bool press )
{
#if DEBUG
Serial.print( "KbdRptParserCDTV::handle: key=" );
PrintHex<uint8_t>( key, 0x80 );
Serial.print( " mod=" );
PrintHex<uint8_t>( mod, 0x80 );
Serial.println( press ? " press" : " release" );
#endif
  if( (mod == 0) && (key == 0x46) )
  {
#if DEBUG
Serial.println( "Action" );
#endif
    set_cdtv_code( press ? CDTV_CODE_POWER : 0 );
    return true;
  }
#if defined(PIN_FF_NEXT) && defined(PIN_FF_PREV)
  amiga_handle_flashfloppy( mod, key, press );
#endif
  return false;
}
KbdRptParserCDTV KbdPrsCDTV;


void setup()
{
#if DEBUG
  Serial.begin( 115200 );
  while( !Serial )
  {
    /* wait */
  }
  Serial.println( "\r\nAmiga Keyboard starting" );
  Serial.println( "Compiled: " __DATE__ " " __TIME__ );
#endif
  KbdPrs.setCallback( &KbdPrsCDTV );
  cdtv_init();
  amikbd_setup();

  if( Usb.Init() == -1 )
  {
#if DEBUG
    Serial.println( "OSC did not start." );
#endif
    pinMode( 13, OUTPUT );
    for(;;)
    {
      digitalWrite( 13, HIGH );
      delay( 500 );
      digitalWrite( 13, LOW );
      delay( 500 );
    }
  }
  delay( 200 );

  HidComposite.SetReportParser(0, &KbdPrs);
  HidComposite.SetReportParser(1, &MousePrs);
  HidKeyboard.SetReportParser(0, &KbdPrs);
  HidMouse.SetReportParser(0, &MousePrs);
}


void loop()
{
  Usb.Task();
  MousePrs.flush();
  amikbd_update();
}
