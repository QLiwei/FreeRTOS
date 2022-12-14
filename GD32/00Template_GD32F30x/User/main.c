#include "bsp.h"
#include "includes.h"


#define APP_DEBUG_ON
#ifdef  APP_DEBUG_ON

    #define APP_INFO(...) printf(__VA_ARGS__)
#else
    #define APP_INFO(...) do { } while(0)
#endif


/*
**********************************************************************************************************
函数声明
**********************************************************************************************************
*/
static void vTaskTaskUserIF(void *pvParameters);
static void vTaskLED(void *pvParameters);
static void vTaskMsgPro(void *pvParameters);
static void vTaskStart(void *pvParameters);
static void AppTaskCreate (void);

/*
**********************************************************************************************************
变量声明
**********************************************************************************************************
*/
static TaskHandle_t xHandleTaskUserIF = NULL;
static TaskHandle_t xHandleTaskLED = NULL;
static TaskHandle_t xHandleTaskMsgPro = NULL;
static TaskHandle_t xHandleTaskStart = NULL;

int main()
{
	/*
		在启动调度前，为了防止初始化 STM32 外设时有中断服务程序执行，这里禁止全局中断(除了 NMI 和 HardFault)。
		这样做的好处是：
		1. 防止执行的中断服务程序中有 FreeRTOS 的 API 函数。
		2. 保证系统正常启动，不受别的中断影响。
		3. 关于是否关闭全局中断，大家根据自己的实际情况设置即可。
		在移植文件 port.c 中的函数 prvStartFirstTask 中会重新开启全局中断。通过指令 cpsie i 开启，__set_PRIMASK(1)
		和 cpsie i 是等效的。
	*/
	__set_PRIMASK(1);
	/* 硬件初始化 */
	bsp_Init();
	/* 创建任务 */
	AppTaskCreate();
	/* 启动调度，开始执行任务 */
	vTaskStartScheduler();
	/*
		如果系统正常启动是不会运行到这里的，运行到这里极有可能是用于定时器任务或者空闲任务的
		heap 空间不足造成创建失败，此要加大 FreeRTOSConfig.h 文件中定义的 heap 大小：
		#define configTOTAL_HEAP_SIZE ( ( size_t ) ( 17 * 1024 ) )
	*/
	while(1);
}


/*
*********************************************************************************************************
* 函 数 名: vTaskTaskUserIF
* 功能说明: 接口消息处理，这里用作 LED 闪烁
* 形 参: pvParameters 是在创建该任务时传递的形参
* 返 回 值: 无
* 优 先 级: 1 (数值越小优先级越低，这个跟 uCOS 相反)
*********************************************************************************************************
*/
static void vTaskTaskUserIF(void *pvParameters)
{
	while(1)
	{
		APP_INFO("LED1 flicker\r\n");
		vTaskDelay(100);
	}
}

/*
*********************************************************************************************************
* 函 数 名: vTaskLED
* 功能说明: LED 闪烁
* 形 参: pvParameters 是在创建该任务时传递的形参
* 返 回 值: 无
* 优 先 级: 2
*********************************************************************************************************
*/
static void vTaskLED(void *pvParameters)
{
	while(1)
	{
		APP_INFO("LED2 flicker\r\n");
		vTaskDelay(200);
	}
}

/*
*********************************************************************************************************
* 函 数 名: vTaskMsgPro
* 功能说明: 信息处理，这里是用作 LED 闪烁
* 形 参: pvParameters 是在创建该任务时传递的形参
* 返 回 值: 无
* 优 先 级: 3
*********************************************************************************************************
*/
static void vTaskMsgPro(void *pvParameters)
{
	while(1)
	{
		APP_INFO("LED3 flicker\r\n");
		vTaskDelay(300);
	}
}

/*
*********************************************************************************************************
* 函 数 名: vTaskStart
* 功能说明: 启动任务，也就是最高优先级任务，这里用作 LED 闪烁
* 形 参: pvParameters 是在创建该任务时传递的形参
* 返 回 值: 无
* 优 先 级: 4
*********************************************************************************************************
*/
static void vTaskStart(void *pvParameters)
{
	while(1)
	{
		/* LED 闪烁 */
		APP_INFO("LED4 flicker\r\n");
		vTaskDelay(400);
	}
}

/*
*********************************************************************************************************
* 函 数 名: AppTaskCreate
* 功能说明: 创建应用任务
* 形 参: 无
* 返 回 值: 无
*********************************************************************************************************
*/
static void AppTaskCreate (void)
{
	xTaskCreate( vTaskTaskUserIF, 		/* 任务函数 */
				"vTaskUserIF", 			/* 任务名 */
				512, 					/* 任务栈大小，单位 word，也就是 4 字节 */
				NULL, 					/* 任务参数 */
				1, 						/* 任务优先级*/
				&xHandleTaskUserIF ); 	/* 任务句柄 */

	xTaskCreate( vTaskLED, 				/* 任务函数 */
				"vTaskLED", 			/* 任务名 */
				512, 					/* 任务栈大小，单位 word，也就是 4 字节 */
				NULL,					/* 任务参数 */
				2, 						/* 任务优先级*/
				&xHandleTaskLED ); 		/* 任务句柄 */

	xTaskCreate( vTaskMsgPro, 			/* 任务函数 */
				"vTaskMsgPro", 			/* 任务名 */
				512, 					/* 任务栈大小，单位 word，也就是 4 字节 */
				NULL, 					/* 任务参数 */
				3, 						/* 任务优先级*/
				&xHandleTaskMsgPro ); 	/* 任务句柄 */

	xTaskCreate( vTaskStart, 			/* 任务函数 */
				"vTaskStart", 			/* 任务名 */
				512, 					/* 任务栈大小，单位 word，也就是 4 字节 */
				NULL, 					/* 任务参数 */
				4, 						/* 任务优先级*/
				&xHandleTaskStart ); 	/* 任务句柄 */
}

