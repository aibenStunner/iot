#include <Servo.h>

int pos = 0;
int servoPin = 7;
int servoDelay = 25;

//Ultrasonic Sensor variables
int trigPin = 8; //Trig pin from arduino
int echoPin = 9; //Echo pin from arduino+
float timeTR;
float distance;
float vSound = 343.;

Servo bigBoy;

void setup()
{
  Serial.begin(9600);
  bigBoy.attach(servoPin);
  bigBoy.write(35);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}


void loop()
{
  //Sending the signal from the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2000);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(15);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);

  //Receiving the signal from the ultrasonic sensor
  timeTR = pulseIn(echoPin, HIGH);
  timeTR = timeTR/1000000.; // Converting from microseconds to seconds

  //Calculating the distane
  distance = vSound * timeTR;
  distance = distance / 2; //To get the actual distance
  distance = distance * 100; //Distance in centimetres

  Serial.println(distance);


  //if(distance <= 40)
  //{
   //   for (pos = 0; pos <= 180; pos += 2)
  //      {
   //       bigBoy.write(pos);
   //       delay(50);
     //   }
  //}

  
  //if(distance > 40)
  //{
   // for (pos = 180; pos >= 0; pos -= 2)
     // {
     //   bigBoy.write(pos);
     //   delay(50);
     // }
 // }
  

}
