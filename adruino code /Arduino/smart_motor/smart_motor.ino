// Loading required libraries
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// Loading web page
#include "index.h"
//define sound velocity in cm/uS
#define SOUND_VELOCITY 0.034

// Storing network credentials for arduino to connect
const char* ssid     = "Terminator";
const char* password = "Copperstone@007";

// Pin numbers for the devices
const int relayPin = D1; // D3
const int flowSensorPin = D4; // Board Pin: D9
// Pin for the ultrasonic sensor
const int trigPin = D2; //Board Pin: D14
const int echoPin = D6; //Board Pin: D12

// ---------- Variables for Flow sensor ----------
// Variables to store flow sensor inputs
volatile int flow_frequency; // Measures flow sensor pulses
int l_hour = 0; // Calculated litres/hour
float vol = 0.0;

// Min required water flow
const int minRequiredFlow = 100;

// Max time to wait to cut-off relay if the flow is below the required level (in minutes)
const int maxWaitTime = 1;

// ----------- Variables for Ultrasonic sensor ----------
long duration;
float distanceCm;
int fillPercentage;
float waterLevel;

// Constant tank size values
int tankHeight = 20; //in cms
int tankCapacity = 1; //in litres
float tankPerCMHeightWaterCapacity = (float)tankCapacity/tankHeight;

// Set web server port number to 80
ESP8266WebServer server(80);


// Auxiliar variables to store the current relay state
String relayState = "off";

// Previous time
unsigned long previousTime = 0; 
// Min required waiting time in miliseconds
const long timeoutTime = maxWaitTime * 60 * 1000 ;

int cutOffWatch = 0;


// -------------------- Initialisation functions -------------------------

// initPins() initializes the required configurations
void initPins() {
  // Initialize serial monitor for output  
  Serial.begin(19200);
  // Set pin Modes
  pinMode(relayPin, OUTPUT); //Setting relayPin with Output mode 
  pinMode(flowSensorPin, INPUT); // Setting flow sensor pin with input mode
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  // Set initial outputs
  digitalWrite(relayPin, LOW);
  digitalWrite(flowSensorPin, HIGH);
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
  server.on("/readFlowSensor", getFlowSensor); //This is flow sensor ajax request
  server.on("/handleRelay", handleRelay); //This is control relay ajax request
  server.on("/getRelayState", getRelayState); //This is to get current relay state ajax request
  server.on("/getTankPercentageLevel", getTankPercentageLevel); //ajax request
  server.on("/getTankWaterLevel", getTankWaterLevel); //ajax request
  server.on("/refreshValues", refreshValues); //ajax request
  server.on("/setTankCapacity", setTankCapacity); //ajax request
  server.begin(); //Starting server
}

// ------------------------- Helper functions ---------------------

// turnRelayOff() will turn the relay off
void turnRelayOff() {
  Serial.println("Turning Relay off");
  relayState = "off";
  digitalWrite(relayPin, LOW);
}

// turnRelayOn() will turn the relay on
void turnRelayOn() {
  Serial.println("Turning Relay on");
  relayState = "on";
  digitalWrite(relayPin, HIGH);
}

// handleAutoCutOff() will check whether to turn relay off if the conditions are met
void handleAutoCutOff() {
  if (relayState == "on") {
    if (l_hour < minRequiredFlow) {
      if (cutOffWatch) {
        if ((millis() - previousTime) > timeoutTime) {
          turnRelayOff();
          cutOffWatch = 0;
        } 
      } else {
        previousTime = millis();
        cutOffWatch = 1;
      }
    } else {
      cutOffWatch = 0;
    }
  }
}


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

// Interrupt function
ICACHE_RAM_ATTR void flow() {
   flow_frequency++;
}

// ------------------------ Web Page request handling functions ----------------------------
// handleRoot() will display the home page
void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}

// getFlowSensor() will get the flow sensor data
void getFlowSensor() {
  // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min.
  l_hour = (flow_frequency * 60 / 7.5); // (Pulse frequency x 60 min) / 7.5Q = flowrate in L/hour
  vol = vol + l_hour;
  flow_frequency = 0; // Reset Counter
  handleAutoCutOff();
  Serial.print(l_hour, DEC); // Print litres/hour
  Serial.println(" L/Sec");
  String sensor_value = String(l_hour);
  server.send(200, "text/plain", sensor_value); //Send Flow sensor value to client ajax request
}

// handleRelay() will handle the relay state
void handleRelay() {
  if (relayState == "off") {
    turnRelayOn();
  } else {
    turnRelayOff();
  }
  server.send(200, "text/plain", relayState);
}

// getRelayState() send the current relay state
void getRelayState() {
  server.send(200, "text/plain", relayState);
}

// refreshValues() reads the sensor value on request
void refreshValues() {
  readAndParseSensor();
  calculateCurrentTankPercentage();
  calculateCurrentWaterLevel();
  server.send(200, "text/plain", "Refreshed");
}

// getTankPercentageLevel() send the tank fill percentage
void getTankPercentageLevel() {
  String fillPercentageString = String(fillPercentage);
  server.send(200, "text/plain", fillPercentageString);
}

// getTankWaterLevel() send the water level in litres
void getTankWaterLevel() {
  String waterLevelString = String(waterLevel);
  server.send(200, "text/plain", waterLevelString);
}

void setTankCapacity() {

  tankHeight = 10;
  tankCapacity = 1;
  tankPerCMHeightWaterCapacity = (float)tankCapacity/tankHeight;
  server.send(200, "text/plain", "Value Updated");
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
  
  attachInterrupt(D4, flow, RISING); // Setup Interrupt
  sei(); // Enable interrupts
}

// loop() will run continously on the Arduino
void loop(void){
  // Listening to the client
  server.handleClient();
  delay(1);
}
