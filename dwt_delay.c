#include "stm32f4xx_hal.h"
#include "dwt_delay.h"

void DWT_Init(void)
{
	/* Enable TRC */
	CoreDebug->DEMCR &= ~0x01000000;
	CoreDebug->DEMCR |=  0x01000000;

	/* Enable counter */
	DWT->CTRL &= ~0x00000001;
	DWT->CTRL |=  0x00000001;

	/* Reset counter */
	DWT->CYCCNT = 0;

	/* 2 dummys */
	__ASM volatile ("NOP");
	__ASM volatile ("NOP");
}

uint32_t DWT_Get(void)
{
  return DWT->CYCCNT;
}

void DWT_Delay(uint32_t micros)
{
	uint32_t start = DWT->CYCCNT;

	/* Go to number of cycles for system */
	micros *= (HAL_RCC_GetHCLKFreq() / 1000000);

	/* Delay till end */
	while ((DWT->CYCCNT - start) < micros);
}
