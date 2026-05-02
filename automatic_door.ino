#include <Servo.h>

Servo gateServo;

// Pins
const int irPin = 2;
const int ledPin = 13;
const int servoPin = 6;

int count = 0;
bool detected = false;

void setup() {
  pinMode(irPin, INPUT);
  pinMode(ledPin, OUTPUT);
  
  gateServo.attach(servoPin);
  Serial.begin(9600);
}

void loop() {
  int irState = digitalRead(irPin);

  // Detect hand (only once per movement)
  if (irState == HIGH && detected == false) {
    count++;
    detected = true;

    Serial.print("Count: ");
    Serial.println(count);

    delay(400); // debounce
  }

  // Reset when hand removed
  if (irState == LOW) {
    detected = false;
  }

  //  Action after 2 detections
  if (count == 2) {
    Serial.println("Action Triggered!");

    digitalWrite(ledPin, HIGH);
    gateServo.write(90); // open

    delay(3000);

    digitalWrite(ledPin, LOW);
    gateServo.write(0); // close

    count = 0; // reset
  }
}