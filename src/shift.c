/*
 * shift.c
 *
 *  Created on: Apr 19, 2013
 *      Author: Timotet
 */

#include "spi.h"
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "Delay.h"
#include "shift.h"
#include "integer.h"

void s595_Put(UINT data) {

	STM_EVAL_LEDOn(LED6);
	//s595_Latch_LO;                //s595_Latch low  active low

	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET)
		;
	// make sure the transmit buffer is free
	SPI_I2S_SendData(SPI2, data); // shift out 16 bits
	// we are not reading data so be sure that the character goes to the shift register
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET)
		;
	// and then be sure it has been sent over the wire
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) == SET)
		;
	STM_EVAL_LEDOff(LED6);
	s595_Latch_HI;                //s595_Latch high  latch the data
	s595_Latch_LO;                //s595_Latch_low

	Delay(1);
	//DelayUs(500);
}

void clearShift(void){

	s595_Put(0x0000);

}

