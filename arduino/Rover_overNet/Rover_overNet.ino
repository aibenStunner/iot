#include <ESP8266WiFi.h>


//const char* ssid = "Hidden Network";
//const char* password = "baka_try";

const char* ssid = "Fiifi_GH";
const char* password = "87559835";


const int motorPin1 = 5;
const int motorPin2 = 4;

const int motorPin3 = 10;
const int motorPin4 = 9;

WiFiServer server(80);

void setup()
{
  Serial.begin(115200);
  delay(10);
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  
  delay(40);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
}

void loop()
{
    // Check if a client has connected
    WiFiClient client = server.available();
    if (!client) {
      return;
    }
   
    // Wait until the client sends some data
    Serial.println("new client");
    while(!client.available()){
      delay(1);
    }
   
    // Read the first line of the request
    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();

    int what = 'g';
    if (request.indexOf("/up") != -1){
      Do('w');
    }
    if (request.indexOf("/down") != -1){
      Do('s');
    }
    if (request.indexOf("/left") != -1){
      Do('a');
    }
    if (request.indexOf("/right") != -1){
      Do('d');
    }
    if (request.indexOf("/stop") != -1){
      Do('q');
    }

    // Return the response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println(""); //  do not forget this one
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
    client.println("<link rel=\"icon\" href=\"data:,\">");
    // CSS to style the on/off buttons 
    // Feel free to change the background-color and font-size attributes to fit your preferences
    client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
    
    client.println(".up-button { position:relative; transition: .5s ease; width: 110px; height: 50px; max-width: 110px; max-height: 50px; left: 46px; background-color: green;}");
    client.println(".up-button:focus { background-color: yellow;}");

    client.println(".left-button { position:relative; transition: .5s ease; width: 110px; height: 50px; max-width: 110px; max-height: 50px; top: 5px; left: 25px; background-color: green;}");
    client.println(".left-button:focus { background-color: yellow;}");

    client.println(".stop-button { position:relative; transition: .5s ease; width: 110px; height: 50px; max-width: 110px; max-height: 50px; top:5px; left: 46px; background-color: red;}");
    client.println(".stop-button:focus { background-color: yellow;}");

    client.println(".right-button { position:relative; transition: .5s ease; width: 110px; height: 50px; max-width: 110px; max-height: 50px; top: 5px; left: 65px; background-color: green;}");
    client.println(".right-button:focus { background-color: yellow;}");

    client.println(".down-button { position:relative; transition: .5s ease; width: 120px; height: 50px; max-width: 110px; max-height: 50px; top: 10px; left: 46px; background-color: green;}");
    client.println(".down-button:focus { background-color: yellow;}</style></head>");

    client.println("<body><h1>CONTROLS</h1>");
    client.println("<br />");
    client.println("<a href=\"/up\"\" style=\"width:1000px\"><button class=\"up-button\">UP</button></a>");
    client.println("<br />");

    client.println("<a href=\"/left\"\"><button class=\"left-button\">LEFT</button></a>");
    client.println("<a href=\"/stop\"\"><button class=\"stop-button\">STOP</button></a>");
    client.println("<a href=\"/right\"\"><button class=\"right-button\">RIGHT</button></a>");
  
    client.println("<br />");
    client.println("<a href=\"/down\"\"><button class=\"down-button\">DOWN</button></a>");
    client.println("<br />");

    client.println("</body></html>");
    client.println();
}

void Do (int what){
    if (what == 'q')
    {
    //Stop
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, LOW);
    }

    
    if (what == 'w')
    {
    //Move Forward
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, HIGH);
    digitalWrite(motorPin4, LOW);
    }

    if (what == 's')
    {
    //Move Backward
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, HIGH);
    }

     if (what == 'a')
    {
    //Turn Left
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
    digitalWrite(motorPin3, HIGH);
    digitalWrite(motorPin4, LOW);
    }

    if (what == 'd')
    {
    //Turn right
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, HIGH);
    }
}
