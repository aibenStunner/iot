const int LEDpin = 13;
int photoSense = A0;
int sensorValue;

//For calibration purposes
int sensorLow = 1023;
int sensorHigh = 0;

void setup()
{
  //Turn on LED to signal the start of the calibration 
  pinMode(LEDpin, OUTPUT);
  digitalWrite(LEDpin, HIGH);

  //Calibrate during the first five seconds
  while(millis() < 5000)
  {
    sensorValue = analogRead(photoSense);

    //Record the maximum sensor value
    if (sensorValue > sensorHigh)
    {
      sensorHigh = sensorValue;
    }

    //Record the minimum sensor value
    if (sensorValue < sensorLow)
    {
      sensorLow = sensorValue;
    }
  }

  //Turn off led to signal the end of calibration
  digitalWrite(LEDpin, LOW);
}

void loop()
{
  //Read the input from the photodiode
  sensorValue = analogRead(photoSense);

  //Map the sensor values to a wide range of pitches
  //Adjust the values below to conform to the maximum and minimum sensor values
  int pitch = map(sensorValue, sensorLow, sensorHigh, 50, 4000);

  //Play the tone
  tone(8, pitch,20); // 20 is the duration for which the sound is played

  delay(10);
}
