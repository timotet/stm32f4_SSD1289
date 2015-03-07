/*
 * spi.h
 *
 *   set up for 1 way tx spi to 74hc595 shift register 2 in series
 *   for future lcd interface
 *
 *  Created on: 4/19/13
 *      Author: Tim Toliver
 */

#ifndef SPI_H_
#define SPI_H_

#ifdef	__cplusplus
extern "C" {
#endif

#include "stm32f4xx.h"

 /* SPIx Communication Interface */
#define SPI2_CLK                       RCC_APB1Periph_SPI2
#define SPI2_CLK_CMD                   RCC_APB1PeriphClockCmd
#define SPI2_IRQn                      SPI2_IRQn
#define SPI2_IRQHANDLER                SPI2_IRQHandler

#define SPI2_SCK_PIN                   GPIO_Pin_13
#define SPI2_SCK_GPIO_PORT             GPIOB
#define SPI2_SCK_GPIO_CLK              RCC_AHB1Periph_GPIOB
#define SPI2_SCK_SOURCE                GPIO_PinSource13
#define SPI2_SCK_AF                    GPIO_AF_SPI2

#define SPI2_MOSI_PIN                  GPIO_Pin_15
#define SPI2_MOSI_GPIO_PORT            GPIOB
#define SPI2_MOSI_GPIO_CLK             RCC_AHB1Periph_GPIOB
#define SPI2_MOSI_SOURCE               GPIO_PinSource15
#define SPI2_MOSI_AF                   GPIO_AF_SPI2

#define SPI2_MISO_PIN                  GPIO_Pin_14
#define SPI2_MISO_GPIO_PORT            GPIOB
#define SPI2_MISO_GPIO_CLK             RCC_AHB1Periph_GPIOB
#define SPI2_MISO_SOURCE               GPIO_PinSource14
#define SPI2_MISO_AF                   GPIO_AF_SPI2

/*
#define SPI2_NSS_PIN                  GPIO_Pin_12
#define SPI2_NSS_GPIO_PORT            GPIOB
#define SPI2_NSS_GPIO_CLK             RCC_AHB1Periph_GPIOB
#define SPI2_NSS_SOURCE               GPIO_PinSource12
#define SPI2_NSS_AF                   GPIO_AF_SPI2
*/

/* Definition for DMAx resources **********************************************/
#define SPI_PORT_DR_ADDRESS                SPI_PORT->DR

#define SPI_PORT_DMA                       DMA1
#define SPI_PORT_DMAx_CLK                  RCC_AHB1Periph_DMA1

#define SPI_PORT_TX_DMA_CHANNEL            DMA_Channel_0
#define SPI_PORT_TX_DMA_STREAM             DMA1_Stream4
#define SPI_PORT_TX_DMA_FLAG_FEIF          DMA_FLAG_FEIF4
#define SPI_PORT_TX_DMA_FLAG_DMEIF         DMA_FLAG_DMEIF4
#define SPI_PORT_TX_DMA_FLAG_TEIF          DMA_FLAG_TEIF4
#define SPI_PORT_TX_DMA_FLAG_HTIF          DMA_FLAG_HTIF4
#define SPI_PORT_TX_DMA_FLAG_TCIF          DMA_FLAG_TCIF4

#define SPI_PORT_DMA_TX_IRQn               DMA1_Stream4_IRQn
#define SPI_PORT_DMA_TX_IRQHandler         DMA1_Stream4_IRQHandler

//////////function prototypes//////////
void SPI_Config(void);
//void spiPutBufferDMA(uint8_t * buffer, uint16_t length);


#ifdef	__cplusplus
}
#endif


#endif /* SPI_H_ */
