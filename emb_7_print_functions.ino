void msg_print(String msg_topic, String msg_message, String msg_direction){
  if(msg_direction == INCOMING){
    Serial.print("<<<<< Received message: [");
    Serial.print(msg_message);
    Serial.print("] From: [");
    Serial.print(msg_topic);
    Serial.println("]");
  } else if (msg_direction == OUTGOING){
    Serial.print(">>>>> Published message: [");  
    Serial.print(msg_message);
    Serial.print("] To: [");
    Serial.print(msg_topic);
    Serial.println("]");
  }
}
