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
    
    for ( ;; )
    {
        vPrintString ( pcTaskName );
        buf1 = 0;
        for(int i = 0; i < 2000000; i++) buf1++;
    }
}

void vTaskFunction2 ( void * pvParameters )
{
    char * pcTaskName ;
    pcTaskName = ( char * ) pvParameters ;
    
    for ( ;; )
    { 
        vPrintString ( pcTaskName );
        buf2 = 0;
        for(int i = 0; i < 2000000; i++) buf2++;
       
    }
}
void vTaskFunction3 ( void * pvParameters )
{
    char * pcTaskName ;
    pcTaskName = ( char * ) pvParameters ;
    
    for ( ;; )
    {
        
        vPrintString ( pcTaskName );
        buf3 = 0;
        for(int i = 0; i < 10000000; i++) buf3++;
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
void vApplicationIdleHook ( void )
{

     vPrintString ( " IDLE Task is running \r \n" );
     buf3 = 0;
    for(int i = 0; i < 2000000; i++)
    {
        buf3++;
    }
}
void app_main(void)
{
    xTaskCreate ( vTaskFunction1 , " Task 1 " , 10000 ,( void *) pcTextForTask1 , 0 , NULL ) ;

    vTaskDelay(pdMS_TO_TICKS(1200));
    xTaskCreate ( vTaskFunction3 , " Task 3 " , 10000 ,( void *) pcTextForTask3 , 5 , NULL ) ;


    
}