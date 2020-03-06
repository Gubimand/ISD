///////////////////////////////////////////////////////////
//
// Source file : 	main.c
// Author :			malthe
// Date :			Mar 6, 2020
// Version :		0.1
//
// Description :
//		Using the Pocket beagle PRU 1
//		reads from shared memory and corrects output
///////////////////////////////////////////////////////////

#include <stdint.h>
#include <pru_cfg.h>
#include "resource_table_empty.h"
#include "prugpio.h"

volatile register uint32_t __R30;    //Output register
volatile register uint32_t __R31;    //Input register

#define SHARE_MEM 0x00010000
volatile uint32_t *shared = (unsigned int*) SHARE_MEM;

void main(void) {
	// Select which pin to toggle.
	// P1_36 = (1<<0). Moves 1 bit 0 times to the left
	uint32_t gpio = P1_36;

	/* Clear SYSCFG[STANDBY_INIT] to enable OCP master port */
	CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;

	while (1) {
		if (shared[0] == 1) {	//Checks shared memory to see if input changed
			__R30 |= gpio;        //Set the GPIO pin to 1 if input changed
		} else {
			__R30 &= ~gpio;        // Set GPIO to 0
		}
	}
}
