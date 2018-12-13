
/* Standard includes. */
#include <LEDTest.h>
#include <stdint.h>

/* Kernel includes. */
#include "stm32f4xx.h"
#include "../FreeRTOS_Source/include/FreeRTOS.h"
#include "../FreeRTOS_Source/include/queue.h"
#include "../FreeRTOS_Source/include/semphr.h"
#include "../FreeRTOS_Source/include/task.h"
#include "../FreeRTOS_Source/include/timers.h"
#include "stm32f4_discovery.h"
#include "Motor.h"
#include "Bluetooth.h"

#define mainEVENT_SEMAPHORE_TASK_PRIORITY	( configMAX_PRIORITIES - 1 )
#define Motor_TASK_PRIORITY                 ( tskIDLE_PRIORITY + 3)
#define Bluetooth_TASK_PRIORITY             ( tskIDLE_PRIORITY + 2)
#define mainSOFTWARE_TIMER_PERIOD_MS		( 1000 / portTICK_RATE_MS )
#define Motor_Period_MS                     ( 1000 / portTICK_RATE_MS)
#define Bluetooth_Period_MS					( 1000 / portTICK_RATE_MS)

#define mainQUEUE_LENGTH					( 1 )


static void prvSetupHardware( void );
static void MotorTask(void *pvParameters);
static void BluetoothTask(void *pvParameters);
static void vExampleTimerCallback( xTimerHandle xTimer );
static xQueueHandle xQueue = NULL;
static xSemaphoreHandle xEventSemaphore = NULL;

static volatile uint32_t ulCountOfTimerCallbackExecutions = 0;
static volatile uint32_t ulCountOfItemsReceivedOnQueue = 0;
static volatile uint32_t ulCountOfReceivedSemaphores = 0;

/*-----------------------------------------------------------*/

int main(void)
{
xTimerHandle xExampleSoftwareTimer = NULL;

	prvSetupHardware();
    LEDInit();
	//LEDOn(LED6);
	bluetooth_init(9600);

	//LEDOn(LED5);
	/*STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_EXTI);

	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED4);
	STM_EVAL_LEDInit(LED5);
	STM_EVAL_LEDInit(LED6);

	STM_EVAL_LEDOff(LED3);
	STM_EVAL_LEDOff(LED4);
	STM_EVAL_LEDOff(LED5);
	STM_EVAL_LEDOff(LED6);*/

	xQueue = xQueueCreate( 	mainQUEUE_LENGTH,		/* The number of items the queue can hold. */
							sizeof( uint32_t ) );	/* The size of each item the queue holds. */
	/* Add to the registry, for the benefit of kernel aware debugging. */
	vQueueAddToRegistry( xQueue, "MainQueue" );

	vSemaphoreCreateBinary( xEventSemaphore );
	/* Add to the registry, for the benefit of kernel aware debugging. */
	vQueueAddToRegistry( xEventSemaphore, "xEventSemaphore" );



	/*xTaskCreate( MotorTask,
				 "Motor",
				 configMINIMAL_STACK_SIZE,
				 NULL,
				 Motor_TASK_PRIORITY,
				 NULL);*/
	xTaskCreate( BluetoothTask,
				"Bluetooth",
				configMINIMAL_STACK_SIZE,
				NULL,
				Bluetooth_TASK_PRIORITY,
				NULL);


	xExampleSoftwareTimer = xTimerCreate("LEDTimer", /* A text name, purely to help debugging. */
								mainSOFTWARE_TIMER_PERIOD_MS,		/* The timer period, in this case 1000ms (1s). */
								pdTRUE,								/* This is a periodic timer, so xAutoReload is set to pdTRUE. */
								( void * ) 0,						/* The ID is not used, so can be set to anything. */
								vExampleTimerCallback				/* The callback function that switches the LED off. */
							);

	xTimerStart( xExampleSoftwareTimer, 0 );
	vTaskStartScheduler();
	//for( ;; );
}
/*-----------------------------------------------------------*/

static void vExampleTimerCallback( xTimerHandle xTimer )
{
	ulCountOfTimerCallbackExecutions++;
}


/*static void MotorTask(void *pvParameters)
{
	portTickType xNextWakeTime;
	xNextWakeTime = xTaskGetTickCount();

	Motor_12_Config();
			STM_EVAL_LEDOn(LED4);

					Motor_1_PRun();
					STM_EVAL_LEDOn(LED5);
					for(int i = 0; i <= 16000000; i ++);
					Motor_1_STOP();
					STM_EVAL_LEDOff(LED5);

					for(int i = 0; i <= 16000000; i ++);
					Motor_1_PRun();
					STM_EVAL_LEDOn(LED5);

					for(int i = 0; i <= 16000000; i ++);
					Motor_1_STOP();
					STM_EVAL_LEDOff(LED5);

					Motor_2_PRun();
					STM_EVAL_LEDOn(LED6);
		for (;;)
		{
			STM_EVAL_LEDOn(LED3);
			for(int i = 0; i <= 800000; i ++);
			STM_EVAL_LEDOff(LED3);
			vTaskDelayUntil(&xNextWakeTime, Motor_Period_MS);
		}

}*/

static void BluetoothTask(void *paParameters)
{
	Motor_12_Config();
	for(;;)
	{

		USART2_IRQHandler();
	}

}
/*-----------------------------------------------------------*/

void vApplicationTickHook( void )
{
portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
static uint32_t ulCount = 0;

	ulCount++;
	if( ulCount >= 500UL )
	{

		xSemaphoreGiveFromISR( xEventSemaphore, &xHigherPriorityTaskWoken );
		ulCount = 0UL;
	}

}
/*-----------------------------------------------------------*/

void vApplicationMallocFailedHook( void )
{
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( xTaskHandle pxTask, signed char *pcTaskName )
{
	( void ) pcTaskName;
	( void ) pxTask;
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
volatile size_t xFreeStackSpace;
	xFreeStackSpace = xPortGetFreeHeapSize();
}
/*-----------------------------------------------------------*/

static void prvSetupHardware( void )
{
	NVIC_SetPriorityGrouping( 0 );
}



