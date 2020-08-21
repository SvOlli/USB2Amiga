/*
 * written by SvOlli
 */

#ifndef __CONFIG_H__
#define __CONFIG_H__ __CONFIG_H__

#include <Arduino.h>

#ifndef DEBUG
#define DEBUG (0)
#endif

/* pin configuration Amiga keyboard
 * PIN_KB_RESET is typically the same as PIN_KB_CLK,
 * except for the A500 where it has to be a dedicated pin */
#define PIN_KB_CLK   (2)
#define PIN_KB_DATA  (3)
#define PIN_KB_RESET PIN_KB_CLK

/* pin configuration CDTV data and joy input */
#define PIN_CDTV_PRDT      (6)
#define PIN_CDTV_JOY_UP    A0    /* DB9 pin 1 */
#define PIN_CDTV_JOY_DOWN  A1    /* DB9 pin 2 */
#define PIN_CDTV_JOY_LEFT  A2    /* DB9 pin 3 */
#define PIN_CDTV_JOY_RIGHT A3    /* DB9 pin 4 */
#define PIN_CDTV_JOY_A     A4    /* DB9 pin 6 */
#define PIN_CDTV_JOY_B     A5    /* DB9 pin 9 */

/* pin configuration for controlling flashfloppy */
#define PIN_FF_NEXT  (4)
#define PIN_FF_PREV  (5)

#endif
