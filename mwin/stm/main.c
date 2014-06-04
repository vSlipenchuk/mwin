#define USE_Delay 1
#define delay Delay

#include <stm32f4xx.h>
#include <stm32f4xx_conf.h>

#include <stm32f4xx_rcc.h>
#include <stm32f4xx_gpio.h>
//#define RCC_GPIO RCC_APB2Periph_GPIOB

//#define LED_PORT GPIOB


#include "stm32f4xx.h"
#include <stdio.h>
#include "stm32f4xx_dac.h"


#include "stm32f429i_discovery.h"

// common.c
//#define USE_Delay 1

void Delay(__IO uint32_t nTime);

#include "stm32f429i_discovery.c"
#include "stm32f429i_discovery_lcd.c"
#include "stm32f429i_discovery_sdram.c"

#include "stm32f4xx_dma.c"
#include "stm32f4xx_i2c.c"
#undef CR1_CLEAR_MASK  
#undef FLAG_MASK
#include "stm32f4xx_spi.c"
#undef CR1_CLEAR_MASK  
#undef FLAG_MASK
//#include "stm32f4xx_dma.c"
#include "stm32f4xx_dma2d.c"
#include "stm32f4xx_ltdc.c"
//#include "stm32f4xx_rcc.c"
#include "stm32f4xx_fmc.c"

#include "syscalls.c" // std inclide


#define LED1_PIN GPIO_Pin_5
#define LED2_PIN GPIO_Pin_6
//STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma.c


static __IO uint32_t TimingDelay;
//static void delay(__IO uint32_t nTime);   

void Delay(__IO uint32_t nTime)
{ 
  TimingDelay = nTime;

  while(TimingDelay != 0);
}

//void delay(__IO uint32_t nTime) { Delay(nTime);}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0)
  { 
    TimingDelay--;
  }
}


void Delay2(volatile uint32_t nCount) {
    for (; nCount != 0; nCount--);
}

void SysTick_Handler(void) { // Hanlder
  TimingDelay_Decrement();
}	

void  mwin_init() {
	 LCD_Init();
  
  /* LCD Layer initialization */
  LCD_LayerInit();
    
  /* Enable the LTDC */
  LTDC_Cmd(ENABLE);
	  LCD_SetLayer(LCD_FOREGROUND_LAYER);
	  // TP_Config(); // touch panel
	
  LCD_Clear(LCD_COLOR_WHITE);
	 LCD_SetFont(&Font8x8);
	
	int i=32;
 for(i=0;i<=35;i++) {
	 //static char buf[20];
	   //s/nprintf(buf,sizeof(buf),"Hello Line %d", i);
    LCD_DisplayStringLine(LINE(i), (uint8_t*)"buf");
 }
	
}


int main(void) {
    /* SystemInit() ??? ?????????? ? startup_stm32f10x_md_vl.S */

	  if (SysTick_Config(SystemCoreClock / 1000))
  { 
    /* Capture error */ 
    while (1);
  }

  mwin_init();
	
	  /* Initialize LEDs available on STM32F429I-DISCO */
  STM_EVAL_LEDInit(LED3);
  STM_EVAL_LEDInit(LED4);
	
	 STM_EVAL_LEDOn(LED3);

	while (1)
  {
    /* Toggle LED4 */
    STM_EVAL_LEDToggle(LED4);

    /* Insert 50 ms delay */
    Delay(50);

    /* Toggle LED3 */
    STM_EVAL_LEDToggle(LED3);

    /* Insert 100 ms delay */
    Delay(100);
  }
return 0;

	
	
	/*
	
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_GPIO, ENABLE);

    GPIO_InitStructure.GPIO_Pin = LED1_PIN | LED2_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init( LED_PORT , &GPIO_InitStructure);

    LED_PORT->ODR ^= LED2_PIN;
    while (1) {
        LED_PORT->ODR ^= LED2_PIN;
        LED_PORT->ODR ^= LED1_PIN;
        Delay(0x7FFFF);
    }
    */

    return 0;
}