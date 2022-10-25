#include "bsp.h"


/* 定时器频率，50us一次中断 */
#define  timerINTERRUPT_FREQUENCY	20000

/* 中断优先级 */
#define  timerHIGHEST_PRIORITY		1

/* 被系统调用 */
volatile uint32_t ulHighFrequencyTimerTicks = 0UL;

void timer6_init(void)
{
    /* TIMER6CLK = SystemCoreClock / 120 = 1MHz */
    timer_parameter_struct timer_initpara;
    rcu_periph_clock_enable(RCU_TIMER6);

    timer_deinit(TIMER6);
    timer_initpara.prescaler = 59U;
    timer_initpara.alignedmode = TIMER_COUNTER_CENTER_UP;
    timer_initpara.counterdirection = TIMER_COUNTER_UP;
    timer_initpara.clockdivision = TIMER_CKDIV_DIV1;
    timer_initpara.period = 50U;
    timer_initpara.repetitioncounter = 0U;

    timer_init(TIMER6, &timer_initpara);

    nvic_priority_group_set(NVIC_PRIGROUP_PRE2_SUB2);
    nvic_irq_enable(TIMER6_IRQn,0,1);

    /* auto-reload preload enable */
    timer_auto_reload_shadow_enable(TIMER6);
    timer_interrupt_flag_clear(TIMER6, TIMER_INT_FLAG_UP);
    timer_interrupt_enable(TIMER6, TIMER_INT_UP);
    timer_enable(TIMER6);
}

/*
*********************************************************************************************************
*	函 数 名: vSetupTimerTest
*	功能说明: 创建定时器
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void vSetupSysInfoTest(void)
{
	timer6_init();
}

/*
*********************************************************************************************************
*	函 数 名: TIM6_IRQHandler
*	功能说明: TIM6中断服务程序。
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void TIMER6_IRQHandler( void )
{
	if(timer_interrupt_flag_get(TIMER6, TIMER_INT_FLAG_UP) != RESET)
	{
		ulHighFrequencyTimerTicks++;
		timer_interrupt_flag_clear(TIMER6, TIMER_INT_FLAG_UP);
	}
}

