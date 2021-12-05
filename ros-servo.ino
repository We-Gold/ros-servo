#include <Servo.h>

Servo servo9;

int position = 0;

void setup() {
  Serial.begin(9600);

  servo9.attach(9);
}

void loop() {
  // Update the servo if there is a message
  if(Serial.available() > 0) {
    String message = Serial.readStringUntil('\n');

    position = message.toInt();

    servo9.write(position);
  }
}
