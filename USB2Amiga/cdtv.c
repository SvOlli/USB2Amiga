/*
 
 Uses: 
 Timer1 (OCR1A) to generate CDTV serial protocol.
 
 The CDTV IR protocol uses a 40kHz carrier when transmitting.
 It sends a 9ms start pulse followed by a 4.5ms pause.
 Then it sends 12 bits, each consisting of a 400us pulse, then
 a 400us (for a 0 bit) or 1200us (for a 1 bit) pause. It then sends
 the same 12 bits inversed. Finally a 400us pulse is sent. 
 Total = 9000 + 4500 + 24 * 1200 + 400 = 42700 us
 Rest = 60000 - 42700 = 17300 us
 
 If a button is held. It sends 'repeat' code every 60ms which is a 9ms
 pulse, followed by a 2.1ms pause and lastly a 400us pulse. 
 Total = 9000 + 2100 + 400 = 11500 us
 Rest = 60000 - 11500 = 48500 us
 
 This work was built on information gathered from:
 http://www.amiga.org/forums/archive/index.php/t-60087.html
 https://github.com/hkzlab/AVR-Experiments/tree/master/samples/m128-ir-cdtv
 
 CD-1253 Mouse uses another simple asynchronous serial protocol over the 
 same (PRDT) line.
 This was reverese engineered by myself (matsstaff)

 Startbit:  pull low 1100us, release 375us
 Data (19 bits): low 500us,  release 375us (sending a 1)
                 low 138us,  release 735us (sending a 0)
 Stop bit:  pull low  88us,  release 
 
 The data (19 bits) is send MSB first
 first bit is unknown (always one), might be reserved for middle button
 second bit is right mouse button, 1 = released, 0 = pressed
 third  bit is left  mouse button, 1 = released, 0 = pressed
 then 8 bits signed horizontal movement, negative = right, positive = left
 last 8 bits signed vertical   movement, negative = down , positive = up
 
 Packets are sent every ~32ms when movement occurs, each packet is approx
 18ms, so there's a ~14ms gap between packets.  
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
 */

#include "Arduino.h"
#include "cdtv.h"
#include "config.h"

#if USE_CDTV_MOUSE_JOY

#define BUFSIZE 16
static volatile int8_t head=0, tail=0;

#if   F_CPU >= 24000000L
#error 24MHz not defined
#warning just using multiply will overflow 16 bit timer
#elif F_CPU >= 20000000L
#error 20MHz not defined
#elif F_CPU >= 16000000L
#define TIMER_US(x) ((x) << 1)
#elif F_CPU >= 12000000L
#define TIMER_US(x) ((x) + ((x) >> 1))
#elif F_CPU >=  8000000L
#define TIMER_US(x) (x)
#else
#error 1MHz not defined
#endif

void cdtv_init(){

  // init datapin
  weak_pullup(PRDTPIN);

  // init joystick
  weak_pullup(A0); // right
  weak_pullup(A1); // left
  weak_pullup(A2); // down
  weak_pullup(A3); // up
  weak_pullup(A4); // b
  weak_pullup(A5); // a

  PCMSK1 |= (1 << PCINT13) | (1 << PCINT12) | (1 << PCINT11) | (1 << PCINT10) | (1 << PCINT9) | (1 << PCINT8);
  PCICR |= (1 << PCIE1); // Enable pinchange interrupt
  
  // Setup timer1 to generate timer interrupts (CTC mode)
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = 0x20; // compare match register 16MHz/8
  TCCR1B |= (1 << WGM12); // CTC mode
  //  TCCR1B |= (1 << CS11); // 8 prescaler (but start disabled)
  TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt

}

// Joystick interrupt
ISR(PCINT1_vect) {
  TCCR1B |= (1 << CS11); // Make sure timer is enabled
}

uint16_t joystick_get_state(){
  uint8_t joy_s = (~PINC & 0x3F);
  return joy_s ? (0x800UL | (joy_s<<2)) : 0;
}

static volatile int16_t mouse_x=0, mouse_y=0;
static volatile uint8_t mouse_buttons=0;
void mouse_set_state(uint8_t buttons, int8_t x, int8_t y) {
  noInterrupts();
#if USE_CDTV_MOUSE_JOY
  if( x == -1 )
  {
    --mouse_x;
  }
  else if( x == 1 )
  {
    ++mouse_x;
  }
  else
  {
    mouse_x = mouse_x + (x/2);
  }
  if( y == -1 )
  {
    --mouse_y;
  }
  else if( y == 1 )
  {
    ++mouse_y;
  }
  else
  {
    mouse_y = mouse_y + (y/2);
  }
#else
  mouse_x = mouse_x - (mouse_x >> 1) + x; // Leaky integration
  mouse_y = mouse_y - (mouse_y >> 1) + y;
#endif
  mouse_buttons |= buttons;
  interrupts();
  TCCR1B |= (1 << CS11); // Make sure timer is enabled
}

