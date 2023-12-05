#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <inttypes.h>  
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

QueueHandle_t requestQueue;


typedef struct {
    int taskId;
    int executionTime;  
    int numTask;
} TaskRequest_1;

typedef struct {
    int taskId;
    int executionTime;
    int numTask;  
} TaskRequest_2;

typedef struct {
    int taskId;
    int executionTime;  
    int numTask;
} TaskRequest_3;

typedef struct {
    int taskId;
    int executionTime;  
    int numTask;
} TaskRequest_4;

typedef struct {
    int taskId;
    int executionTime;  
    int numTask;
} TaskRequest;


void functionTask_1(TaskRequest request) {
    vTaskDelay(request.executionTime);
    uint32_t finishTime = xTaskGetTickCount();
    printf("Task 1.%d finished at time %" PRIu32 "\n", request.numTask, finishTime);
    vTaskDelay(5);
}

void functionTask_2(TaskRequest request) {
    vTaskDelay(request.executionTime);
    uint32_t finishTime = xTaskGetTickCount();
    printf("Task 2.%d finished at time %" PRIu32 "\n", request.numTask, finishTime);
    vTaskDelay(5);
}

void functionTask_3(TaskRequest request) {
    vTaskDelay(request.executionTime);
    uint32_t finishTime = xTaskGetTickCount();
    printf("Task 3.%d finished at time %" PRIu32 "\n", request.numTask, finishTime);
    vTaskDelay(5);
}

void receptionTask(void *parameter) {
        TaskRequest_1 request1;
        TaskRequest_2 request2;
        TaskRequest_3 request3;
        TaskRequest_4 request4;
        request1.numTask = 0;
        request2.numTask = 0;
        request3.numTask = 0;
    while (1) {
        if( (rand() % 4 + 1) ==1){
          request1.taskId =1;
          request1.numTask+=1;
          request1.executionTime = rand() % 1000;
          uint32_t enqueueTime = xTaskGetTickCount();  // Thời điểm task được đưa vào hàng đợi
          xQueueSend(requestQueue, &request1, portMAX_DELAY);
          printf("Task %d.%d enqueued at time %" PRIu32 "\n", request1.taskId,request1.numTask, enqueueTime);
           vTaskDelay(5);
        }

        if((rand() % 4 + 1) ==2){
          request2.taskId =2;
          request2.numTask+=1;
          request2.executionTime = rand() % 1000;
          uint32_t enqueueTime = xTaskGetTickCount();  // Thời điểm task được đưa vào hàng đợi
          xQueueSend(requestQueue, &request2, portMAX_DELAY);
          printf("Task %d.%d enqueued at time %" PRIu32 "\n", request2.taskId,request2.numTask, enqueueTime);
          vTaskDelay(5);
        }
        
        if( (rand() % 4 + 1) ==3){
          request3.taskId =3;
          request3.numTask+=1;
          request3.executionTime = rand() % 1000;
          uint32_t enqueueTime = xTaskGetTickCount();  // Thời điểm task được đưa vào hàng đợi
          xQueueSend(requestQueue, &request3, portMAX_DELAY);
          printf("Task %d.%d enqueued at time %" PRIu32 "\n", request3.taskId,request3.numTask, enqueueTime);
          vTaskDelay(5);
        }

        if( (rand() % 4 + 1) == 4){
          request4.taskId =4;
          request4.numTask+=1;
          request4.executionTime = rand() % 1000;
          uint32_t enqueueTime = xTaskGetTickCount();  // Thời điểm task được đưa vào hàng đợi
          xQueueSend(requestQueue, &request4, portMAX_DELAY);
          printf("Task %d.%d enqueued at time %" PRIu32 "\n", request4.taskId,request4.numTask, enqueueTime);
          vTaskDelay(5);
        }
        vTaskDelay((rand() % 1000));  // Tạo delay giữa các lần enqueue
    }
}

void controller(){
    while (1) {
        // Wait for a task to be available in the queue
        TaskRequest request;

        if (xQueueReceive(requestQueue, &request, portMAX_DELAY)) {
          if(request.taskId == 1){
            printf("Processing Task 1: %d.%d at time %" PRIu32 "\n", request.taskId,request.numTask,xTaskGetTickCount());
            vTaskDelay(5);
            functionTask_1(request);
          }
          if(request.taskId == 2){
            printf("Processing Task 2: %d.%d at time %" PRIu32 "\n", request.taskId,request.numTask,xTaskGetTickCount());
            vTaskDelay(5);
            functionTask_2(request);
          }
          if(request.taskId == 3){
            printf("Processing Task 3: %d.%d at time %" PRIu32 "\n", request.taskId,request.numTask,xTaskGetTickCount());
            vTaskDelay(5);
            functionTask_3(request);
          }
          if(request.taskId == 4){
            vTaskDelay(5);
            printf("ERROR TASK\n");

          }
          vTaskDelay(50);
        } 
    }
}




void app_main() {
    srand(time(NULL));
    
    requestQueue = xQueueCreate(10, sizeof(TaskRequest_1));

    xTaskCreate(receptionTask, "ReceptionTask", 10000, NULL, 1, NULL);
    xTaskCreate(controller, "ControllerTask", 10000, NULL, 2, NULL);
}
