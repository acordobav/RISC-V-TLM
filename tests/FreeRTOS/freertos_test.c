#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Banco de registros
#include "../../inc/ProjectAddress.h"
#include "../../src/Proyecto4/memory_map.h"

//Xterm
#define TRACE (*(unsigned char *)0x40000000)

extern void register_timer_isr();

QueueHandle_t queue_hour_to_day = NULL;
QueueHandle_t queue_day_to_reset = NULL;
QueueHandle_t queue_sensor_data = NULL;


#define ENABLE (*(int *)(PROJECT_ADDRESS))

//Direcciones de memoria para acceder datos del Sensor
#define DATASENSOR1 (*(int *)(REG_DISTANCE0)) //Sensor 1
#define DATASENSOR2 (*(int *)(REG_DISTANCE1)) //Sensor 2
#define DATASENSOR3 (*(int *)(REG_DISTANCE2)) //Sensor 3
#define DATASENSOR4 (*(int *)(REG_DISTANCE3)) //Sensor 4
#define DATASENSOR5 (*(int *)(REG_DISTANCE4)) //Sensor 5
#define DATASENSOR6 (*(int *)(REG_DISTANCE5)) //Sensor 6
#define DATASENSOR7 (*(int *)(REG_DISTANCE6)) //Sensor 7
#define DATASENSOR8 (*(int *)(REG_DISTANCE7)) //Sensor 8

#define ROWS (*(int *)(REG_IMAGE_ROWS)) //ROWS
#define COLS (*(int *)(REG_IMAGE_COLS)) //COLS

typedef struct {
    int *values; //Assume n animals are going to be detected per hour
    int size;
} SensorData;

static int count_hours = 0;
static int days_saved = 0;

static int internal_range = 0;
static int internal_1m = 0;
static int internal_2m = 0;
static int internal_3m = 0;
static int internal_range_out = 0;
static int internal_total_animals = 0;

static int range = 0;
static int results_1m = 0;
static int results_2m = 0;
static int results_3m = 0;
static int total_animals = 0;
static int average_out = 0;

static int range_day = 0;
static int results_1m_day = 0;
static int results_2m_day = 0;
static int results_3m_day = 0;
static int total_animals_day = 0;
static int average_out_day = 0;

static int iteration = 0;

//------------Code Starts Here-------------------------
void calculate_Statistics_hours(int *values, int size, bool save_data_hour){

    //Get register value ------------------------------
    // ADD CODE

    iteration++;

    //Calculate Statistics ---------------------------
    if (save_data_hour){
        for (int i=0; i<size; i++){
            if (values[i] >= 2 && values[i] <= 400){
                internal_total_animals += 1;
                internal_range += values[i];
            
                if (values[i] >= 2 && values[i] <= 50){
                    internal_1m += 1;
                }
                else if (values[i] > 50 && values[i] <= 200){
                    internal_2m += 1;
                }
                else if (values[i] > 200 && values[i] <= 400){
                    internal_3m += 1;
                }
                else{
                    ;
                }
            }

        }
        internal_range_out = internal_range/internal_total_animals;
        count_hours++;
    }

    //Output results ----------------------------------
    range += internal_range;
    results_1m += internal_1m;
    results_2m += internal_2m;
    results_3m += internal_3m;
    total_animals += internal_total_animals;
    average_out += internal_range_out/count_hours;

    /*
    printf("NEW HOUR DATA.\n");
    printf("Total of animals detected: %d.\n", total_animals);
    printf("Total distance: %d.\n", range);
    printf("Number of animals on 1st zone: %d.\n", results_1m);
    printf("Number of animals on 2nd zone: %d.\n", results_2m);
    printf("Number of animals on 3rd zone: %d.\n", results_3m);
    printf("Average distance: %d.\n", average_out);
    printf("NO MORE DATA.\n\n");
    */
}

