#include <DHT.h>

#define dht_apin A0


DHT dht;

void setup(){
  Serial.begin(9600);

  delay(500);
  Serial.println("DHT11 Humidity & Temperature Sensor\n\n");
  delay(1000);
}


void loop(){
  dht.read11(dht_apin);

  Serial.print("Current humidity = ");
  Serial.print(dht.humidiy);
  Serial.print("%  ");
  Serial.print("Temperature = ");
  Serial.print(dht.temperature);
  Serial.print("C ");
  delay(3000);
}
