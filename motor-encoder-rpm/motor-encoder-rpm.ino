/*
  Gearmotor Rotary Encoder Test
  motor-encoder-rpm.ino
  Read pulses from motor encoder to calculate speed
  Control speed with potentiometer
  Displays results on Serial Monitor
  Use Cytron MD10C PWM motor controller
  DroneBot Workshop 2019
  https://dronebotworkshop.com
*/

// Motor encoder output pulse per rotation (change as required)
#define ENC_COUNT_REV 374

// Encoder output to Arduino Interrupt pin
#define ENC_IN 3

// MD10C PWM connected to pin 10
#define PWM 10
// MD10C DIR connected to pin 12
#define DIR 12

// Analog pin for potentiometer
int speedcontrol = 0;

// Pulse count from encoder
volatile long encoderValue = 0;

// One-second interval for measurements
int interval = 1000;

// Counters for milliseconds during interval
long previousMillis = 0;
long currentMillis = 0;

// Variable for RPM measuerment
int rpm = 0;

// Variable for PWM motor speed output
int motorPwm = 0;

void setup()
{
  // Setup Serial Monitor
  Serial.begin(9600);

  // Set encoder as input with internal pullup
  pinMode(ENC_IN, INPUT_PULLUP);

  // Set PWM and DIR connections as outputs
  pinMode(PWM, OUTPUT);
  pinMode(DIR, OUTPUT);

  // Attach interrupt
  attachInterrupt(digitalPinToInterrupt(ENC_IN), updateEncoder, RISING);

  // Setup initial values for timer
  previousMillis = millis();
}

void loop()
{

  // Control motor with potentiometer
  motorPwm = map(analogRead(speedcontrol), 0, 1023, 0, 255);

  // Write PWM to controller
  analogWrite(PWM, motorPwm);

  // Update RPM value every second
  currentMillis = millis();
  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;


    // Calculate RPM
    rpm = (float)(encoderValue * 60 / ENC_COUNT_REV);

    // Only update display when there is a reading
    if (motorPwm > 0 || rpm > 0) {
      Serial.print("PWM VALUE: ");
      Serial.print(motorPwm);
      Serial.print('\t');
      Serial.print(" PULSES: ");
      Serial.print(encoderValue);
      Serial.print('\t');
      Serial.print(" SPEED: ");
      Serial.print(rpm);
      Serial.println(" RPM");
    }

    encoderValue = 0;
  }
}

void updateEncoder()
{
  // Increment value for each pulse from encoder
  encoderValue++;
}
