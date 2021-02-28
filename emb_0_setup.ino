void setup() {
  Serial.begin(115200);
  

  xTaskCreatePinnedToCore(
    task0, /* Task function. */
    "task..0",   /* name of task. */
    100000,     /* Stack size of task */
    NULL,      /* parameter of the task */
    2,         /* priority of the task */
    &taskHandlerZero,    /* Task handle to keep track of created task */
    0);        /* pin task to core 0 */
  Serial.println("Task 0 running..");
  delay(500);

  xTaskCreatePinnedToCore(
    task1,  /* Task function. */
    "task.. 1",    /* name of task. */
    100000,      /* Stack size of task. default 10000 */
    NULL,       /* parameter of the task */
    1,          /* priority of the task */
    &taskHandlerOne,     /* Task handle to keep track of created task */
    1);         /* pin task to core 0 */

  Serial.println("Task 1 running..");
}

void loop() {}
