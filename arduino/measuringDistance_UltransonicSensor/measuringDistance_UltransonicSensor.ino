int trigPin = 8;
int echoPin = 7;
float pingTime;
float speedOfSound = 368.32;  //speed of sound from previous calibration
float distance;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

}

void loop() {
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

  delay(100);
}
