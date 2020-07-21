/*
 * Taken from https://github.com/matsstaff/mwd2cdtv
 * written by matsstaff
 * modified by SvOlli
 *
 * distributed under the terms of the GPLv3 or later
 */

#ifndef __CDTV_H__
#define __CDTV_H__ __CDTV_H__

// CDTV CODES
#define CDTV_CODE_1              0x001
#define CDTV_CODE_2              0x021
#define CDTV_CODE_3              0x011
#define CDTV_CODE_4              0x009
#define CDTV_CODE_5              0x029
#define CDTV_CODE_6              0x019
#define CDTV_CODE_7              0x005
#define CDTV_CODE_8              0x025
#define CDTV_CODE_9              0x015
#define CDTV_CODE_0              0x039
#define CDTV_CODE_ESCAPE         0x031
#define CDTV_CODE_ENTER          0x035
#define CDTV_CODE_GENLOCK        0x022
#define CDTV_CODE_CD_TV          0x002
#define CDTV_CODE_POWER          0x012
#define CDTV_CODE_REWIND         0x032
#define CDTV_CODE_PLAY_PAUSE     0x00A
#define CDTV_CODE_FAST_FORWARD   0x01A
#define CDTV_CODE_STOP           0x02A
#define CDTV_CODE_VOLUME_UP      0x006
#define CDTV_CODE_VOLUME_DOWN    0x03A
#define CDTV_CODE_MOUSE_A        0x080
#define CDTV_CODE_MOUSE_B        0x040
#define CDTV_CODE_MOUSE_UP       0x020
#define CDTV_CODE_MOUSE_RIGHT    0x004
#define CDTV_CODE_MOUSE_DOWN     0x010
#define CDTV_CODE_MOUSE_LEFT     0x008
#define CDTV_CODE_JOYSTICK_A     0x880
#define CDTV_CODE_JOYSTICK_B     0x840
#define CDTV_CODE_JOYSTICK_UP    0x820
#define CDTV_CODE_JOYSTICK_RIGHT 0x804
#define CDTV_CODE_JOYSTICK_DOWN  0x810
#define CDTV_CODE_JOYSTICK_LEFT  0x808

#ifdef __cplusplus
extern "C" {
#endif

#include "amiga_api.h"

void cdtv_init();
void cdtv_main();

void amiga_mouse_update( uint8_t buttons, int8_t x, int8_t y );
/* this overrides any code, repeats until code=0 */
void set_cdtv_code( uint16_t code );

#ifdef __cplusplus
}
#endif

#endif // _CDTV_
