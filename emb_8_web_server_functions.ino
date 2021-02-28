void handle_OnConnect() {
  Serial.println("someone connected to /");
  serverObj.send(200, "text/html", "You connected in root path /");
}

void handle_NotFound() {
  serverObj.send(404, "text/plain", "Not found");
}

void handle_HumidityHigh() {
  Serial.println("A GET request was received to alarm-humidity-on");
  serverObj.send(200, "text/html", "Request to switch on received with success!");
  digitalWrite(outputPin, HIGH);
}

void handle_HumidityNormal() {
  Serial.println("A GET request was received to alarm-humidity-off");
  serverObj.send(200, "text/html", "Request to switch off received with success!");
  digitalWrite(outputPin, LOW);
}
