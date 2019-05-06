//This example will use a static IP to control the switching of a relay. Over LAN using a web browser. 
//A lot of this code have been resued from the example on the ESP8266 Learning Webpage below. 
//http://www.esp8266learning.com/wemos-webserver-example.php


//CODE START 
//1
#include <ESP8266WiFi.h>


// Below you will need to use your own WIFI informaiton.
//2
const char* ssid = "Name of Wi-Fi netwokr"; //WIFI Name, WeMo will only connect to a 2.4GHz network.
const char* password = "Your wi-fi password"; //WIFI Password


//defining the pin and setting up the "server"
//3
int relayPin = D1;
int relayPin1 = D2;
int relayPin2 = D3;
int relayPin3 = D4;
WiFiServer server(80);
IPAddress ip(192, 168, 0, 109); // where 109 is the desired IP Address
IPAddress gateway(192, 168, 0, 1); // set gateway to match your network
IPAddress subnet(255, 255, 255, 0); // set subnet mask to match your network




// void setup is where we initialize variables, pin modes, start using libraries, etc. 
//The setup function will only run once, after each powerup or reset of the wemos board.
//4
void setup() {
  Serial.begin(115200);
  delay(10);
 


  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
  
  pinMode(relayPin1, OUTPUT);
  digitalWrite(relayPin1, LOW);

   pinMode(relayPin2, OUTPUT);
  digitalWrite(relayPin2, LOW);

   pinMode(relayPin3, OUTPUT);
  digitalWrite(relayPin3, LOW);
 
  Serial.print(F("Setting static ip to : "));
  Serial.println(ip);
  
  // Connect to WiFi network
  //5
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.config(ip, gateway, subnet); 
  WiFi.begin(ssid, password);
  //Trying to connect it will display dots
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
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/"); 
}


//void loop is where you put all your code. it is a funtion that returns nothing and will repeat over and over again
//6
void loop() {
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
 
  //Match the request, checking to see what the currect state is
  int value = LOW;
  int value1 = LOW;
  int value2 = LOW;
  int value3 = LOW;
  if (request.indexOf("/relay=ON") != -1) {
  value = digitalRead(relayPin);
  if(value==LOW)
  {
  digitalWrite(relayPin, HIGH);
  value = HIGH;
  }
  else if(value==HIGH)
  {
  digitalWrite(relayPin, LOW);
  value=LOW;
  }
  } 

  if (request.indexOf("/relay2=ON") != -1) {
  value1 = digitalRead(relayPin1);
  if(value1==LOW)
  {
  digitalWrite(relayPin1, HIGH);
  value1 = HIGH;
  }
  else if (value1==HIGH)
  {
  digitalWrite(relayPin1, LOW);
  value1= LOW;
  }
  } 

  if (request.indexOf("/relay3=ON") != -1) {
   value2 = digitalRead(relayPin2);
  if(value2==LOW)
  {
  digitalWrite(relayPin2, HIGH);
  value2 = HIGH;
  }
  else if (value2==HIGH)
  {
  digitalWrite(relayPin2, LOW);
  value2= LOW;
  }
  } 

  if (request.indexOf("/relay4=ON") != -1) {
   value3 = digitalRead(relayPin3);
  if(value3==LOW)
  {
  digitalWrite(relayPin3, HIGH);
  value3 = HIGH;
  }
  else if (value3==HIGH)
  {
  digitalWrite(relayPin3, LOW);
  value3= LOW;
  }
  } 
 
  
  // Return the response, build the html page
  //7
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  
 
  client.print("Uredjaj je sada: ");

  value = digitalRead(relayPin);
  value1 =digitalRead(relayPin1);
  value2 = digitalRead(relayPin2);
  value3 = digitalRead(relayPin3);
  if(value == HIGH) {
  client.print("Ukljucen (ON)");  
  } else if(value == LOW){
  client.print("Iskljucen (OFF)");
  }
   client.print("<br><br> Uredjaj2 je sada:"); 
  if(value1 == HIGH) {
  client.print("  Ukljucen2 (ON)");  
  } else if(value1 == LOW) {
  client.print("  Iskljucen2 (OFF)");
  }
   client.print("<br><br> Uredjaj3 je sada:"); 
  if(value2 == HIGH) {
  client.print("  Ukljucen3 (ON)");  
  } else if(value2 == LOW) {
  client.print("  Iskljucen3 (OFF)");
  }
   client.print("<br><br> Uredjaj4 je sada:"); 
  if(value3 == HIGH) {
  client.print("  Ukljucen4 (ON)");  
  } else if(value3 == LOW) {
  client.print("  Iskljucen4 (OFF)");
  }
  
  client.println("<br><br><br>");
  if(value==LOW)
  {
  client.println("<button type=""button"" style=""background-color:#0086b3;color:white""><a href=\"/relay=ON\" style=""color: #ffffff;text-decoration:none;"">Svetlo 1</a></button> <br><br>");
  }
  else if(value=HIGH)
  {
  client.println("<button type=""button"" style=""background-color:#cc0099;color:white""><a href=\"/relay=ON\" style=""color: #ffffff;text-decoration:none;"">Svetlo 1</a></button> <br><br>");
  }
    if(value1==LOW)
  {
  client.println("<button type=""button"" style=""background-color:#0086b3;color:white""><a href=\"/relay2=ON\" style=""color: #ffffff;text-decoration:none;"">Svetlo 2</a></button> <br><br>");
  }
  else if(value1=HIGH)
  {
  client.println("<button type=""button"" style=""background-color:#cc0099;color:white""><a href=\"/relay2=ON\" style=""color: #ffffff;text-decoration:none;"">Svetlo 2</a></button> <br><br>");
  }
    if(value2==LOW)
  {
  client.println("<button type=""button"" style=""background-color:#0086b3;color:white""><a href=\"/relay3=ON\" style=""color: #ffffff;text-decoration:none;"">Svetlo 3</a></button> <br><br>");
  }
  else if(value2=HIGH)
  {
  client.println("<button type=""button"" style=""background-color:#cc0099;color:white""><a href=\"/relay3=ON\" style=""color: #ffffff;text-decoration:none;"">Svetlo 3</a></button> <br><br>");
  }
    if(value3==LOW)
  {
  client.println("<button type=""button"" style=""background-color:#0086b3;color:white""><a href=\"/relay4=ON\" style=""color: #ffffff;text-decoration:none;"">Svetlo 4</a></button> <br><br>");
  }
  else if(value3=HIGH)
  {
  client.println("<button type=""button"" style=""background-color:#cc0099;color:white""><a href=\"/relay4=ON\" style=""color: #ffffff;text-decoration:none;"">Svetlo 4</a></button> <br><br>");
  }
  
   
  
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
 
}//END 
