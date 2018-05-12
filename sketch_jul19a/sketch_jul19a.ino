#include <Servo.h>
Servo testServo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); //sets up serial monitor
  Serial.println("Servo test code starting...");
  testServo.attach(8); //assigns servo to Digital Port #8
}

void loop() {
  // put your main code here, to run repeatedly:
  testServo.write(0); //go to specified angle in degrees
  delay(1000);
  testServo.write(180);
  delay(1000);
}
