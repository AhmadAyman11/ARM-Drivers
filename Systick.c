#include "Systick.h"


static volatile void (*gPtr2Func)(void) = NULL_PTR;

void SysTick_Init(uint16 a_TimeInMilliSeconds)
{
    SYSTICK_CTRL_REG = 0;
    SYSTICK_RELOAD_REG = (SYSTICK_RELOAD_VALUE * a_TimeInMilliSeconds) - 1;
    SYSTICK_CURRENT_REG = 0;

    SYSTICK_CTRL_REG |= 0x07;
}

void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds)
{
    SYSTICK_CTRL_REG = 0;
    SYSTICK_RELOAD_REG = (SYSTICK_RELOAD_VALUE * a_TimeInMilliSeconds) - 1;
    SYSTICK_CURRENT_REG = 0;

    SYSTICK_CTRL_REG |= 0x05;
    while(BIT_IS_CLEAR(SYSTICK_CTRL_REG, 16));
    SYSTICK_CTRL_REG = 0;
    SYSTICK_CURRENT_REG = 0;
}

void SysTick_Handler(void)
{
    if(gPtr2Func != NULL_PTR)
    {
        (*gPtr2Func)();
    }
}

void SysTick_SetCallBack(volatile void (*Ptr2Func) (void))
{
    gPtr2Func = Ptr2Func;
}

void SysTick_Stop(void)
{
    CLEAR_BIT(SYSTICK_CTRL_REG, 1);
}

void SysTick_Start(void)
{
    SET_BIT(SYSTICK_CTRL_REG, 1);
}

void SysTick_DeInit(void)
{
    SYSTICK_CTRL_REG = 0;
    SYSTICK_RELOAD_REG = 0;
    SYSTICK_CURRENT_REG = 0;
    gPtr2Func = NULL_PTR;
}
