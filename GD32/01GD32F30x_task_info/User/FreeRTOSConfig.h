/*
    FreeRTOS V8.2.3 - Copyright (C) 2015 Real Time Engineers Ltd.
    All rights reserved

    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation >>>> AND MODIFIED BY <<<< the FreeRTOS exception.

    ***************************************************************************
    >>!   NOTE: The modification to the GPL is included to allow you to     !<<
    >>!   distribute a combined work that includes FreeRTOS without being   !<<
    >>!   obliged to provide the source code for proprietary components     !<<
    >>!   outside of the FreeRTOS kernel.                                   !<<
    ***************************************************************************

    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  Full license text is available on the following
    link: http://www.freertos.org/a00114.html

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS provides completely free yet professionally developed,    *
     *    robust, strictly quality controlled, supported, and cross          *
     *    platform software that is more than just the market leader, it     *
     *    is the industry's de facto standard.                               *
     *                                                                       *
     *    Help yourself get started quickly while simultaneously helping     *
     *    to support the FreeRTOS project by purchasing a FreeRTOS           *
     *    tutorial book, reference manual, or both:                          *
     *    http://www.FreeRTOS.org/Documentation                              *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org/FAQHelp.html - Having a problem?  Start by reading
    the FAQ page "My application does not run, what could be wrong?".  Have you
    defined configASSERT()?

    http://www.FreeRTOS.org/support - In return for receiving this top quality
    embedded software for free we request you assist our global community by
    participating in the support forum.

    http://www.FreeRTOS.org/training - Investing in training allows your team to
    be as productive as possible as early as possible.  Now you can receive
    FreeRTOS training directly from Richard Barry, CEO of Real Time Engineers
    Ltd, and the world's leading authority on the world's leading RTOS.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool, a DOS
    compatible FAT file system, and our tiny thread aware UDP/IP stack.

    http://www.FreeRTOS.org/labs - Where new FreeRTOS products go to incubate.
    Come and try FreeRTOS+TCP, our new open source TCP/IP stack for FreeRTOS.

    http://www.OpenRTOS.com - Real Time Engineers ltd. license FreeRTOS to High
    Integrity Systems ltd. to sell under the OpenRTOS brand.  Low cost OpenRTOS
    licenses offer ticketed support, indemnification and commercial middleware.

    http://www.SafeRTOS.com - High Integrity Systems also provide a safety
    engineered and independently SIL3 certified version for use in safety and
    mission critical applications that require provable dependability.

    1 tab == 4 spaces!
*/


#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H


/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html.
 *----------------------------------------------------------*/

extern uint32_t SystemCoreClock;

/* 抢占式调度器:1  合作式调度器:0 */
#define configUSE_PREEMPTION					1
/*
优化优先级列表中要执行的最高优先级任务的算法。
通用方式---配置为 0：
    所有平台的移植文件都可以配置为 0，因为这是通用方式。
    纯 C 编写，比专用方式效率低。
    可用的优先级数量不限制。
专用方式---配置为 1：
    部分平台支持。
    这些平台架构有专用的汇编指令，比如 CLZ（Count Leading Zeros）指令，通过这些指令可以加快算法执行速度。
    比通用方式高效。
    有最大优先级数限制，通常限制为 32 个。
*/
#define configUSE_PORT_OPTIMISED_TASK_SELECTION	1
/* 使能空闲任务的钩子函数 */
#define configUSE_IDLE_HOOK						0
/* 使能滴答定时器中断里面执行的钩子函数*/
#define configUSE_TICK_HOOK						0
/* CPU 的主频，单位 Hz */
#define configCPU_CLOCK_HZ						( SystemCoreClock )
/* 义系统时钟节拍数，单位 Hz，一般取 1000Hz 即可 */
#define configTICK_RATE_HZ						( 1000 )
/* 定义可供用户使用的最大优先级数 */
#define configMAX_PRIORITIES					( 5 )
/* 定义空闲任务的栈空间大小，单位字，即 4 字节。*/
#define configMINIMAL_STACK_SIZE				( ( unsigned short ) 120 )
/* 定义堆大小，FreeRTOS 内核，用户动态内存申请，任务栈，任务创建，信号量创建，消息队列创建等都需要用这个空间 */
#define configTOTAL_HEAP_SIZE					( ( size_t ) ( 47 * 1024 ) )
/* 定义任务名最大的字符数，末尾的结束符 '\0'也要计算在内。 */
#define configMAX_TASK_NAME_LEN					( 10 )

