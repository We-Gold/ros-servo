#include <Servo.h>

const int numberOfServos = 10;

int servoPins[numberOfServos] = {12, 11, 10, 9, 8, 20, 6, 5, 4, 3};

//Servos:
//FRL - 12
//FRF - 11
//FRLat - 10
//FLL - 9
//FLF - 8
//FLLat - 7
//BRL - 6
//BRF - 5
//BLL - 4
//BLF - 3

Servo servos[numberOfServos] = {Servo(), Servo(), Servo(), Servo(), Servo(), Servo(), Servo(), Servo(), Servo(), Servo()};

int ledPin = 2;

void setup() {
  Serial.begin(115200);

  // Attach all of the servos to their pins
  for (int i = 0; i < numberOfServos; i++) {
    // Attach the servo object to the pin
    servos[i].attach(servoPins[i]);
  }

  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, HIGH);
  
  // Update the servo if there is a message
  if(Serial.available() > 0) {
    setNewServoPositions();
    
    emptyBuffer();
  }

  delay(15);
}

void setNewServoPositions() {
  // Save the new desired position for each servo
  for (int i = 0; i < numberOfServos; i++) {
    servos[i].write(Serial.parseInt());
  }

  // Read in the new line before the next message
  Serial.readStringUntil('\n');
}

void emptyBuffer() {
  // Reads in all available bytes
  while (Serial.available() > 0) {
    Serial.read();
  }
}
