#include <stdint.h>
#include <pru_cfg.h>
#include "resource_table_empty.h"
#include "prugpio.h"


volatile register uint32_t __R30; // output
volatile register uint32_t __R31; // input


#define SHARED_MEM   0x00010000
volatile unsigned int *shared = (unsigned int *) (SHARED_MEM);

#define MASK(x) (1UL << (x))
#define gpio_pos 10

void main(void)
{
    /* Clear SYSCFG[STANDBY_INIT] to enable OCP master port */
    CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;




    while (1)
    {
        shared[0] = __R31 & MASK(gpio_pos);
    }
}


