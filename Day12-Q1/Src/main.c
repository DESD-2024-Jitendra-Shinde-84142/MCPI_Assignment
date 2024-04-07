#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"
#include "adc.h"
#include "i2c_lcd.h"
#include "switch.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
	char str[32];
	uint16_t val;
	SystemInit();
	ADC_Init();
	SwitchInit(SWITCH);
	LcdInit();
	LcdWrite(LCD_CMD, LCD_CLEAR);
	LcdPuts(LCD_LINE1, "ADC LDR OUTPUT!");

	while(1) {
		while(exti0_flag == 0)
		    ;
		val = ADC_GetValue();
		LcdWrite(LCD_CMD, LCD_CLEAR);
		sprintf(str, "Conversion= %d", val);
		LcdPuts(LCD_LINE1, "ADC LDR OUTPUT!");
		LcdPuts(LCD_LINE2, str);
		DelayMs(500);
		exti0_flag = 0;
	}
	return 0;
}
