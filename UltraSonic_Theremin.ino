#include <Volume.h>
#include <Ultrasonic.h>

Volume vol; //default pin is set to 5

Ultrasonic ultrasonic(9,8); //(Trig, Echo)
Ultrasonic ultrasonic2(11,10); //(Trig, Echo)

// variable to hold sensor value
int sensorValue;
// variable to hold secondary sensor value
int volumeSensorValue;
// variable to hold sensor minimum
int sensorMin = 0;
// variable to hold sensor maximum
int sensorMax = 50;
// variable to hold pitch value
int pitch;
//variable to hold previous pitch
int previousPitch;
// variable to hold pin for speaker
const int speakerPin = 5;

void setup() {
  Serial.begin(9600);
}

void loop() {
  //read the input from sensors and store them in a variable
  sensorValue = ultrasonic.Ranging(CM);
  volumeSensorValue = ultrasonic2.Ranging(CM);

  //print sensor value over serial
  Serial.print("Pitch Sensor Val: ");
  Serial.println(sensorValue);
  Serial.print("Volume Sensor Val: ");
  Serial.println(volumeSensorValue);

  // check if hand is in range
  if (sensorValue < sensorMax) {
    //create the pitch to play on speaker
    pitch = map(sensorValue, sensorMin, sensorMax, 50, 4000);

    //start volume
    vol.begin();

    //set master volume to sensor max
    vol.setMasterVolume(51.00);
    
    // play the tone for 20 ms on speaker pin
    vol.tone(pitch, volumeSensorValue);

    // wait for a moment
    vol.delay(10);
  }
  else {
    // default tone and volume
    vol.tone(0, volumeSensorValue);
    vol.delay(10);
  }
}
