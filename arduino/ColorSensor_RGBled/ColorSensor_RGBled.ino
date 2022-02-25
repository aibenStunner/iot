#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <String.h>

String colourName(int R, int G, int B)
{
  String colour;

  if(R == 0 && G == 0 && B == 0)
    colour = "Black"; 

  if((R >= 0 && R <= 70) && (G >= 0 && G <= 70) && (B >= 190 && B <= 255))
    colour = "Blue"; 

  if((R >= 0 && R <= 70) && (G >= 190 && G <= 255) && (B >= 190 && B <= 255))
    colour = "Cyan"; 

  if((R >= 100 && R <= 128) && (G >= 100 && G <= 128) && (B >= 100 && B <= 128))
    colour = "Gray"; 

  if((R >= 50 && R <= 64) && (G >= 50 && G <= 64) && (B >= 50 && B <= 64))
    colour = "Dark Gray"; 

  if((R >= 170 && R <= 192) && (G >= 170 && G <= 192) && (B >= 170 && B <= 192))
    colour = "Light Gray"; 

  if((R >= 0 && R <= 70) && (G >= 190 && G <= 255) && (B >= 0 && B <= 70))
    colour = "Green"; 

  if((R >= 190 && R <= 255) && (G >= 0 && G <= 70) && (B >= 190 && B <= 255))
    colour = "Magenta"; 

  if((R >= 190 && R <= 255) && (G >= 170 && G <= 200) && (B >= 0 && B <= 70))
    colour = "Orange"; 

  if((R >= 190 && R <= 255) && (G >= 150 && G <= 175) && (B >= 150 && B <= 175))
    colour = "Pink"; 

  if((R >= 190 && R <= 255) && (G >= 0 && G <= 70) && (B >= 0 && B <= 70))
    colour = "Red"; 

  if((R >= 200 && R <= 255) && (G >= 200 && G <= 255) && (B >= 200 && B <= 255))
    colour = "White"; 

  if((R >= 190 && R <= 255) && (G >= 190 && G <= 255) && (B >= 0 && B <= 70))
    colour = "Yellow"; 

  return colour;
}


int setCoordinates(String colour)
{
  int len = colour.length();
  int c;

  if (len == 3 || len == 4)
    c = 8;

  if (len == 5 || len == 6)
    c = 7;

  if (len == 7 || len == 8)
    c = 6;

  if (len == 9 || len == 10)
    c = 5;

  if (len == 11 || len == 12)
    c = 4;

  if (len == 13  || len == 14)
    c = 3;

  if (len == 15 || len == 16)
    c = 2;

  if (len == 17 || len == 18)
    c = 1;

  if (len == 19 || len == 20)
    c = 0;

  return c;
}



//I2C pins declaration
LiquidCrystal_I2C eYes(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 

//LEDpins
int redPin = 9;
int greenPin = 10;
int bluePin = 11;

//ColorSensor
int S2 =7; //Color sensor pin S2 
int S3 = 8;  //Color sensor pin S3
int outPin = 4; //Color sensor OUT
//S1 goes to 5V
//S0 goes to Ground

int rColorStrength;
int gColorStrength;
int bColorStrength;


unsigned int pulseWidth;

using namespace std;
void setup()
{
  Serial.begin(9600);

  //LED pin initialization
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  //Color Sensor pin initialization
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(outPin, INPUT);

  eYes.begin(20,4);
}

void loop()
{
  //Reading the red component of the color
  //S2 and S3 are to be set to LOW
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);

  pulseWidth = pulseIn(outPin, LOW);

  rColorStrength = pulseWidth;

  //Passing the value through a couple of linear regression models
  rColorStrength = -0.1308384941*rColorStrength + 250.3879641;
  if (rColorStrength <= 0)
    rColorStrength = 0;
  rColorStrength = 1.403793486*rColorStrength - 74.58946568;
  if (rColorStrength <= 0)
    rColorStrength = 0;
  rColorStrength = 0.9472116605*rColorStrength + 9.999291367;
  if (rColorStrength <= 0)
    rColorStrength = 0;
  rColorStrength = 1.044722375*rColorStrength - 10.23461944;
  if (rColorStrength <= 0)
    rColorStrength = 0;
  if (rColorStrength >= 255)
    rColorStrength = 255;
   
   
  //Reading the green component of the color
  //S2 and S3 are to be set to HIGH
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);

  pulseWidth = pulseIn(outPin, LOW);

  gColorStrength = pulseWidth;

  //Passing the value through a couple of linear regression models
  gColorStrength = -0.1756434485*gColorStrength + 304.2022772;
  if (gColorStrength <= 0)
    gColorStrength = 0;
  gColorStrength = 1.151105658*gColorStrength - 39.60219027;
  if (gColorStrength <= 0)
    gColorStrength = 0;
  gColorStrength = 0.8001303181*gColorStrength + 47.45091696;
  if (gColorStrength <= 0)
    gColorStrength = 0;
  gColorStrength = 1.001396098*gColorStrength - 0.07112940755;
  if (gColorStrength <= 0)
    gColorStrength = 0;
  if (gColorStrength >= 255)
    gColorStrength = 255;

  //Reading the blue component of the color
  //S2 is set to LOW and S3 is HIGH
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);

  pulseWidth = pulseIn(outPin, LOW);

  bColorStrength = pulseWidth;

  //Passing the value through a couple of linear regression models
  bColorStrength = -0.2140379614*bColorStrength + 231.3113893;
  if (bColorStrength <= 0)
    bColorStrength = 0;
  bColorStrength = 1.271793408*bColorStrength - 41.97278818;
  if (bColorStrength <= 0)
    bColorStrength = 0;
  bColorStrength = 0.9508441415*bColorStrength - 25.22249504;
  if (bColorStrength <= 0)
    bColorStrength = 0;
  bColorStrength = 1.262302192*bColorStrength + 17.7833985;
  if (bColorStrength <= 0)
    bColorStrength = 0;
  if (bColorStrength >= 255)
    bColorStrength = 255;


  //Displaying output to Serial Monitor
  Serial.print(rColorStrength);
  Serial.print(" , ");
  Serial.print(gColorStrength);
  Serial.print(" , ");
  Serial.println(bColorStrength); 
  Serial.println("");

  analogWrite(redPin, rColorStrength);
  analogWrite(greenPin, gColorStrength);
  analogWrite(bluePin, bColorStrength); 


 String colour = colourName(rColorStrength, gColorStrength, bColorStrength);
 int c = setCoordinates(colour);
 
 //Show the colour on LCD
 eYes.setCursor(0, 0);
 eYes.print("                   ");
 eYes.setCursor(c, 0);
 eYes.print(colour);

 //Show corresponding RGB on the LCD
 eYes.setCursor(0, 2);
 eYes.print("                   ");
 eYes.setCursor(0, 2);
 eYes.print("R(");
 eYes.print(rColorStrength);
 eYes.print(")");
 eYes.setCursor(7, 2);
 eYes.print("G(");
 eYes.print(gColorStrength);
 eYes.print(")");
 eYes.setCursor(14, 2);
 eYes.print("B(");
 eYes.print(bColorStrength);
 eYes.print(")");

  
  delay(250);
  
}
