/*
 * written by SvOlli
 * after taking a look a https://github.com/cssvb94/AmigaUSBMouseJoystick
 *
 * distributed under the terms of the GPLv3 or later
 */

#ifndef __AMIGA_MOUSE_H__
#define __AMIGA_MOUSE_H__ __AMIGA_MOUSE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "amiga_api.h"

void db9_mouse_init();
void amiga_mouse_update( uint8_t buttons, int8_t x, int8_t y );

#ifdef __cplusplus
}
#endif

#endif /* __AMIGA_MOUSE_H__ */
