/* Change these values based on your calibration values */
int lowerThreshold = 400;
int upperThreshold = 520;

// Sensor pins
#define sensorPower 7
#define sensorPin A0

int IN1 = 5;
int Pin1 = A2;
float moistVal = 0; // value for storing soil moisture
int levelval = 0; // value for storing water level

// Declare pins to which LEDs are connected
int redLED = 2;
int yellowLED = 3;
int greenLED = 4;

void setup() {
  Serial.begin(9600);

  // Declare moisture sensor pins
  pinMode(IN1, OUTPUT);
  pinMode(Pin1, INPUT);

  // Declare water level sensor pins
  pinMode(sensorPower, OUTPUT);

  // Set LED pins as an OUTPUT
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

  // Initially turn off all LEDs
  digitalWrite(redLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(greenLED, LOW);

  digitalWrite(sensorPower, LOW);
  digitalWrite(IN1, HIGH);
  delay(500);
}

void loop() {
  int led = turnLED();
  int pump = powerPump();
  Serial.println();
  delay(1000);
}

int readLevel() {
  digitalWrite(sensorPower, HIGH);
  delay(10);
  levelval = analogRead(sensorPin);
  digitalWrite(sensorPower, LOW);
  return levelval;
}

int powerPump() {
  moistVal = analogRead(Pin1);
  int level = readLevel();

  Serial.print("Moisture level:");
  Serial.println(moistVal);

  if(level >= lowerThreshold) {
    if(moistVal > 410) {
      digitalWrite(IN1, LOW);
    } else {
      digitalWrite(IN1, HIGH);
    }
  } else {
    digitalWrite(IN1, HIGH);
  }
}

int turnLED(){
  int level = readLevel();

  if (level == 0) {
    Serial.println("Water Level: Empty");
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, LOW);
  }
  else if (level > 0 && level <= lowerThreshold) {
    Serial.println("Water Level: Low");
    digitalWrite(redLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, LOW);
  }
  else if (level > lowerThreshold && level <= upperThreshold) {
    Serial.println("Water Level: Medium");
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(greenLED, LOW);
  }
  else if (level > upperThreshold) {
    Serial.println("Water Level: High");
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, HIGH);
  }
}
