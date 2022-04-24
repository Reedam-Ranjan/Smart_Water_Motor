// Loading required libraries
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// Loading web page
#include "index.h"

// Storing network credentials for arduino to connect
const char* ssid     = "Terminator";
const char* password = "Copperstone@007";

// Pin numbers for the devices
const int relayPin = D3; // Board Pin: D8

// Set web server port number to 80
ESP8266WebServer server(80);

// Auxiliar variables to store the current relay state
String relayState = "off";

// -------------------- Initialisation functions -------------------------

// initPins() initializes the required configurations
void initPins() {
  // Initialize serial monitor for output  
  Serial.begin(19200);
  // Set pin Modes
  pinMode(relayPin, OUTPUT); //Setting relayPin with Output mode 
  // Set initial outputs
  digitalWrite(relayPin, HIGH);
}

// initWiFi() connects the Arduino to the wifi network
void initWiFi() {
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA); //Sets Wifi mode to connect to Wifi
  WiFi.begin(ssid, password);

  while(WiFi.waitForConnectResult() != WL_CONNECTED){      
      Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

// initServer() will start the server with required configuration
void initServer() {
  server.on("/", handleRoot);      //This is display page
  server.on("/handleRelay", handleRelay); //This is control relay ajax request
  server.on("/getRelayState", getRelayState); //This is to get current relay state ajax request
  server.begin(); //Starting server
}

// ------------------------- Helper functions ---------------------

// turnRelayOff() will turn the relay off
void turnRelayOff() {
  Serial.println("Turning Relay off");
  relayState = "off";
  digitalWrite(relayPin, HIGH);
}

// turnRelayOn() will turn the relay on
void turnRelayOn() {
  Serial.println("Turning Relay on");
  relayState = "on";
  digitalWrite(relayPin, LOW);
}

// ------------------------ Web Page request handling functions ----------------------------
// handleRoot() will display the home page
void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}

// handleRelay() will handle the relay state
void handleRelay() {
  if (relayState == "off") {
    turnRelayOn();
  } else {
    turnRelayOff();
  }
  server.send(200, "text/plane", relayState);
}

// getRelayState() send the current relay state
void getRelayState() {
  server.send(200, "text/plane", relayState);
}

// ----------------------- Arduino working functions ------------------------------

// setup() set ups initial configuration for the Arduino
void setup() {

  // Init configuration
  initPins();
  // Init WiFi
  initWiFi();  
  // Init Server
  initServer();
}

// loop() will run continously on the Arduino
void loop(void){
  // Listening to the client
  server.handleClient();
}
