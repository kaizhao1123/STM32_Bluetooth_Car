/*
 * LED.h
 *
 *  Created on: Nov 20, 2018
 *      Author: Kai Zhao
 */

#ifndef LEDTEST_H_
#define LEDTEST_H_

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void LEDInit();
void LEDOn(int led);
void LEDOff(int led);

#endif /* LEDTEST_H_ */
