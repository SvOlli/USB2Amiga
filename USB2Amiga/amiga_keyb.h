/*
 * This is code from
 * https://github.com/hkzlab/AVR-Experiments/tree/master/libs/amiga_keyb
 * 
 * I just modified it.
 */

#ifndef _AMIGA_KEYBOARD_HEADER_
#define _AMIGA_KEYBOARD_HEADER_

#include <stdint.h>

#define AMI_PRESSED   0x00
#define AMI_RELEASED  0x80

#ifdef __cplusplus
extern "C" {
#endif

void amikbd_setup(void);
void amikbd_init(void);

void amikbd_kSendCommand(uint8_t command); // ORing the command code with 0x80 sets the release bit
void amikbd_kReset(void);

void amikbd_update();

#ifdef __cplusplus
}
#endif

#endif /* _AMIGA_KEYBOARD_HEADER_ */
