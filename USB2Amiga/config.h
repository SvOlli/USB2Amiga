
#ifndef __CONFIG_H__
#define __CONFIG_H__ __CONFIG_H__

#define USB2AMIGA_VERSION "0.8"

#define USE_AMIGA_KEYBOARD (1)
#define USE_CDTV_MOUSE_JOY (1)
#define USE_AMIGA_MOUSE    (0)
#define USE_A500_RESET     (0)

#define DEBUG   (0)

// INT1 on PIN3 (DATAPIN) for ACK, that is DATAPIN needs to be pin 3
#define DATAPIN (3)
#define CLKPIN  (2)
#define PRDTPIN (6)

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
