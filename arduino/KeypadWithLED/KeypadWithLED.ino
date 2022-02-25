/* @file HelloKeypad.pde
|| @version 1.0
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Demonstrates the simplest use of the matrix Keypad library.
|| #
*/
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 8, 7, 6}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

int ledPin = 10;
String password = "1234";
String tempPassword;

void setup(){
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}
  
void loop()
{
  char key = keypad.getKey();
  if (key)
  {
    Serial.println(key);
    if (key == '0' || key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9')
      tempPassword += key;

    if (key == '#')
    {
      if (tempPassword == "1234")
      {
        digitalWrite(ledPin, HIGH);
        tempPassword = "";
      }
      else
      {
        digitalWrite(ledPin, LOW);
        tempPassword = "";ss
      }
    }
    if(key == '*')
      {
        tempPassword = "";
        digitalWrite(ledPin, LOW);
      }
  }
}
