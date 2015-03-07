/*
 * Delay.c
 *
 *  Created on: Apr 17, 2012
 *      Author: Tim Toliver
 */
#include "Delay.h"
#include "integer.h"
#include "stm32f4xx.h"

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void Delay(ULONG nTime)
{
  TimingDelay = nTime;

  while(TimingDelay != 0);
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  {
    TimingDelay--;
  }
}

/**
* @brief Inserts a delay time in uS.
* @param delay_us: specifies the delay time in micro second.
* @retval None
*/
void DelayUs(ULONG delay_us)
{
uint32_t nb_loop;

nb_loop = (((SystemCoreClock / 1000000)/4)*delay_us)+1; /* uS (divide by 4 because each loop take about 4 cycles including nop +1 is here to avoid delay of 0 */
asm volatile(
"1: " "\n\t"
" nop " "\n\t"
" subs.w %0, %0, #1 " "\n\t"
" bne 1b " "\n\t"
: "=r" (nb_loop)
: "0"(nb_loop)
: "r3"
);
}
