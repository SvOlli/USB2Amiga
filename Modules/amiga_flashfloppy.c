/*
 * written by SvOlli
 *
 * distributed under the terms of the GPLv3 or later
 */

#include "gpio.h"
#include "amiga_api.h"

#if defined(PIN_FF_NEXT) && defined(PIN_FF_PREV)
/* mod and key are USB codes */
void amiga_handle_flashfloppy( uint8_t mod, uint8_t key, bool press )
{
  if( mod == 0x05 ) // modifier: L.CTRL+L.ALT
  {
    switch( key )
    {
    case 0x4f: // CS>
      if( press )
      {
        pull_down( PIN_FF_NEXT );
      }
      else
      {
        weak_pullup( PIN_FF_NEXT );
      }
      break;
    case 0x50: // CS<
      if( press )
      {
        pull_down( PIN_FF_PREV );
      }
      else
      {
        weak_pullup( PIN_FF_PREV );
      }
      break;
    case 0x52: // CS^
      if( press )
      {
        pull_down( PIN_FF_NEXT );
        pull_down( PIN_FF_PREV );
      }
      else
      {
        weak_pullup( PIN_FF_NEXT );
        weak_pullup( PIN_FF_PREV );
      }
      break;
    default:
      break;
    }
  }
}
#endif
