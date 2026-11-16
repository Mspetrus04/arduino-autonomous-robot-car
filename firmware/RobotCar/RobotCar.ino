
#include <Arduino.h>
#include <Servo.h>

/*
 * Arduino Autonomous Robot Car - v1.0
 *
 * Hardware:
 * - Arduino Uno R3
 * - L298N motor driver
 * - HC-SR04 ultrasonic sensor
 * - SG90 servo
 *
 * Features:
 * - Autonomous forward movement
 * - Ultrasonic obstacle detection
 * - Left/right environmental scanning
 * - Basic obstacle avoidance
 *
 * Status: Experimental
 */

// ============================================
// PIN CONFIGURATION
// ============================================

// Motor A - Right wheel
const uint8_t ENA = 3;
const uint8_t IN1 = 6;
const uint8_t IN2 = 9;

// Motor B - Left wheel
const uint8_t ENB = 5;
const uint8_t IN3 = 10;
const uint8_t IN4 = 11;

// Ultrasonic sensor
const uint8_t TRIG_PIN = A1;
const uint8_t ECHO_PIN = A0;

// Servo
const uint8_t SERVO_PIN = 4;
Servo scanner;

// ============================================
// CONFIGURATION
// ============================================

const int MOTOR_SPEED = 140;
const int TURN_SPEED = 140;

const int SAFE_DISTANCE = 35; // cm
const int TURN_CLEARANCE = 35;

const int CENTER_ANGLE = 90;
const int LEFT_ANGLE = 150;
const int RIGHT_ANGLE = 30;

const unsigned long TURN_DURATION = 400;
const unsigned long SCAN_DELAY = 450;

// Adjust these if your motors are reversed
const bool REVERSE_RIGHT_MOTOR = false;
const bool REVERSE_LEFT_MOTOR = false;

// ============================================
// MOTOR CONTROL
// ============================================

void stopMotors() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void setMotors(int right, int left) {
  right = constrain(right, -255, 255);
  left = constrain(left, -255, 255);

  if (REVERSE_RIGHT_MOTOR) right = -right;
  if (REVERSE_LEFT_MOTOR) left = -left;

  // Disable PWM before changing direction
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  digitalWrite(IN1, right > 0 ? HIGH : LOW);
  digitalWrite(IN2, right < 0 ? HIGH : LOW);

  digitalWrite(IN3, left > 0 ? HIGH : LOW);
  digitalWrite(IN4, left < 0 ? HIGH : LOW);

  analogWrite(ENA, abs(right));
  analogWrite(ENB, abs(left));
}

void moveForward() {
  setMotors(MOTOR_SPEED, MOTOR_SPEED);
}

void turnLeft() {
  setMotors(TURN_SPEED, -TURN_SPEED);
}

void turnRight() {
  setMotors(-TURN_SPEED, TURN_SPEED);
}

// ============================================
// ULTRASONIC SENSOR
// ============================================

long readDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  unsigned long duration =
      pulseIn(ECHO_PIN, HIGH, 30000UL);

  // Invalid or missing echo
  if (duration == 0) return -1;

  long distance = duration / 58;

  if (distance < 2 || distance > 400) {
    return -1;
  }

  return distance;
}

// ============================================
// SERVO SCANNING
// ============================================

long scanDirection(int angle) {
  scanner.write(angle);
  delay(SCAN_DELAY);

  return readDistance();
}

// ============================================
// OBSTACLE AVOIDANCE
// ============================================

void avoidObstacle() {
  stopMotors();

  Serial.println("Obstacle detected!");
  Serial.println("Scanning surroundings...");

  // Scan both directions
  long leftDistance = scanDirection(LEFT_ANGLE);
  long rightDistance = scanDirection(RIGHT_ANGLE);

  // Return servo to center
  scanner.write(CENTER_ANGLE);
  delay(350);

  Serial.print("Left: ");
  Serial.print(leftDistance);
  Serial.print(" cm | Right: ");
  Serial.println(rightDistance);

  // Stop if a measurement is invalid
  if (leftDistance < 0 || rightDistance < 0) {
    Serial.println("Scan failed.");
    stopMotors();
    return;
  }

  // No clear direction
  if (leftDistance < TURN_CLEARANCE &&
      rightDistance < TURN_CLEARANCE) {
    Serial.println("Both sides blocked.");
    stopMotors();
    return;
  }

  // Turn toward the clearer direction
  if (leftDistance > rightDistance) {
    Serial.println("Turning left.");
    turnLeft();
  } else {
    Serial.println("Turning right.");
    turnRight();
  }

  delay(TURN_DURATION);

  stopMotors();
  delay(250);
}

// ============================================
// SETUP
// ============================================

void setup() {
  Serial.begin(9600);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stopMotors();

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  digitalWrite(TRIG_PIN, LOW);

  scanner.attach(SERVO_PIN);
  scanner.write(CENTER_ANGLE);

  Serial.println("========================");
  Serial.println(" Autonomous Robot v1.0");
  Serial.println("========================");

  delay(5000);
}

// ============================================
// MAIN LOOP
// ============================================

void loop() {
  long distance = readDistance();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance < 0) {
    // Stop when sensor data is unreliable
    stopMotors();
    Serial.println("Sensor error - STOP");
  }
  else if (distance <= SAFE_DISTANCE) {
    avoidObstacle();
  }
  else {
    moveForward();
    Serial.println("Path clear.");
  }

  delay(100);
}
