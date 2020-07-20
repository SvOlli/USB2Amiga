/*
 * written by SvOlli
 */

#ifndef __PINCFG_H__
#define __PINCFG_H__ __PINCFG_H__

#include <Arduino.h>

#ifndef DEBUG
#define DEBUG (0)
#endif

/* pin configuration Amiga keyboard
 * PIN_KB_RESET is typically the same as PIN_KB_CLK,
 * except for the A500 where it has to be a dedicated pin */
#define PIN_KB_DATA  (3)
#define PIN_KB_CLK   (2)
#define PIN_KB_RESET PIN_KB_CLK

/* pin configuration CDTV data and joy input */
#define PIN_CDTV_PRDT (6)
#define PIN_CDTV_JOY_UP (A0)
#define PIN_CDTV_JOY_DOWN (A1)
#define PIN_CDTV_JOY_LEFT (A2)
#define PIN_CDTV_JOY_RIGHT (A3)
#define PIN_CDTV_JOY_A (A4)
#define PIN_CDTV_JOY_B (A5)

#if 0
/* pin configuration Amiga mouse */
#define PIN_DB9_X1 (4)
#define PIN_DB9_X2 (5)
#define PIN_DB9_Y1 (6)
#define PIN_DB9_Y2 (7)
#define PIN_DB9_LB (8)
#define PIN_DB9_RB (9)
#define PIN_DB9_MB (1)
#endif

#endif
