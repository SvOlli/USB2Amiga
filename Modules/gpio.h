/*
 * written by SvOlli
 *
 * distributed unter the terms of the GPLv3 or later
 */

#ifndef __GPIO_H__
#define __GPIO_H__ __GPIO_H__

#include <Arduino.h>

static inline void weak_pullup( uint8_t pin )
{
  pinMode( pin, INPUT );
  digitalWrite( pin, HIGH );
}

static inline void pull_down( uint8_t pin )
{
  digitalWrite( pin, LOW );
  pinMode( pin, OUTPUT );
}

/* pin configuration usb host shield 
 * (for documentation purposes only) */
#define              PIN_USB_SS   (10)
#define              PIN_USB_CLK  (11)
#define              PIN_USB_MISO (12)
#define              PIN_USB_MOSI (13)

#include "config.h"

#endif
