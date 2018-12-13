/*
 * Bluetooth.c
 *
 *  Created on: Nov 13, 2018
 *      Author: kaizhao
 */

#include <LEDTest.h>
#include "bluetooth.h"
#include "Motor.h"
#include "stm32f4_discovery.h"

#if SYSTEM_SUPPORT_OS
#include "includes.h"
#endif
#if EN_USART2_RX




u8 USART2_RX_BUF[USART2_REC_LEN];

u16 USART2_RX_STA=0;

void bluetooth_init(u32 bound){

    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
  //  SystemInit();

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);

    GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2);
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2);

    //GPIOA2,3->USART2RxTx
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    //USART2 init
    USART_InitStructure.USART_BaudRate = bound;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART2, &USART_InitStructure);

    USART_Cmd(USART2, ENABLE);

    //USART2_ClearFlag(USART2, USART2_FLAG_TC);

#if EN_USART2_RX
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//interrupt

    //USART2 NVIC
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//USART2 interrupt channel
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IQR enable
    NVIC_Init(&NVIC_InitStructure);

#endif
}


void USART2_IRQHandler(void)
{
    u8 Res;
#if SYSTEM_SUPPORT_OS
    OSIntEnter();
#endif
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
        Res = USART_ReceiveData(USART2);//(USART2->DR)
//      USART_SendData(USART2,Res);
        if(Res == 0x01)
        {
            LEDOn(LED3);
            Motor_1_PRun();
            Motor_2_STOP();
        }
        else if(Res == 0x02)
        {
        	LEDOn(LED4);
        	Motor_1_NRun();
        	Motor_2_STOP();
        }
        else if(Res == 0x03)
        {
        	LEDOn(LED5);
        	Motor_1_PRun();
        	Motor_2_PRun();
        }
        else if(Res == 0x04)
        {
        	LEDOn(LED6);
        	Motor_1_PRun();
        	Motor_2_NRun();
        }
        else if(Res == 0x05)
        {
        	LEDOff(LED3);
        	LEDOff(LED4);
        	LEDOff(LED5);
        	LEDOff(LED6);
        	Motor_1_STOP();
        	Motor_2_STOP();
        }
  }
#if SYSTEM_SUPPORT_OS
    OSIntExit();
#endif
}
#endif


