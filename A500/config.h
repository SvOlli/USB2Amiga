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
#define PIN_KB_DATA  (3)
#define PIN_KB_CLK   (2)
#define PIN_KB_RESET A2

/* pin configuration Amiga mouse */
#define PIN_DB9_Y2 (4) /* Pin 1 on DB9 */
#define PIN_DB9_X1 (5) /* Pin 2 on DB9 */
#define PIN_DB9_Y1 (6) /* Pin 3 on DB9 */
#define PIN_DB9_X2 (7) /* Pin 4 on DB9 */
#define PIN_DB9_LB (8) /* Pin 6 on DB9 */
#define PIN_DB9_RB A0  /* Pin 9 on DB9 */
#define PIN_DB9_MB A1  /* Pin 5 on DB9, optional */
                       /* Pin 8 on DB9 is GND */
                       /* Pin 7 on DB9 is +5V, which is typically not needed*/

#endif
