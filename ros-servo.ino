#include <Servo.h>
#include <StringSplitter.h>

const int numberOfServos = 2;
const char servoPositionDelimiter = ':';

int servoPins[numberOfServos] = {9, 10};

Servo servos[numberOfServos] = {Servo(), Servo()};

int servoPositions[numberOfServos] = {0, 0};

void setup() {
  Serial.begin(9600);

  // Attach all of the servos to their pins
  for (int i = 0; i < numberOfServos; i++) {
    servos[i].attach(servoPins[i]);
  }
}

void loop() {
  // Update the servo if there is a message
  if(Serial.available() > 0) {
    String message = Serial.readStringUntil('\n');

    setNewServoPositions(message);

    updateServos();
  }
}

void setNewServoPositions(String message) {
  // Split the incoming message by colons ':'
  StringSplitter *splitter = new StringSplitter(message, servoPositionDelimiter, numberOfServos);
  const int numberOfNewPositions = splitter->getItemCount();

  for(int i = 0; i < numberOfNewPositions; i++) {
    servoPositions[i] = (splitter->getItemAtIndex(i)).toInt();
  }
}

void updateServos() {
  // Loop through the servos and set each to its current position
  for (int i = 0; i < numberOfServos; i++) {
    servos[i].write(servoPositions[i]);
  }
}
