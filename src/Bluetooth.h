/*
 * Bluetooth.h
 *
 *  Created on: Nov 13, 2018
 *      Author: kaizhao
 */

#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_
#include "stdio.h"
#include "stm32f4xx_conf.h"
//#include "sys.h"

#define USART2_REC_LEN              200
#define EN_USART2_RX                1

extern u8  USART2_RX_BUF[USART2_REC_LEN];
extern u16 USART2_RX_STA;

void bluetooth_init(u32 bound);
void USART2_IRQHandler(void);


#endif /* BLUETOOTH_H_ */