void calculate_Statistics_day(int hours_to_save_day){

    // Fist, determine if the Statistics can be saved now
    if (hours_to_save_day >= 10){
        
        days_saved++;
        range_day = range;
        results_1m_day = results_1m;
        results_2m_day = results_2m;
        results_3m_day = results_3m;
        total_animals_day = total_animals;
        average_out_day = average_out;

        printf("NEW DAY DATA.\n");
        printf("Corresponding day Data: %d.\n", days_saved);
        printf("Number of hours: %d.\n", count_hours);
        printf("Total of animals detected: %d.\n", total_animals_day);
        printf("Total distance: %d.\n", range_day);
        printf("Number of animals on 1st zone: %d.\n", results_1m_day);
        printf("Number of animals on 2nd zone: %d.\n", results_2m_day);
        printf("Number of animals on 3rd zone: %d.\n", results_3m_day);
        printf("Average distance: %d.\n", average_out_day);
        printf("NO MORE DATA.\n\n");

        //Reset the hour counter
        count_hours = 0;
    }
}
  
void reset_Statistics(int reset_data){
    if (reset_data == 1){
        internal_range = 0;
        internal_1m = 0;
        internal_2m = 0;
        internal_3m = 0;
        internal_total_animals = 0;
        internal_range_out = 0;
    }
    
    //Output results ----------------------------------
    range = internal_range;
    results_1m = internal_1m;
    results_2m = internal_2m;
    results_3m = internal_3m;
    total_animals = internal_total_animals;
    average_out = internal_range_out;
}

