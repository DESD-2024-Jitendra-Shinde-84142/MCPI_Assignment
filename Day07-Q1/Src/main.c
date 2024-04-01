#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"
#include "uart.h"
#include "switch.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
	char str[16];
	int count = 0;
	SystemInit();
	SwitchInit(SWITCH);
	UartInit(BAUD_9600);
	UartPuts("Counting Start...\r\n");
	while(1) {
		while(exti0_flag == 0)
			;
		count++;
		DelayMs(50);
		sprintf(str,"   %d",count);
		UartPuts(str);
		exti0_flag = 0;
	}
	return 0;
}
