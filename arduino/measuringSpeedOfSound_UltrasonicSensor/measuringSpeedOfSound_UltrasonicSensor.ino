int trigPin = 8;
int echoPin = 7;
float pingTime;
float speedOfSound;
float targetDistance = .1;  //Distance in metres i.e 10cm


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2000);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(15);

  pingTime = pulseIn(echoPin, HIGH);   //Measure pingTime in microseconds

  pingTime = pingTime / 1000000.;
  
  speedOfSound = 2 * targetDistance / pingTime;

  Serial.print("Speed of sound: ");
  Serial.print(speedOfSound);
  Serial.println(" m per sec.");

  delay(1000);
  
}
