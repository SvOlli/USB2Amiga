
#ifndef __USB_KEYBOARD_HPP__
#define __USB_KEYBOARD_HPP__ __USB_KEYBOARD_HPP__

#include <hidboot.h>
#include <usbhub.h>
#include <stdint.h>

class KbdRptParser : public KeyboardReportParser
{
public:
  KbdRptParser();
protected:
  void OnControlKeysChanged( uint8_t before, uint8_t after );
  void OnKeyDown( uint8_t mod, uint8_t key );
  void OnKeyUp( uint8_t mod, uint8_t key );
private:
  bool mCapsLock;
  bool mReset;
};
extern KbdRptParser KbdPrs;

#endif
