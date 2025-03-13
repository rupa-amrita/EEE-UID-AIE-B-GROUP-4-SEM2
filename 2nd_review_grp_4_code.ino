#define PIR_SENSOR 4      // PIR Sensor connected to GPIO4
#define IR_SENSOR 5       // IR Sensor connected to GPIO5
#define LED_LIGHT 18      // LED Street Light on GPIO18

unsigned long lightOnTime = 0; // Stores last time motion was detected
const int lightDelay = 5000;   // Light stays ON for 5 seconds

void setup() {
  Serial.begin(115200);         // Start Serial Monitor
  pinMode(PIR_SENSOR, INPUT);   // PIR sensor as input
  pinMode(IR_SENSOR, INPUT);    // IR sensor as input
  pinMode(LED_LIGHT, OUTPUT);   // LED as output
  digitalWrite(LED_LIGHT, LOW); // Initially OFF
}

void loop() {
  int pirState = digitalRead(PIR_SENSOR); // Read PIR Sensor
  int irState = digitalRead(IR_SENSOR);   // Read IR Sensor
  unsigned long currentTime = millis();   // Get current time

  // If motion or obstacle detected, turn ON the light
  if (pirState == HIGH || irState == HIGH) {
    Serial.println("Motion Detected! Turning ON Street Light.");
    digitalWrite(LED_LIGHT, HIGH); // Turn ON LED
    lightOnTime = currentTime;     // Update last detection time
  }

  // Keep the light ON for some time even if no motion
  if (currentTime - lightOnTime > lightDelay) {
    Serial.println("No Motion. Turning OFF Street Light.");
    digitalWrite(LED_LIGHT, LOW); // Turn OFF LED
  }

  delay(100); // Small delay to prevent false triggers
}
