#include "bsp.h"
#include "includes.h"
#include "systick.h"

#define APP_DEBUG_ON
#ifdef  APP_DEBUG_ON
    #define APP_INFO(...) printf(__VA_ARGS__)
#else
    #define APP_INFO(...) do { } while(0)
#endif

void delay()
{
	int i = 0x200000;
	while(i--);
}

int main()
{
	board_console_init();

	while (1)
	{
		APP_INFO("run ...\r\n");
		delay();
	}

}

