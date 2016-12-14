/******************************************************************************
 *
 * @brief     This file is part of the TouchGFX 4.5.0 evaluation distribution.
 *
 * @author    Draupner Graphics A/S <http://www.touchgfx.com>
 *
 ******************************************************************************
 *
 * @section Copyright
 *
 * This file is free software and is provided for example purposes. You may
 * use, copy, and modify within the terms and conditions of the license
 * agreement.
 *
 * This is licensed software for evaluation use, any use must strictly comply
 * with the evaluation license agreement provided with delivery of the
 * TouchGFX software.
 *
 * The evaluation license agreement can be seen on www.touchgfx.com
 *
 * @section Disclaimer
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Draupner Graphics A/S has
 * no obligation to support this software. Draupner Graphics A/S is providing
 * the software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Draupner Graphics A/S can not be held liable for any consequential,
 * incidental, or special damages, or any other relief, or for any claim by
 * any third party, arising from your use of this software.
 *
 *****************************************************************************/
#include "isr.h"

extern int main(void);
extern int SystemInit(void);

extern unsigned long _etext;
extern unsigned long __data_start;
extern unsigned long _edata;
extern unsigned long __bss_start__;
extern unsigned long __bss_end__;
extern unsigned long __stack_end__;
extern unsigned long __valid_user_code_checksum;
/*
int _sbrk_r (struct _reent *r, int incr)
{
    return 0;
}
*/

__attribute__ ((section(".isr_vectors"), used))
void (* const g_pfnVectors[])(void) = {
    (void (*)(void))((unsigned long)&__stack_end__),
    ResetISR,
    NMI_Handler,
    HardFault_Handler,
    MemManage_Handler,
    BusFault_Handler,
    UsageFault_Handler,
    (void (*)(void))((unsigned long)&__valid_user_code_checksum),
    0,
    0,
    0,
    SVC_Handler,
    DebugMon_Handler,
    0,
    PendSV_Handler,
    SysTick_Handler,
    WDT_IRQHandler,    // 16 D/A Converter
    TIMER0_IRQHandler,            // 17 Event Router
    TIMER1_IRQHandler,    // 18 General Purpose DMA
    TIMER2_IRQHandler,                // 19 Reserved
    TIMER3_IRQHandler,                // 20 Reserved
    MyUART0_IRQHandler,    // 21 Ethernet
    UART1_IRQHandler,    // 22 SD/MMC
    UART2_IRQHandler,    // 23 LCD
    UART3_IRQHandler,    // 24 USB0
    PWM1_IRQHandler,    // 25 USB1
    I2C0_IRQHandler,     // 26 State Configurable Timer
    I2C1_IRQHandler,     // 27 Repetitive Interrupt Timer
    I2C2_IRQHandler,    // 28 Timer0
    SPIFI_IRQHandler,    // 29 Timer1
    SSP0_IRQHandler,    // 30 Timer2
    SSP1_IRQHandler,    // 31 Timer3
    PLL0_IRQHandler,    // 32 Motor Control PWM
    RTC_IRQHandler,    // 33 A/D Converter 0
    EINT0_IRQHandler,    // 34 I2C0
    EINT1_IRQHandler,    // 35 I2C1
    EINT2_IRQHandler,            // 36 Reserved
    EINT3_IRQHandler,    // 37 A/D Converter 1
    ADC_IRQHandler,    // 38 SSP0
    BOD_IRQHandler,    // 39 SSP1
    USB_IRQHandler,   // 40 UART0
    CAN_IRQHandler,    // 41 UART1
    GPDMA_IRQHandler,    // 42 UART2
    I2S_IRQHandler,    // 43 UART3
    ENET_IRQHandler,    // 44 I2S0
    MCI_IRQHandler,    // 45 I2S1
    MCPWM_IRQHandler,   // 46 SPI Flash Interface
    QEI_IRQHandler,    // 47 SGPIO
    PLL1_IRQHandler,    // 48 GPIO0
    USBACT_IRQHandler,    // 49 GPIO1
    CANACT_IRQHandler,    // 50 GPIO2
    UART4_IRQHandler,    // 51 GPIO3
    SSP2_IRQHandler,    // 52 GPIO4
    LCD_IRQHandler,    // 53 GPIO5
    MyGPIO_IRQHandler,    // 54 GPIO6
    PWM0_IRQHandler,    // 55 GPIO7
    KFLASH_IRQHandler,    // 56 GINT0 /* LAST */
    GINT1_IRQHandler,    // 57 GINT1
    EVRT_IRQHandler,    // 58 Event Router
    CAN1_IRQHandler,    // 59 C_CAN1
    0,            // 60 Reserved
    0,              // 61 VADC
    ATIMER_IRQHandler,    // 62 ATIMER
    RTC_IRQHandler,    // 63 RTC
    0,            // 64 Reserved
    WDT_IRQHandler,    // 65 WDT
    0,               // 66 M0s
    CAN0_IRQHandler,    // 67 C_CAN0
    QEI_IRQHandler    // 68 QEI
};

