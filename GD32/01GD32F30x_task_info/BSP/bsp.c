#include "bsp.h"


void bsp_Init(void)
{
    /* debug usart init */
    board_console_init();
<<<<<<< HEAD
=======
	
	/* key init */
	bsp_InitKey();
>>>>>>> 4defe80 ([add] FreeRTOS 任务执行情况)
}

