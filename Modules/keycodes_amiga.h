/*
 * written by SvOlli
 * after reading the Amiga Hardware Reference Manual
 *
 * distributed unter the terms of the GPLv3 or later
 */

#ifndef __KEYCODESAMIGA_H__
#define __KEYCODESAMIGA_H__ __KEYCODESAMIGA_H__

#include <stdint.h>
 
#ifdef __cplusplus
extern "C" {
#endif
  extern uint8_t usb2amiga[0x80];
  extern uint8_t modifier2amiga[0x08];
#ifdef __cplusplus
}
#endif

#endif
