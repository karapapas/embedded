void sorting(char* topic, byte* payload, unsigned int length) {

  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;
  String message(p);
  String topic_str(topic);
  String reply;
  String msg_direction; // To be passed to the msg_print function

  if (topic_str == topicControl) {
    if (message == CMD_UPDATE) {
      measure = 0;
      msg_print(topic_str, message, INCOMING);
      requestConfiguration();                                           // In case we receive updateConfig request config
    } else if (message == CMD_MEASURE) {
      msg_print(topic_str, message, INCOMING);
      measure = 1;
    } else if (message == CMD_CRC_ERROR) {
      measure = 0;
      msg_print(topic_str, message, INCOMING);
      Serial.println("Error in Crc8 process. System will reboot in 5 seconds");
      delay(5000);
      setup();
    }
  } else if (topic_str == topicData) {
    measure = 0;
    msg_print(topic_str, message, INCOMING);                          // Inform user for the recieved 6digit message
    resetMeasurementParams(message);                                  // Reset Delay and TOPs
    reply = convertMessageToCrc8Format(message);                      // Convert 6digit params to 9digit crc8 params
    char replyInCrc8Format[50];                                       // Declare a local Char Array
    reply.toCharArray(replyInCrc8Format, 50);                         // Convert String to Char Array to be used in Publish
    client.publish(topicDataCrc, replyInCrc8Format);                  // Send the 9digit Crc8 params to topic data crc
    msg_print(topicDataCrc, replyInCrc8Format, OUTGOING);             // Inform the user for the publish
  }
}