extern void (*__init_array_start []) (void) __attribute__((weak));
extern void (*__init_array_end []) (void) __attribute__((weak));

void ResetISR(void)
{
    unsigned long *src, *dst;
    
    int count;
    int i;

    
    src = &_etext;
    for(dst = &__data_start; dst < &_edata; ) {
        *dst++ = *src++;
    }

    for(dst = &__bss_start__; dst < &__bss_end__; ) {
        *dst++ = 0;
    }
    
    count = __init_array_end - __init_array_start;
    for (i = 0; i < count; i++)
        __init_array_start[i] ();
    
    unsigned int * pSCB_VTOR = (unsigned int *) 0xE000ED08;
    if ((unsigned int *)g_pfnVectors!=(unsigned int *) 0x00000000) {
        // CMSIS : SCB->VTOR = <address of vector table>
        *pSCB_VTOR = (unsigned int)g_pfnVectors;
    }

    SystemInit();
    main();
}

void NMI_Handler(void) 
{
  while(1);
}

void HardFault_Handler(void) 
{
  while(1);
}

void MemManage_Handler(void) 
{
  while(1);
}

void BusFault_Handler(void) 
{
  while(1);
}

void UsageFault_Handler(void) 
{
  while(1);
}

void DebugMon_Handler(void) 
{
  while(1);
}

void DAC_IRQHandler(void) 
{

}

void ETH_IRQHandler(void) 
{

}

void MyUART0_IRQHandler(void) 
{

}

void SDIO_IRQHandler(void) 
{

}

void USB0_IRQHandler(void) 
{

}

void USB1_IRQHandler(void) 
{

}

void SCT_IRQHandler(void) 
{

}

void RIT_IRQHandler(void) 
{

}

void TIMER0_IRQHandler(void) 
{

}

void TIMER1_IRQHandler(void) 
{

}

void TIMER2_IRQHandler(void) 
{

}

void TIMER3_IRQHandler(void) 
{

}

void MCPWM_IRQHandler(void) 
{

}

void ADC0_IRQHandler(void) 
{

}

void I2C0_IRQHandler(void) 
{

}

void I2C1_IRQHandler(void) 
{

}

void ADC1_IRQHandler(void) 
{

}

void SSP0_IRQHandler(void) 
{

}

void SSP1_IRQHandler(void) 
{

}

void UART0_IRQHandler(void) 
{

}

void UART1_IRQHandler(void) 
{

}

void UART2_IRQHandler(void) 
{

}

void UART3_IRQHandler(void) 
{

}

void I2S0_IRQHandler(void) 
{

}

void I2S1_IRQHandler(void) 
{

}

void SPIFI_IRQHandler(void) 
{

}

void SGPIO_IRQHandler(void) 
{

}

void GPIO0_IRQHandler(void) 
{

}

void GPIO1_IRQHandler(void) 
{

}

void GPIO2_IRQHandler(void) 
{

}

void GPIO3_IRQHandler(void) 
{

}

void GPIO4_IRQHandler(void) 
{

}

void GPIO5_IRQHandler(void) 
{

}

void GPIO6_IRQHandler(void) 
{

}

void GPIO7_IRQHandler(void) 
{

}

void GINT0_IRQHandler(void) 
{

}

void GINT1_IRQHandler(void) 
{

}

void EVRT_IRQHandler(void) 
{

}

void CAN1_IRQHandler(void) 
{

}

void ATIMER_IRQHandler(void) 
{

}

void RTC_IRQHandler(void) 
{

}

void WDT_IRQHandler(void) 
{

}

void CAN0_IRQHandler(void) 
{

}

void QEI_IRQHandler(void) 
{

}

void PWM1_IRQHandler(void) 
{

}

void I2C2_IRQHandler(void) 
{

}

void PLL0_IRQHandler(void) 
{

}

void EINT0_IRQHandler(void) 
{

}

void EINT1_IRQHandler(void) 
{

}

void EINT2_IRQHandler(void) 
{

}

void EINT3_IRQHandler(void) 
{

}

void ADC_IRQHandler(void) 
{

}

void BOD_IRQHandler(void) 
{

}

void CAN_IRQHandler(void) 
{

}

void I2S_IRQHandler(void) 
{

}

void ENET_IRQHandler(void) 
{

}

void PLL1_IRQHandler(void) 
{

}

void USBACT_IRQHandler(void) 
{

}

void CANACT_IRQHandler(void) 
{

}

void UART4_IRQHandler(void) 
{

}

void SSP2_IRQHandler(void) 
{

}

void MyGPIO_IRQHandler(void) 
{

}

void PWM0_IRQHandler(void) 
{

}


void KFLASH_IRQHandler(void) 
{

}