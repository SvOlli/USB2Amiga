/*
 * written by SvOlli
 * after taking a look a https://github.com/cssvb94/AmigaUSBMouseJoystick
 *
 * distributed unter the terms of the GPLv3 or later
 */

#ifndef __AMIGA_MOUSE_H__
#define __AMIGA_MOUSE_H__ __AMIGA_MOUSE_H__

void amims_init();
void mouse_set_state( uint8_t buttons, int8_t x, int8_t y );

#endif
