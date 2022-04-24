int relayState = 0;
const int relayPin = D1; // Board Pin: D8->D3/D9

void setup() {
  Serial.begin(19200);
  pinMode(relayPin, OUTPUT); 
  digitalWrite(relayPin, LOW);
}

// loop() will run continously on the Arduino
void loop(void){
  if(relayState) {
    digitalWrite(relayPin, LOW);
    relayState = 0;
  } else {
    digitalWrite(relayPin, HIGH);
    relayState = 1;
  }
  delay(2000);
  
}
