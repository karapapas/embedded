void requestConfiguration() {
  client.publish(topicControl, CMD_REQUEST_CONFIG);                 // After each mqtt server connection and after subscription to topics, publish sendConfig to control topic.
  msg_print(topicControl, CMD_REQUEST_CONFIG, OUTGOING);
}

void resetMeasurementParams(String message) {
  measurementDelay  = message.substring(0, 2).toInt() * 1000;
  topTemp = message.substring(2, 4).toInt();
  topHum = message.substring(4).toInt();
}

void getReadings() {  

  currentTemp = dht.readTemperature();
  currentHum = dht.readHumidity();

  Serial.print("T: ");
  Serial.print(currentTemp,1);             // Display values with one decimal point.
  Serial.print(" H: ");
  Serial.print(currentHum,1);
  Serial.print(" Current Delay: ");
  Serial.println(measurementDelay);

  if (isnan(currentTemp) || isnan(currentHum)) {      // Check if any of the two readings fail exit function.
    currentTemp = 0;
    currentHum = 0;
    return;
  }

  if (currentTemp > topTemp) {              // Compare measured temperature with threshold
    Serial.println("Temperature High");
  }

  if (currentHum > topHum) {                // Compare measured humidity with threshold
    Serial.println("Humidity High");
  }
  
}
