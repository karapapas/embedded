void task1(void *pvParameters) {

  wifiConnect();
  mqttReconnect();                        // Connect to MQTT broker and subscribe to topics

  pinMode(outputPin, OUTPUT);
  digitalWrite(outputPin, LOW);

  // Web server controllers
  //----------------------------------
  serverObj.on("/", handle_OnConnect);
  serverObj.on("/alarm-humidity-on", handle_HumidityHigh);
  serverObj.on("/alarm-humidity-off", handle_HumidityNormal);
  serverObj.onNotFound(handle_NotFound);

  serverObj.begin();
  
  client.setCallback(sorting);
  requestConfiguration();

  for (;;) {
    if (WiFi.status() != WL_CONNECTED) {                        // Reconnect to WiFi if not connected
      wifiConnect();
    }

    if (!client.connected()) {                                  // Reconnect to MQTT broker if not connected
      mqttReconnect();
    }

    client.loop();                                              // Maintains connections, checks for incoming messages.
    serverObj.handleClient();                                   // Keep listening for incoming REST requests
    delay(1000);

  }
}
