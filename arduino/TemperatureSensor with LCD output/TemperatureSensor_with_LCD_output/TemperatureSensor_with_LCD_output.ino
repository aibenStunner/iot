#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//I2C pins declaration
LiquidCrystal_I2C eYes(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 

//Variable for the temperature sensor
const int sensorPin = A0;

//BaseLine temprerature(room temperature is most suitable)
float baselineTemp = 30;
void setup()
{
  //Starting the LCD Display
  eYes.begin(16,4);
  eYes.setCursor(3,1);
  eYes.print("Temperature: ");

  
  Serial.begin(9600); //Open the serial port to display values

  //set the LED pins as outputs
  //the for() loops saves some extra coding
  for(int x = 2; x <= 9; x++)
  {
    pinMode(x, OUTPUT);
    digitalWrite(x, LOW); 
  }
}


void loop()
{
  int sensorValue = analogRead(sensorPin);  //Read value from the temperature sensor

  //Send the 10-bit sensor value out the serial port
  Serial.print(sensorValue);
  Serial.println(" AnalogToDigitalConverter, ");

  //Convert the ADC reading to voltage
  float voltage = (sensorValue / 1024.) * 5000.0;

  //Send the voltage level out to the Serial port
  Serial.print(voltage);
  Serial.println(" milliVolts. ");

  //Convert the voltage to centigrades
  //The sensor reports 10mV per degree with 500mV offset
  float temperature = voltage / 10;
  Serial.print(temperature);
  Serial.println(" degC");
  Serial.println(" ");

  //Printing to the LCD Display the recorded temperature
  eYes.setCursor(5,2);
  eYes.print("                "); //Clears the entire row
  eYes.setCursor(5,2);
  eYes.print(temperature);
  eYes.print(" degreeCelcius");
  delay(250);

  //Using the baseline temperature as a starting point, Increment
  //The number to LEDs that are on for every 2 degress of increment
  //If the current temperature is lower than the baseline
  //Turn off all LEDs

  if(temperature < baselineTemp)
  {
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
  }

  else if(temperature >= baselineTemp+1 && temperature < baselineTemp+2)
  {
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW); 
  }

   else if(temperature >= baselineTemp+2 && temperature < baselineTemp+3)
  {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW); 
  }

   else if(temperature >= baselineTemp+3 && temperature < baselineTemp+4)
  {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW); 
  }

    else if(temperature >= baselineTemp+4 && temperature < baselineTemp+5)
  {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW); 
  }

   else if(temperature >= baselineTemp+5 && temperature < baselineTemp+6)
  {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW); 
  }

   else if(temperature >= baselineTemp+6 && temperature < baselineTemp+7)
  {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW); 
  }

   else if(temperature >= baselineTemp+7 && temperature < baselineTemp+8)
  {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW); 
  }

  else if(temperature >= baselineTemp+8)
  {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH); 
  }
}
