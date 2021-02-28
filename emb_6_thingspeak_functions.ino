void postData() {

    ThingSpeak.setField(1, float(currentTemp));
    ThingSpeak.setField(2, float(currentHum));
    
    int x = ThingSpeak.writeFields(myIotChannel, myIotApiKeyWrite);
    
    if (x == 200) {
      Serial.println("Success: Channel update two fields simultaneously with success.");
    } else if (abs(x) == 401) {
      Serial.println("ThingSpeak does not accept so frequent updates. At least 15 sec must pass between REST calls.");
    }
    else {
      Serial.println("Error: Problem updating channel. HTTP error code " + String(x));
    }

    
}