/* Called from timer interrupt */
uint8_t mouse_get_state(uint32_t *ms) {
  uint8_t mx = -mouse_x; //invert
  uint8_t my = -mouse_y;
  uint8_t rv = mouse_buttons || mx || my;

  *ms = (((uint32_t)(mouse_buttons ^ 0x7)) << 16) | ((uint16_t)mx) << 8 | my;

  // Reset mouse state
  mouse_x=0;
  mouse_y=0;
  mouse_buttons=0;

  return rv; 
}

enum transmitstates {
  tx_idle=0,
  ir_start,
  ir_transmit,                  // 2
  ir_end_pulse=ir_transmit+48,  // 50
  ir_stop,
  ir_repeat,
  ir_repeat_end_pulse,
  ir_repeat_stop,
  ir_repeat_stop2,
  m_start,                      // 56
  m_transmit,                   // 57
  m_stop=m_transmit+38,
  m_stop2
};

ISR(TIMER1_COMPA_vect) {
  static uint16_t joy_state=0;
  static uint8_t tx_state=0;
  static uint32_t mouse=0;

  if(tx_state == tx_idle){
    uint16_t new_joy_state = joystick_get_state();
    
    if(new_joy_state || joy_state){
      tx_state = (new_joy_state == joy_state) ? ir_repeat : ir_start;
      joy_state = new_joy_state;
      pull_down(PRDTPIN);
      OCR1A = TIMER_US(9000); // 9ms start pulse
      TCNT1 = 0;
    } else if(mouse_get_state(&mouse)) {
      tx_state = m_start;
      pull_down(PRDTPIN);
      OCR1A = TIMER_US(1100); // 1.1ms start pulse
      TCNT1 = 0;
    } else {
      TCCR1B &= ~(1 << CS11); // disable timer
    }
  } else if(tx_state < m_start) { // PAD
    if(tx_state == ir_start){
      weak_pullup(PRDTPIN);
      OCR1A = TIMER_US(4500); // 4.5ms pause
      tx_state++;
    } 
    else if(tx_state<ir_end_pulse){
      uint8_t ss = tx_state - ir_transmit;
      if((ss & 0x1) == 0){ // Pulse
        pull_down(PRDTPIN);
        OCR1A = TIMER_US(400);
      } else { // Pause
        weak_pullup(PRDTPIN);
        ss = ss >> 1;
        if(ss >= 12){
          ss -= 12;
        }
        ss = 11 - ss;
        if(tx_state > ir_transmit + 24){
          OCR1A = (joy_state >> ss & 0x1) ? TIMER_US(400) : TIMER_US(1200);
        } else {
          OCR1A = (joy_state >> ss & 0x1) ? TIMER_US(1200) : TIMER_US(400);
        }
      }
      tx_state++;
    } 
    else if(tx_state==ir_end_pulse){
      pull_down(PRDTPIN);
      OCR1A = TIMER_US(400);
      tx_state++;
    } 
    else if(tx_state==ir_stop){
      weak_pullup(PRDTPIN);
      OCR1A = TIMER_US(17300); // Allow some space
      tx_state = tx_idle;
    } 
    else if(tx_state==ir_repeat){
      weak_pullup(PRDTPIN);
      OCR1A = TIMER_US(2100); // pause
      tx_state++;
    }
    else if(tx_state==ir_repeat_end_pulse){
      pull_down(PRDTPIN);
      OCR1A = TIMER_US(400);
      tx_state++;
    } 
    else if(tx_state==ir_repeat_stop){
      weak_pullup(PRDTPIN);
      OCR1A = TIMER_US(24250); // Allow some space
      tx_state++;
    } 
    else if(tx_state==ir_repeat_stop2){
      OCR1A = TIMER_US(24250); // Allow some space
      tx_state = tx_idle;
    }
  } else { // MOUSE
    if(tx_state == m_start){
      weak_pullup(PRDTPIN);
      OCR1A = TIMER_US(375); // 375us pause
      tx_state++;
    } else if(tx_state < m_stop) {
      uint8_t ss = tx_state - m_transmit; // ss goes from 0 to 37
      uint8_t bitv = (mouse >> (18 - (ss >> 1))) & 0x1;
      if((ss & 0x1) == 0){ // Pulse
        pull_down(PRDTPIN);
        OCR1A = bitv ? TIMER_US(500) : TIMER_US(138);
      } else { // pause
        weak_pullup(PRDTPIN);
        OCR1A = bitv ? TIMER_US(375) : TIMER_US(735);
      }
      tx_state++;
    } else if(tx_state == m_stop){
        pull_down(PRDTPIN);
        OCR1A = TIMER_US(88); // 88us stop pulse
        tx_state++;
    } else { // m_stop2
        weak_pullup(PRDTPIN);
        OCR1A = TIMER_US(14000);        // 14ms pause
        tx_state = tx_idle;
    }
  }
}

#endif
