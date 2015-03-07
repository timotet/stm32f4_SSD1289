/*
 * Delay.h
 *
 *  Created on: Apr 17, 2012
 *      Author: Tim Toliver
 */

#ifndef DELAY_H_
#define DELAY_H_

#ifdef	__cplusplus
extern "C" {
#endif

#include "integer.h"

ULONG TimingDelay;

//void Delay(UINT nCount);
void Delay(ULONG nTime);
void DelayUs(ULONG delay_us);
void TimingDelay_Decrement(void);

#ifdef	__cplusplus
}
#endif

#endif /* DELAY_H_ */
