#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "freertos/task.h"

static long long unsigned int buf1 = 0,  buf2 =0,  buf3 =0  ;

static const char * pcTextForTask1 = " Task 1 is running \r \n " ;
static const char * pcTextForTask2 = " Task 2 is running \r \n " ;
static const char * pcTextForTask3 = " Task 3 is running \r \n " ;


void vPrintString (char * pcTaskName )
{
    printf( "TIME: %lu- CORE: %d - %s",xTaskGetTickCount(), xPortGetCoreID(), pcTaskName );
}
void vTaskFunction1 ( void * pvParameters )
{
    char * pcTaskName ;
    pcTaskName = ( char * ) pvParameters ;
    vTaskDelay(pdMS_TO_TICKS(30));
    for ( ;; )
    {
        vPrintString ( pcTaskName );
        long long int time = xTaskGetTickCount() + 500;
        while (xTaskGetTickCount() <  time)
        {
            
        }
        vPrintString ( " TASK 1 END \r \n");
        taskYIELD();
    }
}

void vTaskFunction2 ( void * pvParameters )
{
    char * pcTaskName ;
    pcTaskName = ( char * ) pvParameters ;
    vTaskDelay(pdMS_TO_TICKS(1500));
    for ( ;; )
    { 
        vPrintString ( pcTaskName );
        long long int time = xTaskGetTickCount() + 200;
        while (xTaskGetTickCount() <  time)
        {
            
        }
        vPrintString ( " TASK 2 END \r \n");
        vTaskDelay(pdMS_TO_TICKS(10000));
    }
}
void vTaskFunction3 ( void * pvParameters )
{
    char * pcTaskName ;
    pcTaskName = ( char * ) pvParameters ;
    vTaskDelay(pdMS_TO_TICKS(500));
    for ( ;; )
    {
        
        vPrintString ( pcTaskName );
        long long int time = xTaskGetTickCount() + 200;
        while (xTaskGetTickCount() <  time)
        {
            
        }
        vPrintString ( " TASK 3 END \r\n");
        vTaskDelay(pdMS_TO_TICKS(10000));
    }
}
void vApplicationIdleHook ( void )
{

    //  vPrintString ( " IDLE Task is running \r \n" );
    //  buf3 = 0;
    // for(int i = 0; i < 2000000; i++)
    // {
    //     buf3++;
    // }
}
void app_main(void)
{
    xTaskCreate ( vTaskFunction1 , " Task 1 " , 10000 ,( void *) pcTextForTask1 , 0 , NULL ) ;
    xTaskCreate ( vTaskFunction2 , " Task 2 " , 10000 ,( void *) pcTextForTask2 , 2 , NULL ) ;
    xTaskCreate ( vTaskFunction3 , " Task 3 " , 10000 ,( void *) pcTextForTask3 , 5 , NULL ) ;

    
}