/* 系统时钟节拍计数使用 TickType_t 数据类型定义的 */
#define configUSE_16_BIT_TICKS					0
/*
  使能与空闲任务同优先级的任务
    满足以下两个条件时，此参数才有效果
        1.使能抢占式调度器。
        2.有创建与空闲任务同优先级的任务。
        配置为 1，就可以使能此特性了，实际应用中不建议用户使用此功能，将其配置为 0 即可。
*/
#define configIDLE_SHOULD_YIELD					1

/* The full demo always has tasks to run so the tick will never be turned off.
The blinky demo will use the default tickless idle implementation to turn the
tick off. */
/* 使能 tickless 低功耗模式 */
#define configUSE_TICKLESS_IDLE					1


/* 使能消息队列。*/
#define configUSE_QUEUE_SETS					1


/* Ensure stdint is only used by the compiler, and not the assembler. */
#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)
#include <stdint.h>
extern volatile uint32_t ulHighFrequencyTimerTicks;
#endif

/* Run time and task stats gathering related definitions. */
#define configGENERATE_RUN_TIME_STATS 1
#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS() (ulHighFrequencyTimerTicks = 0ul)
#define portGET_RUN_TIME_COUNTER_VALUE() ulHighFrequencyTimerTicks

/*  使能此配置将添加额外的结构体成员和函数，以此来协助可视化和跟踪，
    在使用 IAR 中的 FreeRTOS插件时要使能这个配置，否则无法显示任务栈的使用情况。
*/
#define configUSE_TRACE_FACILITY				1
/* This demo makes use of one or more example stats formatting functions.  These
format the raw data provided by the uxTaskGetSystemState() function in to human
readable ASCII form.  See the notes in the implementation of vTaskList() within
FreeRTOS/Source/tasks.c for limitations. */
#define configUSE_STATS_FORMATTING_FUNCTIONS	1

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES 			0
#define configMAX_CO_ROUTINE_PRIORITIES ( 2 )

/* Software timer definitions. */
#define configUSE_TIMERS				1
#define configTIMER_TASK_PRIORITY		( 2 )
#define configTIMER_QUEUE_LENGTH		5
#define configTIMER_TASK_STACK_DEPTH	( configMINIMAL_STACK_SIZE )

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */
#define INCLUDE_vTaskPrioritySet		1
#define INCLUDE_uxTaskPriorityGet		1
#define INCLUDE_vTaskDelete				1
#define INCLUDE_vTaskCleanUpResources	1
#define INCLUDE_vTaskSuspend			1
#define INCLUDE_vTaskDelayUntil			1
#define INCLUDE_vTaskDelay				1
#define INCLUDE_eTaskGetState			1
#define INCLUDE_xTimerPendFunctionCall	1

/* Cortex-M specific definitions. */
#ifdef __NVIC_PRIO_BITS
	/* __BVIC_PRIO_BITS will be specified when CMSIS is being used. */
	#define configPRIO_BITS       		__NVIC_PRIO_BITS
#else
	#define configPRIO_BITS       		4        /* 15 priority levels */
#endif

/* The lowest interrupt priority that can be used in a call to a "set priority"
function. */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY			0xf

/* The highest interrupt priority that can be used by any interrupt service
routine that makes calls to interrupt safe FreeRTOS API functions.  DO NOT CALL
INTERRUPT SAFE FREERTOS API FUNCTIONS FROM ANY INTERRUPT THAT HAS A HIGHER
PRIORITY THAN THIS! (higher priorities are lower numeric values. */
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY	5

/* Interrupt priorities used by the kernel port layer itself.  These are generic
to all Cortex-M ports, and do not rely on any particular library functions. */
#define configKERNEL_INTERRUPT_PRIORITY 		( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
/* !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

/* Normal assert() semantics without relying on the provision of an assert.h
header file. */
#define configASSERT( x ) if( ( x ) == 0 ) { taskDISABLE_INTERRUPTS(); for( ;; ); }

/* Definitions that map the FreeRTOS port interrupt handlers to their CMSIS
standard names. */
#define xPortPendSVHandler PendSV_Handler
#define vPortSVCHandler SVC_Handler
#define xPortSysTickHandler SysTick_Handler

#endif /* FREERTOS_CONFIG_H */

