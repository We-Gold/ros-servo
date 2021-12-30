import processing.serial.*;
import controlP5.*;

Serial port;
ControlP5 cp5;

Slider[] sliders;

String message = "";

int numberOfServos = 10;

int[] defaultValues = {76, 72, 138, 128, 180, 123, 65, 41, 108, 117};

void setup() {  
  println(Serial.list());
  
  port = new Serial(this, Serial.list()[1], 115200); // Had to use COM3, hence the 1
  
  cp5 = new ControlP5(this);
  
  size(400, 800);
  
  sliders = new Slider[numberOfServos];
  
  int heightInterval = (height - 100) / numberOfServos;
  
  for(int i = 0; i < numberOfServos; i++) {
    sliders[i] = cp5.addSlider("" + i)
      .setPosition(20, 20 + i * heightInterval)
      .setSize(360, 40)
      .setRange(0, 180)
      .setValue(defaultValues[i]); 
  }
  
  frameRate(30);
}

void draw() {
  sendSliderValues();
}

void sendSliderValues() {
  message = "";
  
  for(int i = 0; i < sliders.length; i++) {
    message += round(sliders[i].getValue()) + (i == sliders.length - 1 ? "" : ":");
  }
  
  message += "\n";
  
  port.write(message);
  print(message);
}
