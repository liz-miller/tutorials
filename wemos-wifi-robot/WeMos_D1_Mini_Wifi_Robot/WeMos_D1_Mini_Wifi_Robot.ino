// Load Wi-Fi library
#include <ESP8266WiFi.h>
/*
 * Wemos D1 mini + L298N wifi-enabled Robot Controller
 * Control your Create mobile robot using this framework
 * Github Repo - 
 * Dependencies:
 *    1. ESP8266 library: Sketch >> Include Library >> Manage Libraries >> Search for ESP8266com & install
 *    2. Arduino Board Manager URL (Copy & paste in Arduino >> Preferences): http://arduino.esp8266.com/stable/package_esp8266com_index.json
 *    3. Set board to WeMos D1 R2 & mini under Tools >> Board. 
 *    4. Change baud rate to 115200 Tools >> Upload Speed >> 115200
 * ---
 * Wemos D1 mini + L298N wifi-enabled Robot Controller by Learn Robotics LLC is licensed under a Creative Commons Attribution-ShareAlike 4.0 International License.
 * Based on a work at https://www.learnrobotics.org/blog.
 * Permissions beyond the scope of this license may be available at https://www.learnrobotics.org/contact.
 * v1.0 published 03/06/2018 by Liz Miller
 * Refer to Terms & Conditions at https://www.learnrobotics.org/terms-conditions/
 * 
 * Built with references from:
 *  Random Nerd Tutorials - https://randomnerdtutorials.com/esp8266-web-server/
 *  L298N Wiring Diagram - http://www.14core.com/wiring-driving-the-l298n-h-bridge-on-2-to-4-dc-motors/
 *  Wemos-D1-Mini-RC - https://github.com/wassgha/WemosD1MiniRC
 *  esp8266-robot - https://github.com/openhomeautomation/esp8266-robot
 */

// Replace with your network credentials
const char* ssid     = "yourssid";
const char* password = "yourpassword";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;
// Auxiliar variable to store the current output state
String outputState = "off"; //initially set to off
String outputDirection = "n/a"; //initially no direction

// Motor Inputs (INL=left in INR=right in)
const int INL1 = D7;
const int INL2 = D6;
const int INR1 = D3;
const int INR2 = D4;

//from BasicHttpClient example
/*void setupWifi(){
      USE_SERIAL.begin(115200);
   // USE_SERIAL.setDebugOutput(true);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

    WiFi.mode(WIFI_STA);
    WiFiMulti.addAP("ROBONET", "Mast3rSUsh1");
}*/

void connectToWifi(){
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void setup() {
  // put your setup code here, to run once:
  pinMode(INL1, OUTPUT);
  pinMode(INL2, OUTPUT);
  pinMode(INR1, OUTPUT);
  pinMode(INR2, OUTPUT);
  stopMotors(); //ensure motors are off on initialization
  Serial.begin(115200);
  connectToWifi(); //rui example
}

void right(){
  Serial.println("right...");
  digitalWrite(INL1, HIGH);
  analogWrite(INL2, LOW);  
  digitalWrite(INR1, HIGH);
  analogWrite(INR2, LOW);
}

void left(){
  Serial.println("left...");
  digitalWrite(INL1, LOW);
  digitalWrite(INL2, HIGH);  
  digitalWrite(INR1, LOW);
  digitalWrite(INR2, HIGH);
}

void stopMotors(){
  Serial.println("stop...");
  digitalWrite(INL1, LOW);
  digitalWrite(INL2, LOW);  
  digitalWrite(INR1, LOW);
  digitalWrite(INR2, LOW);
}

void forward(){
  Serial.println("forward...");
  digitalWrite(INL1, HIGH);
  digitalWrite(INL2, LOW);  
  digitalWrite(INR1, LOW);
  digitalWrite(INR2, HIGH);
}

void backward(){
  Serial.println("backward...");
  digitalWrite(INL1, LOW);
  digitalWrite(INL2, HIGH);  
  digitalWrite(INR1, HIGH);
  digitalWrite(INR2, LOW);
}

//Create a web server on local network address
void createWebServer(){
  WiFiClient client = server.available();   // Listen for incoming clients
  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // Motor Control (On & Off)
            if (header.indexOf("GET /control/forward") >= 0) {
              outputState = "ON";
              outputDirection = "MOVING FORWARDS";
              forward();
              
            } else if (header.indexOf("GET /control/stop") >= 0) {
              outputState = "OFF";
              outputDirection = "ROBOT IS NOT MOVING";
              stopMotors();
              
            } else if (header.indexOf("GET /control/backward") >= 0) {
              outputState = "ON";
              outputDirection = "MOVING BACKWARDS";
              backward();
              
            } else if (header.indexOf("GET /control/left") >= 0) {
              outputState = "ON";
              outputDirection = "MOVING LEFT";
              left();  
                         
            } else if (header.indexOf("GET /control/right") >= 0) {
              outputState = "ON";
              outputDirection = "MOVING RIGHT...";
              right();             
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #2ca545; border: none; color: white; padding: 16px 40px; margin: 25px");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}</style></head>");
            
            // Web Page Heading
            client.println("<img src=https://www.learnrobotics.org/wp-content/uploads/2017/11/cropped-logo-small-1.png height=50px>");
            client.println("<h2>Wifi Mobile Robot Controller</h2>");
            client.println("<p> Take control of your robot from anywhere on your home network! Tutorial sponsored by <a href=https://www.learnrobotics.org>Learn Robotics</a></p>");
            client.println(" ");
            client.println(" ");
            
            // Display current state, and controller buttons for robot 
            client.println("<p>Robot State " + outputState + " Robot Direction " + outputDirection +"</p>");
            
            client.println("<p><a href=\"/control/forward\"><button class=\"button\">FORWARD</button></a></p>");
            client.print("<p><a href=\"/control/left\"><button class=\"button\">LEFT</button></a> <a href=\"/control/stop\"><button class=\"button\">STOP</button></a> <a href=\"/control/right\"><button class=\"button\">RIGHT</button></a></p>");
            client.println("<p><a href=\"/control/backward\"><button class=\"button\">BACKWARD</button></a></p>");
            
               
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}

void loop(){
  createWebServer();
}
