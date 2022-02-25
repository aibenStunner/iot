#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

int trigPin = 8; //Trig pin from arduino
int echoPin = 9; //Echo pin from arduino
float timeTR;
float distance;
float vSound = 343.;

//I2C pins declaration
LiquidCrystal_I2C eYes(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 

void setup() 
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  eYes.begin(16,4);
  eYes.setCursor(0,1);
  eYes.print("Measured Distance...");
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

  eYes.setCursor(5,2);
  eYes.print("                   "); //Clears the entire row
  eYes.setCursor(5,2);
  eYes.print(distance);
  eYes.print(" centimetres");
 

  delay(250);
}
