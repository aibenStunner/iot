#include <Servo.h>
//----------------------------------------------//
//Range of this servo is 0 deg to 180 deg//
//But doesn't work really well at angles below 35 deg//


int pos = 0;
int servoPin = 6;
int servoDelay = 25;
int trigPin = 8;
int echoPin = 7;
float pingTime;
float speedOfSound = 368.32;  //speed of sound from previous calibration
float distance;

//Creating the servo object
Servo bigBoy;

void setup() 
{
  Serial.begin(9600);
  bigBoy.attach(servoPin);
  bigBoy.write(pos);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
}

void loop() 
{
  moveServo(); 
}


void moveServo()
{
  for (pos = 0; pos < 180;)
  {
    calcDistance();
    pos += 35;
    bigBoy.write(pos);
    delay(100);
  }

  for (pos = 180; pos > 0;)
  {
    calcDistance();
    pos -= 35;
    bigBoy.write(pos);
    delay(100);
  }
}

void calcDistance()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2000);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(15);

  pingTime = pulseIn(echoPin, HIGH);   //Measure pingTime in microseconds
  pingTime = pingTime / 1000000.;
  
  distance = speedOfSound * pingTime / 2;

  distance = distance * 100;   //distance in centimeters

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" centimeters.");

  //delay(50);
}
