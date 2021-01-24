/* INCLUDE */
#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "sleep.h"

/* MAIN CODE */
int main(void)
{
    uint32_t *led = (uint32_t *)0x41200000;
	uint32_t *btn = (uint32_t *)0x41210000;

	init_platform();

    print("Hello World\n\r");

    while (1) {
    	if (*btn & 0x1) {
        	*led |= 0x1;
    	}

    	else {
    		*led &= ~0x1;
    	}
    }

    cleanup_platform();
    return 0;
}
