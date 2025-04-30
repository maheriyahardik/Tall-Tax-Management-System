#include <Servo.h>  // Includes the Servo library

Servo servo;
int trig = 5;       // Pin for triggering the ultrasonic sensor
int echo = 6;       // Pin for receiving the echo signal
int servoPin = 9;   // Pin to control the servo motor
long Duration, Distance, Average;
long aver[3];       // Array to store distance readings for averaging

void setup() {
  Serial.begin(9600);
  servo.attach(servoPin);   // Attach servo once at start
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  servo.write(0);           // Initialize with the lid closed
  delay(1000);
}

void measure() {
  digitalWrite(trig, LOW);
  delayMicroseconds(5);
  digitalWrite(trig, HIGH);
  delayMicroseconds(15);
  digitalWrite(trig, LOW);
  Duration = pulseIn(echo, HIGH);  // Measure the time taken by the echo
  Distance = (Duration / 2) / 29.1; // Convert time to distance in centimeters
}

void loop() {
  for (int i = 0; i <= 2; i++) {
    measure();
    aver[i] = Distance;
    delay(10);
  }
  
  Average = (aver[0] + aver[1] + aver[2]) / 3; // Average of 3 measurements
  Serial.print("Distance: ");
  Serial.print(Average);
  Serial.println(" cm");

  if (Average < 10) { // If object detected within 10 cm
    servo.write(90);  // Open lid (or gate)
    delay(3000);      // Stay open for 3 seconds
    servo.write(0);   // Close lid
    delay(1000);      // Delay to allow lid to close
  }

  delay(100); // Small delay to avoid rapid looping
}
