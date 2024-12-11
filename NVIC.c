#include "NVIC.h"


volatile uint32 *NVIC_PRI_REGS[] =
{
 &NVIC_PRI0_REG, &NVIC_PRI1_REG, &NVIC_PRI2_REG, &NVIC_PRI3_REG,
 &NVIC_PRI4_REG, &NVIC_PRI5_REG, &NVIC_PRI6_REG, &NVIC_PRI7_REG,
 &NVIC_PRI8_REG, &NVIC_PRI9_REG, &NVIC_PRI10_REG, &NVIC_PRI11_REG,
 &NVIC_PRI12_REG, &NVIC_PRI13_REG, &NVIC_PRI14_REG, &NVIC_PRI15_REG,
 &NVIC_PRI16_REG, &NVIC_PRI17_REG, &NVIC_PRI18_REG, &NVIC_PRI19_REG,
 &NVIC_PRI20_REG, &NVIC_PRI21_REG, &NVIC_PRI22_REG, &NVIC_PRI23_REG,
 &NVIC_PRI24_REG, &NVIC_PRI25_REG, &NVIC_PRI26_REG, &NVIC_PRI27_REG,
 &NVIC_PRI28_REG, &NVIC_PRI29_REG, &NVIC_PRI30_REG, &NVIC_PRI31_REG,
 &NVIC_PRI32_REG, &NVIC_PRI33_REG, &NVIC_PRI34_REG
};

void NVIC_EnableIRQ(NVIC_IRQType IRQ_Num)
{
    uint8 Reg_offset = IRQ_Num / 32;
    uint8 Bit_offset = IRQ_Num % 32;

    if (Reg_offset == 0)
    {
        SET_BIT(NVIC_EN0_REG, Bit_offset);
    }
    else if (Reg_offset == 1)
    {
        SET_BIT(NVIC_EN1_REG, Bit_offset);
    }
    else if (Reg_offset == 2)
    {
        SET_BIT(NVIC_EN2_REG, Bit_offset);
    }
    else if (Reg_offset == 3)
    {
        SET_BIT(NVIC_EN3_REG, Bit_offset);
    }
    else if (Reg_offset == 4)
    {
        SET_BIT(NVIC_EN4_REG, Bit_offset);
    }
}

void NVIC_DisableIRQ(NVIC_IRQType IRQ_Num)
{
    uint8 Reg_offset = IRQ_Num / 32;
    uint8 Bit_offset = IRQ_Num % 32;

    if (Reg_offset == 0)
    {
        SET_BIT(NVIC_DIS0_REG, Bit_offset);
    }
    else if (Reg_offset == 1)
    {
        SET_BIT(NVIC_DIS1_REG, Bit_offset);
    }
    else if (Reg_offset == 2)
    {
        SET_BIT(NVIC_DIS2_REG, Bit_offset);
    }
    else if (Reg_offset == 3)
    {
        SET_BIT(NVIC_DIS3_REG, Bit_offset);
    }
    else if (Reg_offset == 4)
    {
        SET_BIT(NVIC_DIS4_REG, Bit_offset);
    }
}

void NVIC_SetPriorityIRQ(NVIC_IRQType IRQ_Num, NVIC_IRQPriorityType IRQ_Priority)
{
    uint8 PRI_Index = IRQ_Num / 4;
    uint8 PRIORITY_BITS_POS  = (IRQ_Num % 4) * 8 + 5;
    uint32 PRIORITY_MASK = ~(0x7 << PRIORITY_BITS_POS);

    *NVIC_PRI_REGS[PRI_Index] = (*NVIC_PRI_REGS[PRI_Index] & PRIORITY_MASK) | (IRQ_Priority << PRIORITY_BITS_POS);
}

