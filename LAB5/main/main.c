#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"

// Hàm Callback của bộ hẹn giờ
void TimerCallback(TimerHandle_t xTimer) {
    // Lấy dữ liệu từ timer
    void *pvTimerID = pvTimerGetTimerID(xTimer);
    
    // Kiểm tra ID của timer và thực hiện hành động tương ứng
    if (pvTimerID == (void *)1) {
        // Bộ hẹn giờ cho "ahihi"
        static int countAhihi = 0;
        printf("ahihi %d- Time: %lu\n",countAhihi, xTaskGetTickCount());
        countAhihi++;
        if (countAhihi >= 10) {
            printf("ahihi stop\n");
            xTimerStop(xTimer, portMAX_DELAY);
        }
    } else if (pvTimerID == (void *)2) {
        // Bộ hẹn giờ cho "ihaha"
        static int countIhaha = 0;
        printf("ihaha %d - Time: %lu\n",countIhaha, xTaskGetTickCount());
        countIhaha++;
        if (countIhaha >= 5) {
            // Dừng bộ hẹn giờ
            printf("ihaha stop\n");
            xTimerStop(xTimer, portMAX_DELAY);
        }
    }
}

void app_main(void) {
    // Tạo bộ hẹn giờ cho "ahihi"
    TimerHandle_t xTimerAhihi = xTimerCreate("TimerAhihi", 2000, pdTRUE, (void *)1, TimerCallback);
    if (xTimerAhihi != NULL) {
        // Bắt đầu bộ hẹn giờ cho "ahihi"
        xTimerStart(xTimerAhihi, portMAX_DELAY);
    }

    // Tạo bộ hẹn giờ cho "ihaha"
    TimerHandle_t xTimerIhaha = xTimerCreate("TimerIhaha", 3000, pdTRUE, (void *)2, TimerCallback);
    if (xTimerIhaha != NULL) {
        // Bắt đầu bộ hẹn giờ cho "ihaha"
        xTimerStart(xTimerIhaha, portMAX_DELAY);
    }

    // Dừng Task Scheduler vì đã tạo xong timer
    vTaskDelete(NULL);
}
