#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "driver/gpio.h"



int key_reg0 = 1;
int key_reg1 = 1;
int key_reg2 = 1;
int key_reg3 = 1;
void set_up(void){
    gpio_set_direction( GPIO_NUM_16 , GPIO_MODE_INPUT );
    gpio_set_pull_mode(GPIO_NUM_16 ,GPIO_PULLUP_ONLY);
}
void vGetKeyInput(void){

    while(1){
        key_reg0 = key_reg1;
        key_reg1 = key_reg2;
        key_reg2 = gpio_get_level(GPIO_NUM_16);
            
        // }
        if(key_reg0 == key_reg1 && key_reg1 == key_reg2){
            if(key_reg3 != key_reg2){
                key_reg3 = key_reg2;
                if(key_reg2 == 0){
                    printf("ESP\n");
                }
            }
        }
        vTaskDelay(10/portTICK_PERIOD_MS);
    }
}
void vPrintStuIdf(void){
    while (1)
    {
        printf("2012945\n");
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }

}
void app_main(void)
{
    set_up();
    xTaskCreate(vGetKeyInput,"GET KEY INPUT",1000,NULL,0,NULL);
    xTaskCreate(vPrintStuIdf,"PRINT STUDENT IDENTIFY",1000,NULL,0,NULL);
    // vTaskStartScheduler();

    
}
