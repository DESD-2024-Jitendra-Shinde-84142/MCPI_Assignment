#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"

#include "led.h"
#include "switch.h"
#include "lcd.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
	SystemInit();
	LedInit(LED_RED);
	SwitchInit(SWITCH);
	int count = 0;
	char strlcd[25];

	while(1)
	{
		while(exti0_flag == 0)
			;
		LedBlink(LED_RED, 1000);

		count++;
		LcdInit();
		sprintf(strlcd,"Count = %d",count);
		LcdPuts(LCD_LINE1, "ASSIGNMENT");
		LcdPuts(LCD_LINE2, strlcd);

		exti0_flag = 0;
	}
	return 0;
}
