// SSR relay
int relayPin = D3;// set pin 8 for relay output
int flowSensorPin = A0;
volatile int flow_frequency; // Measures flow sensor pulses
// Calculated litres/hour
float vol = 0.0,l_minute;
unsigned long currentTime;
unsigned long cloopTime;
const int requiredFlow = 1;
int val;

ICACHE_RAM_ATTR void flow () // Interrupt function
{
   flow_frequency++;
}

// setup code for Robojax Solid State Relay
void setup() {
    // initialize serial communication at 9600 bits per second:
  Serial.begin(19200);
  pinMode(relayPin, OUTPUT);
  pinMode(flowSensorPin, INPUT);
  digitalWrite(flowSensorPin, HIGH); // Optional Internal Pull-Up
  digitalWrite(relayPin, LOW); //relay turned off initially
  attachInterrupt(digitalPinToInterrupt(flowSensorPin), flow, RISING); // Setup Interrupt
  Serial.println("Water Flow Meter");
  currentTime = millis();
  cloopTime = currentTime;
}

// loop code for Robojax Solid State Relay
void loop() {
  currentTime = millis();
  // Every second, calculate and print litres/hour
  if(currentTime >= (cloopTime + 1000))
  {
    cloopTime = currentTime; // Updates cloopTime
    val = analogRead(flowSensorPin);  // read the input pin
    Serial.print("Analog: ");
    Serial.println(val); 
    Serial.print("Freq: ");
    Serial.println(flow_frequency);
    if(flow_frequency != 0){
      // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min.
      l_minute = (flow_frequency / 7.5); // (Pulse frequency x 60 min) / 7.5Q = flowrate in L/hour
      l_minute = l_minute/60;    
      if (l_minute >= requiredFlow) {
        digitalWrite(relayPin, HIGH);
      } else {
        digitalWrite(relayPin, LOW);
      }
      vol = vol +l_minute;
      flow_frequency = 0; // Reset Counter
      Serial.print(l_minute, DEC); // Print litres/hour
      Serial.println(" L/Sec");
      Serial.print(vol, DEC);
      Serial.println(" L");
    }
    else {
      Serial.println(" flow rate = 0 ");
      digitalWrite(relayPin, LOW);
    }
  }
}
