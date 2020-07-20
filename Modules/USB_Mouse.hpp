/*
 * written by SvOlli after reading the 
 * Arduino USB Host Shield library 2.0 example code USBHIDBootKbdAndMouse
 *
 * distributed unter the terms of the GPLv3 or later
 */

#ifndef __USB_MOUSE_HPP__
#define __USB_MOUSE_HPP__ __USB_MOUSE_HPP__

#include <hidboot.h>
#include <usbhub.h>
#include <stdint.h>

class MouseRptParser : public MouseReportParser
{
public:
  MouseRptParser();
  void flush();
protected:
  /* callback API from Arduino */
  void OnMouseMove( MOUSEINFO *mi );
  void OnLeftButtonUp( MOUSEINFO *mi );
  void OnLeftButtonDown( MOUSEINFO *mi );
  void OnRightButtonUp( MOUSEINFO *mi );
  void OnRightButtonDown( MOUSEINFO *mi );
  void OnMiddleButtonUp( MOUSEINFO *mi );
  void OnMiddleButtonDown( MOUSEINFO *mi );
private:
  int8_t mDx, mDy;
  uint8_t mButtons;
};
extern MouseRptParser MousePrs;

#endif
