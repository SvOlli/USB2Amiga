/*
 * written by SvOlli after reading the 
 * Arduino USB Host Shield library 2.0 example code USBHIDBootKbdAndMouse
 *
 * distributed under the terms of the GPLv3 or later
 */

#ifndef __USB_KEYBOARD_HPP__
#define __USB_KEYBOARD_HPP__ __USB_KEYBOARD_HPP__

#include <hidboot.h>
#include <usbhub.h>
#include <stdint.h>


class KeyRptParserCallback
{
public:
  /* inputs are the same as OnKeyUp/Down, return is stop processing */
  /* mod and key passed as reference to allow modifying */
  virtual bool handle( uint8_t &mod, uint8_t &key, bool press ) = 0;
};


class KbdRptParser : public KeyboardReportParser
{
public:
  KbdRptParser();
  void setCallback( KeyRptParserCallback *callback ) { mpCallback = callback; }
protected:
  void OnControlKeysChanged( uint8_t before, uint8_t after );
  void OnKeyDown( uint8_t mod, uint8_t key );
  void OnKeyUp( uint8_t mod, uint8_t key );
private:
  bool mReset;
  KeyRptParserCallback *mpCallback;
};
extern KbdRptParser KbdPrs;

#endif /* __USB_KEYBOARD_HPP__ */
