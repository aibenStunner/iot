//Including the CapacitiveSensor library
#include <CapacitiveSensor.h>

//Creating the sensor object
CapacitiveSensor capSensor(4,2);

int threshold = 1000;

const int LEDpin = 13;

void setup()
{
  //Serial port starter
  Serial.begin(9600);

  pinMode(LEDpin, OUTPUT);
}

void loop()
{
  //Reading the sensor value into a variable
  long sensorValue = capSensor.capacitiveSensor(30);

  //Displaying the value read to the serial monitor
  Serial.println(sensorValue); 

  if(sensorValue > threshold)
  {
    digitalWrite(LEDpin, HIGH);
  }

  else
  {
    digitalWrite(LEDpin, LOW);
  }

  delay(10);
}
