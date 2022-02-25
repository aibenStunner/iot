#define sensorPin 2
#define ledPin 8
#define buzzerPin 7

int val = 0;
bool motionState = false;  //We start with no motion detected

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(sensorPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);
}

void loop()
{
  val = digitalRead(sensorPin); //Read out the sensor pin and store as val

  //If motion is detected (ie. sensorPin=HIGH),...
  if (val == HIGH)
  {
    digitalWrite(ledPin, HIGH);
    alarm(500, 1000); //Call the alarm(duration, frequencuy) function
    delay(100);

    //Change the motion state to true (motion detected):
    if (motionState == false)
    {
      Serial.println("Motion detected");
      motionState = true;
    }
  }

  else 
  {
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);
    delay(200);

    //Change the motion state to false (no motion)
    if (motionState == true)
    {
      Serial.println("Motion ended");
      motionState = false;
    }
  } 
}


//Fucntion to sound the alarm
void alarm(long duration, int freq)
{
  tone(buzzerPin, freq);
  delay(duration);
  noTone(buzzerPin);
}

