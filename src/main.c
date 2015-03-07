/*
 * main.c
 *
 *  Created on: 2/4/14
 *      Author: Timotet
 */

#include "integer.h"
#include "stm32f4_discovery.h"
#include "spi.h"
#include "stm32f4xx.h"
#include "Delay.h"
#include "shift.h"
//#include "stm32f4xx_usart.h"
#include "SSD1289.h"
//#include "font_5x7.h"


//LONG TimeOut;
//UCHAR Counter = 0;

/*Private defines---------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;
//USART_InitTypeDef USART_InitStructure;

/* function prototypes -----------------------------------------------*/
static void GPIO_Config(void);
//static void Usart_Config(void);
static void SysTickConfig(void);

int main(void) {

	GPIO_Config();
	SysTickConfig();
	SPI_Config();
	//Usart_Config();

	clearShift();
	Delay(10);
	SSD1289_init();

	while (1) {


		putColor(Red);
		Delay(1000);
		Clear(1);
		putColor(Blue);
		Delay(1000);
		Clear(1);
		putColor(White);
		Delay(1000);
		Clear(1);
		putColor(Cyan);
		Delay(1000);
		Clear(1);
		putColor(Yellow);
		Delay(1000);
		Clear(1);
		putColor(Purple);
		Delay(1000);
		Clear(1);

		setColor(Green);
		drawString(1,1, "Hello World!");
		Delay(5000);

	}

}

/////////////////////////Functions/////////////////////////////

static void GPIO_Config(void) {
	/* GPIOB Periph clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	/* Configure PB0 in output push pull mode */
	GPIO_InitStructure.GPIO_Pin = s595_Latch;    //PB0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* Configure PB1 in output push pull mode */
	GPIO_InitStructure.GPIO_Pin = LCD_VCC; //PB1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* Configure PB2 in output push pull mode */
	GPIO_InitStructure.GPIO_Pin = LCD_LED;    //PB2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* Configure PB3 in output push pull mode */
	GPIO_InitStructure.GPIO_Pin = SSD1289_R;    //PB3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* Configure PB4 in output push pull mode */
	GPIO_InitStructure.GPIO_Pin = SSD1289_WR; //PB4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* Configure PB5 in output push pull mode */
	GPIO_InitStructure.GPIO_Pin = SSD1289_RST; //PB5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* Configure PB6 in output push pull mode */
	GPIO_InitStructure.GPIO_Pin = SSD1289_REGSEL; //PB6
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* Configure PB7 in output push pull mode */
	GPIO_InitStructure.GPIO_Pin = SSD1289_CS; //PB7
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/*initialize leds on discovery board*/
	STM_EVAL_LEDInit(LED6);
	STM_EVAL_LEDInit(LED5);
	STM_EVAL_LEDInit(LED4);
	STM_EVAL_LEDInit(LED3);

	// start with these low
	s595_Latch_LO;
	LCD_VCC_LO;
	LCD_LED_LO;
	SSD1289_R_LO;
	SSD1289_WR_LO;
	SSD1289_RST_LO;
	SSD1289_REGSEL_LO;
	SSD1289_CS_LO;

}


//Configure a SysTick Base time to 10 ms.

static void SysTickConfig(void) {
	// Setup SysTick Timer for 1ms interrupts
	if (SysTick_Config(SystemCoreClock / 1000)) {
		// Capture error
		while (1);
	}

	// Configure the SysTick handler priority
	NVIC_SetPriority(SysTick_IRQn, 0x0F);
}

/*
void Usart_Config(void){
	{
	  // USARTx configured as follow:
	   //    - BaudRate = 115200 baud
	   //    - Word Length = 8 Bits
	   //    - One Stop Bit
	   //    - No parity
	   //    - Hardware flow control disabled (RTS and CTS signals)
	   //    - Receive and transmit enabled

	  GPIO_InitTypeDef GPIO_InitStructure;
	  USART_InitTypeDef USART_InitStructure;

	  // Enable GPIO clock
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	  // Enable UART clock
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	  // Connect PXx to USARTx_Tx
	  GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_USART3);

	  // Connect PXx to USARTx_Rx
	  GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_USART3);

	  // Configure USART Tx as alternate function
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOC, &GPIO_InitStructure);

	  // Configure USART Rx as alternate function
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	  GPIO_Init(GPIOC, &GPIO_InitStructure);

	  USART_InitStructure.USART_BaudRate = 115200;
	  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	  USART_InitStructure.USART_StopBits = USART_StopBits_1;
	  USART_InitStructure.USART_Parity = USART_Parity_No;
	  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	  // USART configuration
	  USART_Init(USART3, &USART_InitStructure);

	  //Enable USART
	  USART_Cmd(USART3, ENABLE);
	}
}
*/



////////////////////////////interrupts////////////////

void SysTick_Handler(void)
{
  TimingDelay_Decrement();
  STM_EVAL_LEDToggle(LED5);
}



/*

void SysTick_Handler(void)
{
  // Decrement the timeout value
  if (TimeOut != 0)
  {
    TimeOut--;
  }

  if (Counter < 10)
  {
    Counter++;
  }
  else
  {
    Counter = 0;
    STM_EVAL_LEDToggle(LED5);

  }
}
*/
