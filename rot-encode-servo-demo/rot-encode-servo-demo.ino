/*
  Rotary Encoder with Servo Motor Demo
  rot-encode-servo-demo.ino
  Demonstrates operation of Rotary Encoder
  Positions Servo Motor
  Displays results on Serial Monitor
  DroneBot Workshop 2019
  https://dronebotworkshop.com
*/

// Include the Servo Library
#include <Servo.h>

// Rotary Encoder Inputs
#define inputCLK 4
#define inputDT 5

// Create a Servo object
Servo myservo;

int counter = 0;
int currentStateCLK;
int previousStateCLK;

void setup() {

  // Set encoder pins as inputs
  pinMode (inputCLK, INPUT);
  pinMode (inputDT, INPUT);

  // Setup Serial Monitor
  Serial.begin (9600);

  // Attach servo on pin 9 to the servo object
  myservo.attach(9);

  // Read the initial state of inputCLK
  // Assign to previousStateCLK variable
  previousStateCLK = digitalRead(inputCLK);

}

void loop()

// Read the current state of inputCLK
currentStateCLK = digitalRead(inputCLK);

// If the previous and the current state of the inputCLK are different then a pulse has occured
if (currentStateCLK != previousStateCLK) {

  // If the inputDT state is different than the inputCLK state then
  // the encoder is rotating counterclockwise
  if (digitalRead(inputDT) != currentStateCLK) {
    counter --;
    if (counter < 0) {
      counter = 0;
    }

  } else {
    // Encoder is rotating clockwise
    counter ++;
    if (counter > 180) {
      counter = 180;
    }

  }

  // Move the servo
  myservo.write(counter);

  Serial.print("Position: ");
  Serial.println(counter);
}
// Update previousStateCLK with the current state
previousStateCLK = currentStateCLK;
}
