void topicSubscribe() {
sprintf(topicControl, "%s/%s", MQTT_CLIENT, MQTT_TOPIC_CONTROL);    // Format the string of the names of the topics that we will subscribe.
sprintf(topicData, "%s/%s", MQTT_CLIENT, MQTT_TOPIC_DATA);
sprintf(topicDataCrc, "%s/%s", MQTT_CLIENT, MQTT_TOPIC_DATACRC);

  if (client.connected()) {
    Serial.print("Subscribed to MQTT topics: [");

    client.subscribe(topicControl);                     // Subscribe to control to listen for the "startMeasurement", "crcError", "updateConfig" commands
    client.subscribe(topicData);                        // Subscribe to data to listen for measurement parameters

    Serial.print(topicData);
    Serial.print("] and [");
    Serial.print(topicControl);
    Serial.println("]");
    
//    Serial.println(millis());   // measure time cost of  client.loop() == 1 millisecond
    client.loop();
//    Serial.println(millis());
  }
}
