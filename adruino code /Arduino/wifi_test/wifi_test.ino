#include <ESP8266WiFi.h>

WiFiServer wifiServer(80);

const char* ssid = "Terminator";
const char* password = "Copperstone@007";

void setup() {
  Serial.begin(19200);
  delay(1000);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }
  Serial.print("Connected to WiFi. IP: ");
  Serial.println(WiFi.localIP());
  wifiServer.begin();

}

void loop() {
  WiFiClient client = wifiServer.available();
  if(client) {
    while(client.connected()) {
      while(client.available()>0) {
        char c = client.read();
        Serial.write(c);
      }
      delay(10);
    }
    client.stop();
    Serial.println("Client disconnected");
  }
}
