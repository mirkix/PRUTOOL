#include <stdint.h>

volatile register uint32_t __R30;
volatile register uint32_t __R31;

main()
{
	__R30 = 0;

	while(1)
	{
		__R30 = 1;
		__delay_cycles(100000000);
		__R30 = 0;
		__delay_cycles(100000000);
	}

}

