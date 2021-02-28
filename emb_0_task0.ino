void task0(void *pvParameters) {
  
  dht.begin();
  ThingSpeak.begin(connectionForThingSpeak);


  for (;;) {
    long currentTime = millis();  // milliseconds since esp boot
    long durationSendData = currentTime - lastTimeSendData;

    if (measure == 1 ) {
      getReadings();                                              // Get readings from sensor.
      if(durationSendData >= 15000){
        postData();
//        Serial.println("duration between requests to thingspeak: ");
//        Serial.println(durationSendData);           
        lastTimeSendData = currentTime;
      }
      delay(measurementDelay);
    } else {
      delay(1000);
    }
    
  }

}
