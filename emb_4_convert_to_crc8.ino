String convertMessageToCrc8Format(String message){
  String reply;
    
  int Delay = Compute_CRC8_Simple_OneByte(message.substring(0, 2).toInt());

  int Temp = Compute_CRC8_Simple_OneByte(message.substring(2, 4).toInt());

  int Hum = Compute_CRC8_Simple_OneByte(message.substring(4).toInt());

  client.loop();                           

  reply = reply + ((Delay  <100)  ? ("0" + String(Delay)) :String(Delay));
  reply = reply + ((Temp   <100)  ? ("0" + String(Temp))  :String(Temp));
  reply = reply + ((Hum    <100)  ? ("0" + String(Hum))   :String(Hum));

  return reply;
}


static byte Compute_CRC8_Simple_OneByte(byte byteVal){
  
  const byte generator = 0x04;
  byte crc = byteVal;                                       // init crc directly with input byte instead of 0, avoid useless 8 bitshifts until input byte is in crc register
  
  for (int i = 0; i < 8; i++){
      if ((crc & 0x80) != 0){
          crc = (byte)((crc << 1) ^ generator);             // most significant bit set, shift crc register and perform XOR operation, taking not-saved 9th set bit into account
      }
      else{
          crc <<= 1;                                        // most significant bit not set, go to next bit
      }
      client.loop();                           // Must include it in every loop so that we won't loose connection with the mqtt server.
  }
  
  return crc;
}