static void task_read_sensor_data(void *pParameter) {
    printf("Task Read Sensor Data starts\n");

    SensorData sensorData;
    int dataReadCounter = 0;

	sensorData.size = 10;
    sensorData.values = (int *)malloc(sensorData.size * sizeof(int));

    while(1){
        /*
        printf("Received Sensor Data:\n");
        for (int i = 0; i < sensorData.size; i++) {
            printf("Current Value[%d] = %d\n", i, sensorData.values[i]);
        }
        */

        //Reading possible data coming from sensors. Not sending until 10 measures
        //are read
        //printf("Trying to read data");
        if (DATASENSOR1 > 0 && dataReadCounter<10){
            sensorData.values[dataReadCounter] = DATASENSOR1;
            dataReadCounter++;
        }
        if (DATASENSOR2 > 0 && dataReadCounter<10){
            sensorData.values[dataReadCounter] = DATASENSOR2;
            dataReadCounter++;
        }
        if (DATASENSOR3 > 0 && dataReadCounter<10){
            sensorData.values[dataReadCounter] = DATASENSOR3;
            dataReadCounter++;
        }
        if (DATASENSOR4 > 0 && dataReadCounter<10){
            sensorData.values[dataReadCounter] = DATASENSOR4;
            dataReadCounter++;
        }
        if (DATASENSOR5 > 0 && dataReadCounter<10){
            sensorData.values[dataReadCounter] = DATASENSOR5;
            dataReadCounter++;
        }
        if (DATASENSOR6 > 0 && dataReadCounter<10){
            sensorData.values[dataReadCounter] = DATASENSOR6;
            dataReadCounter++;
        }
        if (DATASENSOR7 > 0 && dataReadCounter<10){
            sensorData.values[dataReadCounter] = DATASENSOR7;
            dataReadCounter++;
        }
        if (DATASENSOR8 > 0 && dataReadCounter<10){
            sensorData.values[dataReadCounter] = DATASENSOR8;
            dataReadCounter++;
        }

        //We have read all required values. Lets send the data
        if (dataReadCounter == 10){
            xQueueSend(queue_sensor_data, &sensorData, portMAX_DELAY);
            dataReadCounter = 0;
        }
        
        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
}

static void task_calculate_statistics_hour(void *pParameter) {
    printf("Task 1 starts\n");

	SensorData sensorData;
	sensorData.size = 10;
	int count = 0;

	while(1){
        printf("Task 1 being executed\n");
		if (xQueueReceive(queue_sensor_data, &sensorData, portMAX_DELAY)){

            /*
            printf("Received Sensor Data:\n");
            for (int i = 0; i < sensorData.size; i++) {
                printf("Value[%d] = %.d\n", i, sensorData.values[i]);
            }
            */

			calculate_Statistics_hours(sensorData.values, sensorData.size, true);
			count++;

			if (count >= 10){
				xQueueSend(queue_hour_to_day, &count, portMAX_DELAY);
				count = 0;
			}
		}
		
		
		vTaskDelay(100 / portTICK_PERIOD_MS);
	}
}

static void task_calculate_statistics_day(void *pParameter) {
	printf("Task 2 starts\n");
    
    int countHours;
	int reset = 0;
    while(1) {
        printf("Task 2 being executed\n");
        // Recibir datos de la cola
        if (xQueueReceive(queue_hour_to_day, &countHours, portMAX_DELAY)) {
            calculate_Statistics_day(countHours);

			reset = 1;
            xQueueSend(queue_day_to_reset, &reset, portMAX_DELAY);
			reset = 0;
        }
    }
}

static void task_reset_statistics(void *pParameter) {
	printf("Task 3 starts\n");
    
    int reset = 0;
    while(1) {
        printf("Task 3 being executed\n");
        // Recibir datos de la cola
        if (xQueueReceive(queue_day_to_reset, &reset, portMAX_DELAY)) {
            // Llama a la función para reiniciar estadísticas
            reset_Statistics(reset);
        }
    }
}

int main( void )
{

	printf("Starting FreeRTOS test\n");
	
    //Set init parameters
	ROWS = 323;
    COLS = 434;

    // Just for testing. Memory address of the project. Data 'coming' from Sensors
    // This variables can be changed to see specific results during first iteration of the program
    DATASENSOR1 = 0;
    DATASENSOR2 = 0;
    DATASENSOR3 = 0;
    DATASENSOR4 = 0;
    DATASENSOR5 = 0;
    DATASENSOR6 = 0;
    DATASENSOR7 = 0;
    DATASENSOR8 = 0;

    //Init system
    ENABLE = 1;

	/* Create queues */
	queue_hour_to_day  = xQueueCreate(10, sizeof(int));
	queue_day_to_reset = xQueueCreate(10, sizeof(int));
	queue_sensor_data  = xQueueCreate(10, sizeof(SensorData));
	
	/* Create tasks */
	xTaskCreate(task_read_sensor_data, "TaskRead", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL);
	xTaskCreate(task_calculate_statistics_hour, "TaskHours", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL);
	xTaskCreate(task_calculate_statistics_day, "TaskDay", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL);
	xTaskCreate(task_reset_statistics, "TaskReset", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL);

	/* Start the kernel.  From here on, only tasks and interrupts will run. */
	vTaskStartScheduler();

	/* Exit FreeRTOS */
	return 0;
}

void vApplicationMallocFailedHook( void )
{
	/* vApplicationMallocFailedHook() will only be called if
	configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
	function that will get called if a call to pvPortMalloc() fails.
	pvPortMalloc() is called internally by the kernel whenever a task, queue,
	timer or semaphore is created.  It is also called by various parts of the
	demo application.  If heap_1.c or heap_2.c are used, then the size of the
	heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
	FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
	to query the size of free heap space that remains (although it does not
	provide information on how the remaining heap might be fragmented). */
	taskDISABLE_INTERRUPTS();

	TRACE='M';
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
	/* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
	to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
	task.  It is essential that code added to this hook function never attempts
	to block in any way (for example, call xQueueReceive() with a block time
	specified, or call vTaskDelay()).  If the application makes use of the
	vTaskDelete() API function (as this demo application does) then it is also
	important that vApplicationIdleHook() is permitted to return to its calling
	function, because it is the responsibility of the idle task to clean up
	memory allocated by the kernel to any task that has since been deleted. */
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
	( void ) pcTaskName;
	( void ) pxTask;

	/* Run time stack overflow checking is performed if
	configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
	function is called if a stack overflow is detected. */
	taskDISABLE_INTERRUPTS();
	TRACE = 'S';
	for( ;; );
}
/*-----------------------------------------------------------*/
