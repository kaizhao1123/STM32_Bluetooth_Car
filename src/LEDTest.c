/*
 * LED.c
 *
 *  Created on: Nov 20, 2018
 *      Author: Kai Zhao
 */
#include <LEDTest.h>

void LEDInit()
{
	STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_EXTI);

	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED4);
	STM_EVAL_LEDInit(LED5);
	STM_EVAL_LEDInit(LED6);

	STM_EVAL_LEDOff(LED3);
	STM_EVAL_LEDOff(LED4);
	STM_EVAL_LEDOff(LED5);
	STM_EVAL_LEDOff(LED6);
}

void LEDOn(int led)
{
	STM_EVAL_LEDOn(led);
}

void LEDOff(int led)
{
	STM_EVAL_LEDOff(led);
}

