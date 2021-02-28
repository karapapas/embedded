void mqttReconnect() {

  while (!client.connected()) {                                       // Loop until we're reconnected.
    Serial.print("Attempting MQTT connection...");
    
    if(client.connect(MQTT_CLIENT, "samos", "karlovasi33#")) {
      Serial.println("MQTT connected");
      topicSubscribe();                                               // If successfully connected to Mqtt server, subscribe to topics.
    }    
    else{
      Serial.print("failed, rc= ");
      Serial.println(client.state());                                 // Provides info for the state of the connection.

      delay(5000);                                                    // Wait 5 seconds before retrying.
    }
  }
}
