// Loading required libraries
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// Loading web page
#include "index.h"


// Storing network credentials for arduino to connect
const char* ssid     = "Terminator";
const char* password = "Copperstone@007";

// Set web server port number to 80
ESP8266WebServer server(80);

// Pin numbers for the devices
const int trigPin = D4; //Board Pin: D9
const int echoPin = D3; //Board Pin: D8

//define sound velocity in cm/uS
#define SOUND_VELOCITY 0.034

long duration;
float distanceCm;
int fillPercentage;
float waterLevel;

// Constant tank size values
const int tankHeight = 20; //in cms
const int tankCapacity = 1; //in litres
const float tankPerCMHeightWaterCapacity = (float)tankCapacity/tankHeight;

// initPins() initializes the required configurations
void initPins() {
  // Initialize serial monitor for output  
  Serial.begin(19200);
  // Set pin modes
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
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
  server.on("/getTankPercentageLevel", getTankPercentageLevel); //ajax request
  server.on("/getTankWaterLevel", getTankWaterLevel); //ajax request
  server.on("/refreshValues", refreshValues); //ajax request
  server.begin(); //Starting server
}

// ------------------------- Helper functions ---------------------

void readAndParseSensor() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_VELOCITY/2;

  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
}

void calculateCurrentWaterLevel() {
  waterLevel = (tankHeight-distanceCm)*tankPerCMHeightWaterCapacity;
  if (waterLevel < 0) {
    waterLevel = tankCapacity;
  }
  Serial.print("Water Level: ");
  Serial.println(waterLevel);
  Serial.print("Per cm Level: ");
  Serial.println(tankPerCMHeightWaterCapacity);
}

void calculateCurrentTankPercentage() {
  fillPercentage = 100 - ((distanceCm/tankHeight)*100);
  if (fillPercentage < 0) {
    fillPercentage = 100;
  }
  Serial.print("Fill percentage: ");
  Serial.println(fillPercentage);
}

// ------------------------ Web Page request handling functions ----------------------------

// handleRoot() will display the home page
void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}

// refreshValues() reads the sensor value on request
void refreshValues() {
  readAndParseSensor();
  calculateCurrentTankPercentage();
  calculateCurrentWaterLevel();
  server.send(200, "text/plane", "Refreshed");
}

// getTankPercentageLevel() send the tank fill percentage
void getTankPercentageLevel() {
  String fillPercentageString = String(fillPercentage);
  server.send(200, "text/plane", fillPercentageString);
}

// getTankWaterLevel() send the water level in litres
void getTankWaterLevel() {
  String waterLevelString = String(waterLevel);
  server.send(200, "text/plane", waterLevelString);
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
void loop() {
  // Listening to the client
  server.handleClient();
  delay(1);
}
