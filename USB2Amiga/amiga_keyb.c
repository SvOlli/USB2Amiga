/*
 * This is code from
 * https://github.com/hkzlab/AVR-Experiments/tree/master/libs/amiga_keyb
 * 
 * modified for correct bus behavior by matsstaff
 */

#include <Arduino.h>
#include "amiga_keyb.h"
#include "config.h"

#define AMI_KBDCODE_SELFTESTFAILED 0xFC
#define AMI_KBDCODE_INITKEYSTREAM  0xFD
#define AMI_KBDCODE_ENDKEYSTREAM   0xFE
#define AMI_KBDCODE_LOSTSYNC       0xF9

// INT1 on PIN3 (DATAPIN) for ACK, that is DATAPIN needs to be pin 3
#ifndef DATAPIN
#define DATAPIN 3
#endif
#ifndef CLKPIN
#define CLKPIN 4
#endif

#define BUFSIZE 16
static uint8_t head=0, tail=0;
static uint8_t buf[BUFSIZE];
static uint8_t lastcmd=0;


static volatile uint8_t synced = 1;
static unsigned long lastsyncattempt=0;

static inline void amikbd_kClock(void);
static inline void amikbd_kToggleData(uint8_t bit);

uint8_t amikbd_kSync(void);


ISR(INT1_vect) {
  synced = 1;
  EIMSK &= ~(1 << INT1); // Disable INT1
}

void amikbd_setup(void) {

  /* Set all the lines to input and disable pull-up resistors!
   * The line will be pulled high by the resistors (10K) inside the Amiga. 
   * When we want to pull a line to low, we simply set the pin to output.
   */

  // Prepare KDAT port
  weak_pullup(CLKPIN);
  weak_pullup(DATAPIN);
  
//  EICRA &= ~((1 << ISC10) | (1 << ISC11)); // Trigger interrupt at LOW LEVEL (INT1)
  EICRA |= ((1 << ISC10) | (1 << ISC11)); // Trigger interrupt at RISING EDGE (INT1)
  EIMSK &= ~(1 << INT1); // Disable INT1
  EIFR |= (1 << INTF1); // Clear interrupt flag
}

// http://amigadev.elowar.com/read/ADCD_2.1/Hardware_Manual_guide/node0177.html
void amikbd_init(void) {
	amikbd_kSync();

	// We should send the "test failed" code here, if any problem is detected

	// Send initializate powerup key stream
	amikbd_kSendCommand(AMI_KBDCODE_INITKEYSTREAM);
	// Here we should send the keycodes for all the "pressed" keyboard keys...
	// But I will simply suppose there is none

	amikbd_kSendCommand(AMI_KBDCODE_ENDKEYSTREAM);
	//amikbd_kSendCommand(0x35); // TODO: Check if this is really useless

}

// Clock the keyboard line
static inline void amikbd_kClock(void) {
  delayMicroseconds(20);
  pull_down(CLKPIN);
  delayMicroseconds(20);
  weak_pullup(CLKPIN);
  delayMicroseconds(20);
}

void amikbd_kReset(void) {
  pull_down(CLKPIN);
  delay(600);
  weak_pullup(CLKPIN);
}

static inline void amikbd_kToggleData(uint8_t bit) {
	if (bit){
    pull_down(DATAPIN);
	} else {
    weak_pullup(DATAPIN);
	}
	amikbd_kClock();
}


// http://amigadev.elowar.com/read/ADCD_2.1/Hardware_Manual_guide/node0173.html
void amikbd_transfer(uint8_t command) {
  weak_pullup(DATAPIN);

  amikbd_kToggleData((command >> 6) & 1);
  amikbd_kToggleData((command >> 5) & 1);
  amikbd_kToggleData((command >> 4) & 1);
  amikbd_kToggleData((command >> 3) & 1);
  amikbd_kToggleData((command >> 2) & 1);
  amikbd_kToggleData((command >> 1) & 1);
  amikbd_kToggleData((command >> 0) & 1);
  amikbd_kToggleData((command >> 7) & 1);

  weak_pullup(DATAPIN);

  delayMicroseconds(10); // Allow short time to settle

  lastsyncattempt = millis();
  synced = 0;

  // Wait for sync
  EIMSK |= (1 << INT1); // Enable INT1
}

void amikbd_update(){
  static uint8_t prevsync = 0;
  if(synced == 0 && millis() - lastsyncattempt > 143){
    amikbd_kClock(); 
    lastsyncattempt = millis();
    prevsync = 1;
  } else if(synced) {
    if(prevsync == 1) {
      amikbd_transfer(AMI_KBDCODE_LOSTSYNC);
      prevsync = 2;
    } else if (prevsync == 2) {
      amikbd_transfer(lastcmd);
      prevsync = 0;
    } else if (head != tail) {
      lastcmd = buf[head];
      head = (head+1) % BUFSIZE;
      amikbd_transfer(lastcmd);
    }
  }
}

void amikbd_kSendCommand(uint8_t command) {
  uint8_t t = (tail + 1) % BUFSIZE;
  
  if (command == 0xFF || head == t){
    return;
  }

  buf[tail] = command;
  tail = t;
}
