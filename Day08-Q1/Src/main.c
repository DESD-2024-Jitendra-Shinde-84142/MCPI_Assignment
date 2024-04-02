#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"
#include "eeprom.h"
#include "uart.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
	int choice;
	char str[32];
	SystemInit();
	EEPROM_Init();
	UartInit(BAUD_9600);

	do {
		UartPuts("Enter Your Choice..\r\n");
		UartPuts("1. Write a string into EEPROM\r\n");
		UartPuts("2. Read a string from EEPROM\r\n");

		UartGets(str);

		sscanf(str,"%d", &choice);

		switch(choice)
		{
			case 1:
				UartGets(str);
				EEPROM_Write(0x0020,(uint8_t*)str, 16);
				break;
			case 2:
				EEPROM_Read(0x0020, (uint8_t*)str, 16);
				UartPuts(str);

				break;
		}
		}while(choice != 0);

	return 0;
}
