/*
 * spi.c
 *
 *   set up for 1 way tx spi to talk to 74hc595 shift register
 *
 *  Created on: Apr 19, 2013
 *      Author: Timotet
 */

#include "spi.h"
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "shift.h"
#include "integer.h"


// Private typedef -----------------------------------------------------------
SPI_InitTypeDef SPI_InitStructure;
NVIC_InitTypeDef NVIC_InitStructure;
DMA_InitTypeDef DMA_InitStructure;
GPIO_InitTypeDef GPIO_InitStructure;

// Set up SPI2 peripheral
void SPI_Config(void)
{
	// enable SPI peripheral clock
	//SPI2_CLK_CMD (SPI2_CLK , ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

	// enable the peripheral GPIO port clocks
	RCC_AHB1PeriphClockCmd(SPI2_SCK_GPIO_CLK | SPI2_MOSI_GPIO_CLK, ENABLE);

	// Connect GPIO pins for SPI as alternate function - see section 3, Table 6 in the device data sheet
	GPIO_PinAFConfig(SPI2_SCK_GPIO_PORT, SPI2_SCK_SOURCE, SPI2_SCK_AF);
	GPIO_PinAFConfig(SPI2_MOSI_GPIO_PORT, SPI2_MOSI_SOURCE, SPI2_MOSI_AF);
	GPIO_PinAFConfig(SPI2_MISO_GPIO_PORT, SPI2_MISO_SOURCE, SPI2_MISO_AF);
	//GPIO_PinAFConfig(SPI2_NSS_GPIO_PORT, SPI2_NSS_SOURCE, SPI2_NSS_AF);

	// now configure the pins themselves
	// they are all going to be fast push-pull outputs
	// but the SPI pins use the alternate function
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

	// SPI SCK pin configuration
	GPIO_InitStructure.GPIO_Pin = SPI2_SCK_PIN;
	GPIO_Init(SPI2_SCK_GPIO_PORT, &GPIO_InitStructure);

	// SPI  MOSI pin configuration
	GPIO_InitStructure.GPIO_Pin = SPI2_MOSI_PIN;
	GPIO_Init(SPI2_MOSI_GPIO_PORT, &GPIO_InitStructure);

	// SPI MISO pin configuration
	GPIO_InitStructure.GPIO_Pin = SPI2_MISO_PIN;
	GPIO_Init(SPI2_MISO_GPIO_PORT, &GPIO_InitStructure);

	// Set up the SPI peripheral
	SPI_I2S_DeInit(SPI2);
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
	SPI_Init(SPI2, &SPI_InitStructure);

	//Enable the SPI port
	SPI_Cmd(SPI2, ENABLE);

}



/*

	// interrupt method
	// Configure the Priority Group to 1 bit
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	//Configure the SPI interrupt priority
	NVIC_InitStructure.NVIC_IRQChannel = SPI2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; // configure interrupt to lowest priority
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	//set up SPI interrupt to flag when TX buffer is empty
	SPI_I2S_ITConfig(SPI2,SPI_I2S_IT_TXE,ENABLE);

	//DMA method
	RCC_AHB1PeriphClockCmd(SPI_PORT_DMAx_CLK, ENABLE);
	// start with a blank DMA configuration just to be sure
	DMA_DeInit(SPI_PORT_TX_DMA_STREAM);

	    //Check if the DMA Stream is disabled before enabling it.
	    //Note that this step is useful when the same Stream is used multiple times:
	    //enabled, then disabled then re-enabled... In this case, the DMA Stream disable
	    //will be effective only at the end of the ongoing data transfer and it will
	    //not be possible to re-configure it before making sure that the Enable bit
	    //has been cleared by hardware. If the Stream is used only once, this step might
	    //be bypassed.

	while (DMA_GetCmdStatus(SPI_PORT_TX_DMA_STREAM) != DISABLE);
	// Configure DMA controller to manage TX DMA requests for the HCMS display
	// first make sure we are using the default values
	DMA_StructInit(&DMA_InitStructure);
	// these are the only parameters that change from the defaults
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) & (SPI2->DR);
	DMA_InitStructure.DMA_Channel = SPI_PORT_TX_DMA_CHANNEL;
    DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;

	   //It is not possible to call DMA_Init without values for the source
	   //address and non-zero size even though a transfer is not done here.
	   //These are checked only when the assert macro are active though.

	DMA_InitStructure.DMA_Memory0BaseAddr = 0;
	DMA_InitStructure.DMA_BufferSize = 1;
	DMA_Init(SPI_PORT_TX_DMA_STREAM, &DMA_InitStructure);
	// Enable the DMA transfer complete interrupt
	DMA_ITConfig(SPI_PORT_TX_DMA_STREAM, DMA_IT_TC, ENABLE);
	  // enable the interrupt in the NVIC
	NVIC_InitStructure.NVIC_IRQChannel = SPI_PORT_DMA_TX_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	// Enable dma tx request.
	SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Tx, ENABLE);
    }

    //DMA buffer
    void spiPutBufferDMA(uint8_t * buffer, uint16_t length)
    {
    SPI_PORT_TX_DMA_STREAM->NDTR = length;
    SPI_PORT_TX_DMA_STREAM->M0AR = (uint32_t) buffer;
    DMA_Cmd(SPI_PORT_TX_DMA_STREAM, ENABLE);
    }

*/

/*
	///DMA interrupt routine
	void SPI_PORT_DMA_TX_IRQHandler() {

	// Test if DMA Stream Transfer Complete interrupt

	STM_EVAL_LEDToggle(LED4); //led for debug

	if (DMA_GetITStatus(SPI_PORT_TX_DMA_STREAM, DMA_IT_TCIF4))
	 {
	  DMA_ClearITPendingBit(SPI_PORT_TX_DMA_STREAM, DMA_IT_TCIF4);

	    //There is an unpleasant wait until we are certain the data has been sent.
	    // The need for this has been verified by oscilloscope. The shift register
	    // at this point may still be clocking out data and it is not safe to
	    // release the chip select line until it has finished. It only costs half
	    // a microsecond so better safe than sorry. Is it...

	    //  a) flushed from the transmit buffer

	    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET)
	    {
	    };

	     //b) flushed out of the shift register

	    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) == SET)
	    {
	    };
	  }
	  STM_EVAL_LEDToggle(LED4);
	  s595_CE_HI;        //s595_CE pin high
	}
*/






