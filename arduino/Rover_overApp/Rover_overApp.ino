#define motorPin1 5
#define motorPin2 4

#define motorPin3 10
#define motorPin4 9

#define servoPin 15

#define trigPin 2
#define echoPin 0


#include <Servo.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

// collision Avoidance setup
int distance = 100;

//Creating the servo object
Servo bigBoy;


String command;     //String to store app command state.
int speedCar = 800;         // 400 - 1023.
int speed_Coeff = 3;

const char* ssid = "NodeMCU Car";
ESP8266WebServer server(80);

void setup(){
    // motion setup
    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
    pinMode(motorPin3, OUTPUT);
    pinMode(motorPin4, OUTPUT);
  
    Serial.begin(115200);   // COM listener

    // Collision avoidance
    bigBoy.attach(servoPin);
    bigBoy.write(115);
    pinMode(trigPin, OUTPUT);   
    pinMode(echoPin, INPUT);
    delay(2000);
    distance = readDistance();
    delay(100);
    distance = readDistance();
    delay(100);
    distance = readDistance();
    delay(100);
    distance = readDistance();
    delay(100);
   
    // Connecting WiFi
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid);
  
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);
   
    // Starting WEB-server 
    server.on ( "/", HTTP_handleRoot );
    server.onNotFound ( HTTP_handleRoot );
    server.begin();
}

//////////// MOTION//////////////////////////
void goAhead(){
    analogWrite(motorPin1, speedCar);
    analogWrite(motorPin3, speedCar);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin4, LOW);
}

void goBack(){
    analogWrite(motorPin2, speedCar);
    analogWrite(motorPin4, speedCar);
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin3, LOW); 
}

void goRight(){
    analogWrite(motorPin1, speedCar);
    analogWrite(motorPin4, speedCar);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
}

void goLeft(){
    analogWrite(motorPin2, speedCar);
    analogWrite(motorPin3, speedCar);
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin4, LOW);
}

void goAheadRight(){
    analogWrite(motorPin3, speedCar/speed_Coeff);
    analogWrite(motorPin1, speedCar);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin4, LOW);
}

void goAheadLeft(){
    analogWrite(motorPin1, speedCar/speed_Coeff);
    analogWrite(motorPin3, speedCar);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin4, LOW);
}

void goBackRight(){
    analogWrite(motorPin4, speedCar/speed_Coeff);
    analogWrite(motorPin1, speedCar);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
}

void goBackLeft(){
    analogWrite(motorPin1, speedCar/speed_Coeff);
    analogWrite(motorPin4, speedCar);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
}

void stopRobot(){
  //Stop
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, LOW);
}
//////////////////////////////////////////////////
   
   
/////////// Collision avoidance //////////////////////
int lookRight()
{
    bigBoy.write(50); 
    delay(200);
    int distance = readDistance();
    bigBoy.write(115); 
    delay(200);
    return distance;
}

int lookLeft()
{
    bigBoy.write(170); 
    delay(200);
    int distance = readDistance();
    bigBoy.write(115); 
    delay(200);
    return distance;
}

int readDistance() { 
    long duration;
    int distance;
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    
    // Calculating the distance
    distance= duration*0.034/2;
    Serial.print("Distance: ");
    Serial.println(distance);
    return distance;
}
///////////////////////////////////////////////////////////////

void loop() {
      // START /////
      handleMotion();
}


void handleMotion(){
   int distanceR = 0;
   int distanceL = 0;
   delay(40);

   if(distance<=20)
   {
      stopRobot();
      delay(100);
      goBack();
      delay(300);
      stopRobot();
      delay(100);
      distanceR = lookRight();
      distanceL = lookLeft();
    
      if(distanceR>=distanceL)
      {
        goRight();
        delay(300);
        stopRobot();
      }
      else
      {
        goLeft();
        delay(300);
        stopRobot();
      }
   }
   
   else
   {
      server.handleClient();
    
      command = server.arg("State");
      if (command == "F") goAhead();
      else if (command == "B") goBack();
      else if (command == "L") goLeft();
      else if (command == "R") goRight();
      else if (command == "I") goAheadRight();
      else if (command == "G") goAheadLeft();
      else if (command == "J") goBackRight();
      else if (command == "H") goBackLeft();
      else if (command == "0") speedCar = 400;
      else if (command == "1") speedCar = 470;
      else if (command == "2") speedCar = 540;
      else if (command == "3") speedCar = 610;
      else if (command == "4") speedCar = 680;
      else if (command == "5") speedCar = 750;
      else if (command == "6") speedCar = 820;
      else if (command == "7") speedCar = 890;
      else if (command == "8") speedCar = 960;
      else if (command == "9") speedCar = 1023;
      else if (command == "S") stopRobot();
   }
   distance = readDistance();   
}

void HTTP_handleRoot(void) {

if( server.hasArg("State") ){
       Serial.println(server.arg("State"));
  }
  server.send ( 200, "text/html", "" );
  delay(1);
}
