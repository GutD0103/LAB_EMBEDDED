#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "driver/gpio.h"

uint8_t pre_button = 0;
uint8_t cur_button = 0;

void set_up(void){
    gpio_set_direction( GPIO_NUM_2 , GPIO_MODE_INPUT );
    gpio_set_pull_mode(GPIO_NUM_2 ,GPIO_PULLUP_ONLY);
}
void GetKeyInput(void){
    for(;;){
        cur_button = gpio_get_level(GPIO_NUM_2);
        if(cur_button == pre_button){
            if(cur_button == 1){
                printf("ESP\n");
            }
        }
        pre_button = cur_button;
        vTaskDelay(5/portTICK_PERIOD_MS);
    }
}
void PrintStuIdf(void){
    for(;;){
        printf("%lld :2012945\n",esp_timer_get_time()/1000);
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }

}
void app_main(void)
{
    set_up();
    xTaskCreate(GetKeyInput,"GET KEY INPUT",1000,NULL,1,NULL);
    xTaskCreate(PrintStuIdf,"PRINT STUDENT IDENTIFY",1000,NULL,2,NULL);
    vTaskEndScheduler();
}
