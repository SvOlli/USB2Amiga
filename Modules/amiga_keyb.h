/*
 * Taken from https://github.com/matsstaff/mwd2cdtv which itself was
 * taken from https://github.com/hkzlab/AVR-Experiments/tree/master/libs/amiga_keyb
 * written by hkzlab
 * modified by matsstaff and SvOlli
 *
 * distributed unter the terms of the GPLv3 or later
 */

#ifndef __AMIGA_KEYB_H__
#define __AMIGA_KEYB_H__ __AMIGA_KEYB_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "amiga_api.h"

void amikbd_setup();
void amikbd_init();

void amiga_keyboard_send( uint8_t command );
void amiga_keyboard_reset();

void amikbd_update();

#ifdef __cplusplus
}
#endif

#endif /* __AMIGA_KEYB_H__ */
