// Sensor pins
#define sensorPower 7
#define sensorPin A0

// Value for storing water level
int val = 0;

/* Change these values based on your calibration */
int lowerThreshold = 200;
int upperThreshold = 400;

void setup() {
  Serial.begin(9600);
  pinMode(sensorPower, OUTPUT);
  digitalWrite(sensorPower, LOW); // Turn off sensor initially
}

void loop() {
  int level = readSensor();

  if (level == 0) {
    Serial.println("Water Level: Empty");
  } else if (level > 0 && level <= lowerThreshold) {
    Serial.println("Water Level: Low");
  } else if (level > lowerThreshold && level <= upperThreshold) {
    Serial.println("Water Level: Medium");
  } else if (level > upperThreshold) {
    Serial.println("Water Level: High");
  }

  delay(1000); // Wait 1 second before next reading
}

// Function to read sensor value
int readSensor() {
  digitalWrite(sensorPower, HIGH);   // Turn sensor ON
  delay(10);                         // Wait for stable reading
  val = analogRead(sensorPin);      // Read the value
  digitalWrite(sensorPower, LOW);   // Turn sensor OFF
  return val;
}
