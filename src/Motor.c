/*
 * Motor.c
 *
 *  Created on: Nov 15, 2018
 *      Author: Kai Zhao
 */


#include "Motor.h"
#include "stm32f4xx_it.h"
#include "stm32f4xx_conf.h"

//#include "delay_other.h"

void Motor_12_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_ResetBits(GPIOA,GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_4|GPIO_Pin_5);
}

void Motor_1_STOP(void)
{
	IN1(High);
	IN2(High);
}

void Motor_1_PRun(void)
{
	IN1(Low);
	IN2(High);
}

void Motor_1_NRun(void)
{
	IN1(High);
	IN2(Low);
}

void Motor_2_STOP(void)
{
	IN3(High);
	IN4(High);
}

void Motor_2_PRun(void)
{
	IN3(Low);
	IN4(High);
}

void Motor_2_NRun(void)
{
	IN3(High);
	IN4(Low);
}



