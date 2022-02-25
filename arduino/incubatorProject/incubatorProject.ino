#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Servo.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define DHTTYPE    DHT11      // DHT 11
#define DHTPIN 2              // Digital pin connected to the DHT sensor 

#define servoPin 7            // Servo pin

#define bulbPin 8             // Bulb pin
#define fanPin 9              // Fan pin


// Creating sensor(DHT11) object
DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

// Creating the servo object
Servo bigBoy;

// I2C pins declaration
LiquidCrystal_I2C eYes(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 

unsigned long startTime, refTime; // for timing

void setup() {
  Serial.begin(9600);
  // Initialize sensor (DHT11).
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;
  delay(1000);

  // Initialize servo motor
  bigBoy.attach(servoPin);
  bigBoy.write(0);

  // LCD initialization
  eYes.begin(16,4);
  eYes.setCursor(0,0);
  eYes.print("INCUBATOR CONDITIONS");
  eYes.setCursor(1,1);
  eYes.print("Temperature: ");
  eYes.setCursor(7,2);
  eYes.print("Humidity: ");
  eYes.setCursor(4,4);
  eYes.print("--------------------");

  delay(1000);

  // Pin initialization
  pinMode(bulbPin, OUTPUT);
  pinMode(fanPin, OUTPUT);

  // first rotation(10 cycles)
  for (int i = 0; i < 10; i++)
  {
    moveServo();
    showConditions();
    controlConditions();
  }

  // Initialize start time;
  startTime = millis();
}

void loop() {
  showConditions();
  controlConditions();
  refTime = millis();

  // Controlling rotation
  // To cause rotation every 4 hours, i.e. rotation is done 6 times daily
  if ((refTime-startTime) > 14400000){
    startTime = refTime;
    // rotate 10 cycles
    for (int i = 0; i < 10; i++){
      moveServo();
      showConditions();
      controlConditions(); 
    }
  }
}

void controlConditions(){
  // Getting incubator conditions
  float temperature;
  float humidity;
  delay(delayMS);
  showConditions();
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  temperature = event.temperature;
  
  dht.humidity().getEvent(&event);
  humidity = event.relative_humidity;
  

  // Control of incubator conditions
  //if (temperature < 37.22)
    //heatOn();
  //if (temperature > 38.89)
    //heatOff();

  if (temperature < 28.00)
    heatOn();
  if (temperature > 28.00)
    heatOff();
}


void heatOn(){
  digitalWrite(bulbPin, HIGH);
  digitalWrite(fanPin, HIGH);
}

void heatOff(){
  digitalWrite(bulbPin, LOW);
  digitalWrite(fanPin, LOW);
}

void moveServo()
{
  for (int pos = 0; pos < 180;)
  {
    pos += 35;
    bigBoy.write(pos);
    delay(100);
  }
  delay(1000);
  for (int pos = 180; pos > 0;)
  {
    pos -= 35;
    bigBoy.write(pos);
    delay(100);
  }
  delay(1000);
}


float showConditions(){
  delay(delayMS);
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    eYes.setCursor(14,1);
    eYes.print("Error!");
  }
  else {
    eYes.setCursor(14,1);
    eYes.print(event.temperature);
    eYes.setCursor(18,1);
    eYes.print(F("C"));
    
  }
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    eYes.setCursor(17,2);
    eYes.print("Error!");
  }
  else {
    eYes.setCursor(17,2);
    eYes.print(event.relative_humidity);
    eYes.setCursor(21,2);
    eYes.print(F("%"));
  }
}
