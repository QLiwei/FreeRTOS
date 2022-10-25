#include "bsp.h"


void bsp_Init(void)
{
    /* debug usart init */
    board_console_init();
	/* key init */
	bsp_InitKey();
}