void NVIC_EnableException(NVIC_ExceptionType Exception_Num)
{
    if (Exception_Num == EXCEPTION_MEM_FAULT_TYPE)
    {
        SET_BIT(NVIC_SYSTEM_SYSHNDCTRL, MEM_MANAGE_FAULT_ENABLE_BIT_POS);
    }
    else if (Exception_Num == EXCEPTION_BUS_FAULT_TYPE)
    {
        SET_BIT(NVIC_SYSTEM_SYSHNDCTRL, BUS_FAULT_ENABLE_BIT_POS);
    }
    else if (Exception_Num == EXCEPTION_USAGE_FAULT_TYPE)
    {
        SET_BIT(NVIC_SYSTEM_SYSHNDCTRL, USAGE_FAULT_ENABLE_BIT_POS);
    }
    else
    {
        Enable_Faults();
        Enable_Exceptions();
    }
}

void NVIC_DisableException(NVIC_ExceptionType Exception_Num)
{
    if (Exception_Num == EXCEPTION_MEM_FAULT_TYPE)
    {
        CLEAR_BIT(NVIC_SYSTEM_SYSHNDCTRL, MEM_MANAGE_FAULT_ENABLE_BIT_POS);
    }
    else if (Exception_Num == EXCEPTION_BUS_FAULT_TYPE)
    {
        CLEAR_BIT(NVIC_SYSTEM_SYSHNDCTRL, BUS_FAULT_ENABLE_BIT_POS);
    }
    else if (Exception_Num == EXCEPTION_USAGE_FAULT_TYPE)
    {
        CLEAR_BIT(NVIC_SYSTEM_SYSHNDCTRL, USAGE_FAULT_ENABLE_BIT_POS );
    }
    else
    {
        Disable_Faults();
        Disable_Exceptions();
    }
}

void NVIC_SetPriorityException(NVIC_ExceptionType Exception_Num, NVIC_ExceptionPriorityType Exception_Priority)
{
    if (Exception_Num == EXCEPTION_MEM_FAULT_TYPE)
    {
        NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG & MEM_FAULT_PRIORITY_MASK ) | (Exception_Priority << MEM_FAULT_PRIORITY_BITS_POS);
    }
    else if (Exception_Num == EXCEPTION_BUS_FAULT_TYPE)
    {
        NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG & BUS_FAULT_PRIORITY_MASK) | (Exception_Priority << BUS_FAULT_PRIORITY_BITS_POS);
    }
    else if (Exception_Num == EXCEPTION_USAGE_FAULT_TYPE)
    {
        NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG & USAGE_FAULT_PRIORITY_MASK) | (Exception_Priority << USAGE_FAULT_PRIORITY_BITS_POS);
    }
    else if (Exception_Num == EXCEPTION_SVC_TYPE)
    {
        NVIC_SYSTEM_PRI2_REG = (NVIC_SYSTEM_PRI2_REG & SVC_PRIORITY_MASK) | (Exception_Priority << SVC_PRIORITY_BITS_POS);
    }
    else if (Exception_Num == EXCEPTION_DEBUG_MONITOR_TYPE)
    {
        NVIC_SYSTEM_PRI3_REG =(NVIC_SYSTEM_PRI3_REG & DEBUG_MONITOR_PRIORITY_MASK) | (Exception_Priority<< DEBUG_MONITOR_PRIORITY_BITS_POS);
    }
    else if (Exception_Num == EXCEPTION_PEND_SV_TYPE)
    {
        NVIC_SYSTEM_PRI3_REG =  (NVIC_SYSTEM_PRI3_REG & PENDSV_PRIORITY_MASK) | (Exception_Priority << PENDSV_PRIORITY_BITS_POS);
    }
    else if (Exception_Num == EXCEPTION_SYSTICK_TYPE)
    {
        NVIC_SYSTEM_PRI3_REG =  (NVIC_SYSTEM_PRI3_REG & SYSTICK_PRIORITY_MASK) | (Exception_Priority << SYSTICK_PRIORITY_BITS_POS);
    }
}



