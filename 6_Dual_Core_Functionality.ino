/*
   This sketch runs a artificial load on both cores to measure maximum compute power of the ESP32
*/
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "soc/rtc_wdt.h"
#include "esp_int_wdt.h"
#include "esp_task_wdt.h"

unsigned long loops1 = 1000; unsigned long loops2 = 1000;
float t1;
int t2; int t3;

unsigned long qq = 0;
TaskHandle_t Task1, Task2;

void artificialLoad () {
  for ( long i = 0; i < loops1; i++) {
    for (long  j = 1; j < loops2; j++) {
      qq++;      t1 = 5000.0 * i;
      t2 = 150 * 1234 * i;
      t3 = j % 554 ;
    }
  }
}
void artificialLoad2 () {
  for ( long i = 0; i < loops1; i++) {
    for (long  j = 1; j < loops2; j++) {
      qq++;      t1 = 5000.0 * i;
      t2 = 150 * 1234 * i;
      t3 = j % 554 ;
    }
  }
}

void codeForTask1( void * parameter ) {

  esp_task_wdt_delete(NULL);
  //  vTaskSuspend(NULL);
  unsigned long i, j;
  for (;;) {
    //esp_task_wdt_init(30, false);
    long start = millis();
//    artificialLoad();
    Serial.print("Finish Task 1 which runs on Core ");
    Serial.print( xPortGetCoreID());
    Serial.print(" Time ");    Serial.println(millis() - start);
    //delay(1);
  }
}

void codeForTask2( void * parameter ) {

  esp_task_wdt_delete(NULL);

  for (;;) {
    //esp_task_wdt_init(30, false);
    long start = millis();
//    artificialLoad2();
    Serial.print("Finish Task 2 which runs on Core ");
    Serial.print( xPortGetCoreID());
    Serial.print(" Time ");    Serial.println(millis() - start);
    //delay(1);
  }
}

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  /*Syntax for assigning task to a core:
    xTaskCreatePinnedToCore(
                    coreTask,   // Function to implement the task
                    "coreTask", // Name of the task
                    10000,      // Stack size in words
                    NULL,       // Task input parameter
                    0,          // Priority of the task
                    NULL,       // Task handle.
                    taskCore);  // Core where the task should run
  */


  xTaskCreatePinnedToCore(    codeForTask1,    "led1Task",    1000,    NULL,    1,    &Task1,    0);
  delay(500);  // needed to start-up task1
  xTaskCreatePinnedToCore(    codeForTask2,    "led2Task",    1000,    NULL,    1,    &Task2,    1);
  delay(500);
  //  vTaskDelete(NULL);
  //vTaskSuspend(Task1);
}

void loop() {
  //  delay(1000);
}