
#ifndef __CONFIG_H__
#define __CONFIG_H__ __CONFIG_H__

#define USB2AMIGA_VERSION "0.8"

#define USE_AMIGA_KEYBOARD (1)
#define USE_CDTV_MOUSE_JOY (1)
#define USE_AMIGA_MOUSE    (0)
#define USE_A500_RESET     (0)

#ifndef DEBUG
#define DEBUG   (1)
#endif

/* pin definitiion */
/* note: pins 10-13 are used by USB host shield */
/* note: pins 0 and 1 are TX and RX */

/* INT1 on PIN3 (DATAPIN) for ACK, that is DATAPIN needs to be pin 3 */
#define DATAPIN (3)
#define CLKPIN  (2)
#define PRDTPIN (6)

#define DB9OUT_PIN1 (4)
#define DB9OUT_PIN2 (5)
#define DB9OUT_PIN3 (6)
#define DB9OUT_PIN4 (7)
#define DB9OUT_PIN6 (8)
#define DB9OUT_PIN9 (9)
#define DB9OUT_PIN5 (0)

#define X1PIN (DB9OUT_PIN2)
#define X2PIN (DB9OUT_PIN4)
#define Y1PIN (DB9OUT_PIN3)
#define Y2PIN (DB9OUT_PIN1)
#define LBPIN (DB9OUT_PIN6)
#define RBPIN (DB9OUT_PIN9)
#define MBPIN (DB9OUT_PIN5)

/* joy in is only implemented in CDTV mode */
#define JOYIN_PIN1 (A0)
#define JOYIN_PIN2 (A1)
#define JOYIN_PIN3 (A2)
#define JOYIN_PIN4 (A3)
#define JOYIN_PIN6 (A4)
#define JOYIN_PIN9 (A5)


/* yes, I know this is not config, but config.h is the only global
 * include I've got so far */
static inline void weak_pullup( int pin )
{
  pinMode( pin, INPUT );
  digitalWrite( pin, HIGH );
}

static inline void pull_down( int pin )
{
  digitalWrite( pin, LOW );
  pinMode( pin, OUTPUT );
}

#endif
