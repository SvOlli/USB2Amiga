
#include "USB_Keyboard.hpp"
#include "config.h"

#include "keycodes_amiga.h"
#include "amiga_keyb.h"
#include "cdtv.h"

static inline void amigakey( uint8_t code, bool pressed )
{
  if( code >= 0x80 )
  {
    return;
  }
#if DEBUG
  if( pressed )
  {
    Serial.print( "DOWN amiga=" );
  }
  else
  {
    Serial.print( "UP   amiga=" );
  }
  PrintHex<uint8_t>( code, 0x80 );
  Serial.println();
#endif
  amikbd_kSendCommand( code | (pressed ? 0x00 : 0x80) );
}


KbdRptParser::KbdRptParser()
: KeyboardReportParser()
, mReset( false )
{
}

void KbdRptParser::OnControlKeysChanged( uint8_t before, uint8_t after)
{
#if DEBUG
  MODIFIERKEYS beforeMod;
  *((uint8_t*)&beforeMod) = before;

  MODIFIERKEYS afterMod;
  *((uint8_t*)&afterMod) = after;

  if (beforeMod.bmLeftCtrl != afterMod.bmLeftCtrl)
  {
    Serial.println("LeftCtrl changed");
  }
  if (beforeMod.bmLeftShift != afterMod.bmLeftShift)
  {
    Serial.println("LeftShift changed");
  }
  if (beforeMod.bmLeftAlt != afterMod.bmLeftAlt)
  {
    Serial.println("LeftAlt changed");
  }
  if (beforeMod.bmLeftGUI != afterMod.bmLeftGUI)
  {
    Serial.println("LeftGUI changed");
  }

  if (beforeMod.bmRightCtrl != afterMod.bmRightCtrl)
  {
    Serial.println("RightCtrl changed");
  }
  if (beforeMod.bmRightShift != afterMod.bmRightShift)
  {
    Serial.println("RightShift changed");
  }
  if (beforeMod.bmRightAlt != afterMod.bmRightAlt)
  {
    Serial.println("RightAlt changed");
  }
  if (beforeMod.bmRightGUI != afterMod.bmRightGUI)
  {
    Serial.println("RightGUI changed");
  }
#endif

  for( uint8_t i = 0; i < 8; ++i )
  {
    uint8_t b = 1 << i;
    if( (before & b) != (after & b) )
    {
      if( after & b )
      {
        amigakey( modifier2amiga[i], true );
      }
      else
      {
        amigakey( modifier2amiga[i], false );
      }
    }
  }

  if( mReset )
  {
    mReset = false;
#if DEBUG
    Serial.println( "Sending hard reset" );
#endif
    amikbd_kReset();
  }

  if( (after == 0x89) || (after == 0x98) )
  {
    /* one CTRL and both Amiga/Win Keys */
    amigakey( 0x78, true );
    amigakey( 0x78, true );
    mReset = true;
#if DEBUG
    Serial.println( "Sending reset warning" );
#endif
  }

#if DEBUG
  Serial.print( "MOD  " );
  PrintHex<uint8_t>( before, 0x80 );
  Serial.print( "->" );
  PrintHex<uint8_t>( after, 0x80 );
  Serial.println( "" );
#endif
}


void KbdRptParser::OnKeyDown(uint8_t mod, uint8_t key)
{
#if DEBUG
  Serial.print( "DOWN key=" );
  PrintHex<uint8_t>( key, 0x80 );
  Serial.print( " mod=" );
  PrintHex<uint8_t>( mod, 0x80 );
  Serial.println( "" );
#endif
  if( key == UHS_HID_BOOT_KEY_CAPS_LOCK )
  {
    /* CAPS LOCK */
#if DEBUG
    Serial.print( "CAPS LOCK: " );
    Serial.println( kbdLockingKeys.kbdLeds.bmCapsLock );
#endif
    if( !kbdLockingKeys.kbdLeds.bmCapsLock )
    {
      return;
    }
  }
  amigakey( usb2amiga[key], true );
  if( ((mod & 0x01) || (mod & 0x10)) &&  /* CTRL   */
      ((mod & 0x04) || (mod & 0x40)) &&  /* ALT    */
      ((key == 0x4c) || (key == 0x63)) ) /* DELETE */
  {
    /* CTRL + ALT + DELETE */
    amigakey( 0x78, true );
    amigakey( 0x78, true );
    mReset = true;
#if DEBUG
    Serial.println( "Sending reset warning" );
#endif
  }
  if( key == 0x46 ) /* SysRq */
  {
    set_cdtv_code( CDTV_CODE_POWER );
  }
}

void KbdRptParser::OnKeyUp(uint8_t mod, uint8_t key)
{
#if DEBUG
  Serial.print( "UP   key=" );
  PrintHex<uint8_t>( key, 0x80 );
  Serial.print( " mod=" );
  PrintHex<uint8_t>( mod, 0x80 );
  Serial.println( "" );
#endif
  if( key == UHS_HID_BOOT_KEY_CAPS_LOCK )
  {
    /* CAPS LOCK */
    if( kbdLockingKeys.kbdLeds.bmCapsLock )
    {
      return;
    }
  }
  amigakey( usb2amiga[key], false );
  if( mReset )
  {
    mReset = false;
#if DEBUG
  Serial.println( "Sending hard reset" );
#endif
    amikbd_kReset();
  }
  if( key == 0x46 ) /* SysRq */
  {
    set_cdtv_code( 0 );
  }
}
