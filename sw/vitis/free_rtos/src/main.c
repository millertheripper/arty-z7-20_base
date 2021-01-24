/* FreeRTOS includes. */
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* Xilinx includes. */
#include "xil_printf.h"
#include "xparameters.h"
#include "xgpio.h"

#define DELAY_10_SECONDS	10000UL
#define DELAY_1_SECOND		1000UL
/*-----------------------------------------------------------*/
/* Private function prototypes */
static void task_producer(void *pvParameters);
static void task_consumer(void *pvParameters);
static void task_led(void *pvParameters);

// TODO: Add some tasks that do a printf.. Printf might be mixed up
// TODO: Add two tasks that demonstrates the use of mutexes (read and write to global array)
// TODO: Show how tasks can be launched in order or must be launched in order

/*-----------------------------------------------------------*/
/* FreeRTOS Task handles */
static TaskHandle_t thandle_task_producer;
static TaskHandle_t thandle_task_consumer;
static TaskHandle_t thandle_task_led;

/* FreeRTOS Queues */
static QueueHandle_t xQueue = NULL;

/* FreeRTOS Semaphores */

/* Other private globals */
static XGpio gpio_led;
static XGpio gpio_button;

int main(void)
{
	printf("Hello from FreeRTOS.\r\n");

	/* Create the two tasks.  The Tx task is given a lower priority than the
	Rx task, so the Rx task will leave the Blocked state and pre-empt the Tx
	task as soon as the Tx task places an item in the queue. */
	xTaskCreate( task_producer, 			/* The function that implements the task. */
				 (const char *)"Producer",  /* Text name for the task, provided to assist debugging only. */
				 configMINIMAL_STACK_SIZE, 	/* The stack allocated to the task. */
				 NULL, 						/* The task parameter is not used, so set to NULL. */
				 tskIDLE_PRIORITY,			/* The task runs at the idle priority. */
				 &thandle_task_producer);	/* Save task handle in global variable */

	xTaskCreate( task_consumer,
				 (const char *)"Consumer",
				 configMINIMAL_STACK_SIZE,
				 NULL,
				 tskIDLE_PRIORITY + 1,
				 &thandle_task_consumer);

	xTaskCreate( task_led,
				 (const char *)"Led",
				 configMINIMAL_STACK_SIZE,
				 NULL,
				 tskIDLE_PRIORITY,
				 &thandle_task_led);

	/* Create the queue used by the tasks to communicate */
	xQueue = xQueueCreate(10, sizeof(char));	/* Create a queue with 10 characters */

	/* Check the queue was created. */
	configASSERT(xQueue);

	/* Pass control to the system scheduler */
	vTaskStartScheduler();

	/* If all is well, the scheduler will now be running, and the following line
	will never be reached.  If the following line does execute, then there was
	insufficient FreeRTOS heap memory available for the idle and/or timer tasks
	to be created.  See the memory management section on the FreeRTOS web site
	for more details. */
	for( ;; );
}

/*-----------------------------------------------------------*/
static void task_led(void *pvParameters)
{
	uint32_t led;

	/* Initialize LED gpio, channel 0, as output (output = 0) */
	XGpio_Initialize(&gpio_led, XPAR_AXI_GPIO_0_DEVICE_ID);
	XGpio_SetDataDirection(&gpio_led, 0, 0);

	/* Initialize BUTTON gpio, channel 0, as input (input = 1) */
	XGpio_Initialize(&gpio_button, XPAR_AXI_GPIO_1_DEVICE_ID);
	XGpio_SetDataDirection(&gpio_button, 0, 1);

	XGpio_DiscreteWrite(&gpio_led, 0, 0x0f);

	while (1) {
		/* Do a read modify write to led register */
		led = XGpio_DiscreteRead(&gpio_led, 0);
		led |= 0x01;
		XGpio_DiscreteWrite(&gpio_led, 0, led);
		vTaskDelay(50);

		led = XGpio_DiscreteRead(&gpio_led, 0);
		led &=~ 0x01;
		XGpio_DiscreteWrite(&gpio_led, 0, 0x0);
		vTaskDelay(50);
	}
}


/*-----------------------------------------------------------*/
static void task_producer(void *pvParameters)
{
	const TickType_t x1second = pdMS_TO_TICKS( DELAY_1_SECOND );
	uint32_t i = 0;

	while(1) {
		/* Delay for 1 second. */
		vTaskDelay(x1second);

		/* Send the next value on the queue.  The queue should always be
		empty at this point so a block time of 0 is used. */
		i++;
		xil_printf("task_producer: Sent: %u\r\n", i);
		xQueueSend(xQueue, &i, 10);
	}
}

/*-----------------------------------------------------------*/
static void task_consumer(void *pvParameters)
{
	uint32_t i = 0;

	while(1) {
		/* Block to wait for data arriving on the queue. */
		xQueueReceive(xQueue, &i, portMAX_DELAY); 	/* Wait without a timeout for data. */

		/* Print the received data. */
		xil_printf("task_consumer: Received: %u\r\n", i);
	}
}

