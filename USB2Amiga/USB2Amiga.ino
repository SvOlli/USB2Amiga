/*
 * USB to Amiga Keyboard Mouse Joystick converter
 * ==============================================
 * 
 * Hacked together by SvOlli with ideas/code from
 * matsstaff, who used code by hkzlab
 * cssvb94
 * 
 * Distributed unter the terms of the GPLv3 or any later version
 */ 

#include <Arduino.h>
#include <stdint.h>
#include "config.h"
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


void setup()
{
#if DEBUG
  Serial.begin( 115200 );
  while( !Serial )
  {
    /* wait */
  }
  Serial.println( "\r\nAmiga Keyboard " USB2AMIGA_VERSION " starting" );
  Serial.println( "Compiled: " __DATE__ " " __TIME__ );
#endif
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
