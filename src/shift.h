/*
 * shift.h
 *
 * this is for use with a 74hc595 shift register
 *
 *  Created on: Apr 19, 2013
 *      Author: Timotet
 */

#ifndef SHIFT_H_
#define SHIFT_H_

#ifdef	__cplusplus
extern "C" {
#endif

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "integer.h"

#define s595_Latch          GPIO_Pin_0    //connect to pin  PB 0 on discovery board

#define s595_Latch_HI       GPIO_SetBits(GPIOB,s595_Latch)
#define s595_Latch_LO       GPIO_ResetBits(GPIOB,s595_Latch)

//function prototypes
void s595_Put(UINT data);
void clearShift(void);


#ifdef	__cplusplus
}
#endif

#endif /* SHIFT_H_ */
