/************************************************************************************************* 
                                      PROGRAMMINFO
************************************************************************************************** 
Funktion: ESP32 TESTPROGRAMM Access Point mit WEB Server fuer drei GPIOs
Mobile Browser:   192.168.4.1
**************************************************************************************************
Version: khf 13.09.2024
**************************************************************************************************
Board: DOIT ESP32 DEVKIT V1 Ver.ESPRESSIF 3.0.4
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
http://arduino.esp8266.com/stable/package_esp8266com_index.json
https://adafruit.github.io/arduino-board-index/package_adafruit_index.json
**************************************************************************************************
C++ Arduino IDE V1.8.19
**************************************************************************************************
Einstellungen:
https://dl.espressif.com/dl/package_esp32_index.json
http://dan.drown.org/stm32duino/package_STM32duino_index.json
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_dev_index.json
**************************************************************************************************
**************************************************************************************************/
//Wi-Fi Library https://github.com/arduino-libraries/WiFi
#include <WiFi.h>

const char* ssid     = "ESP32"; 
const char* password = "1234";

WiFiServer server(80);

String header;

String output26State = "off";
String output27State = "off";
String output13State = "off";

const int output26 = 26;
const int output27 = 27;
const int output13 = 13;

void setup() {
  Serial.begin(115200);
  // Definiere Ausgänge
  pinMode(output26, OUTPUT);
  pinMode(output27, OUTPUT);
   pinMode(output13, OUTPUT);
  // Setzt Ausgänge auf LOW
  digitalWrite(output26, LOW);
  digitalWrite(output27, LOW);
  digitalWrite(output13, LOW);
  
  // Wi-Fi verbinden
  Serial.print("Service Set Identifier (Access Point)â€¦");

  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // eingehende Clients

  if (client) {                             // Wenn neue Client-Verbindung,
    Serial.println("New Client.");          // sende Info an seriellen Monitor
    String currentLine = "";                // Zeichenfolge, um eingehende Daten vom Client zu speichern
    while (client.connected()) {            // Schleife, während der Client verbunden ist
      if (client.available()) {             // wenn es Bytes gibt, die vom Client gelesen werden müssen,
        char c = client.read();             // Byte lesen und dann
        Serial.write(c);                    // auf den seriellen Monitor ausgeben
        header += c;
        if (c == '\n') {                    // Wenn es sich bei dem Byte um ein Zeilenumbruchzeichen handelt
          // Wenn die aktuelle Zeile leer ist, dann schreibe zwei Zeilenumbruchzeichen in einer Zeile.
          // Das ist das Ende der Client-HTTP-Anforderung, also sende eine Antwort:
          if (currentLine.length() == 0) {
            // HTTP-Header beginnen immer mit einem Antwortcode (z.B. HTTP/1.1 200 OK)
            // und ein Content-Typ, damit der Client weiß, was kommt, dann eine Leerzeile:)
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // Aktiviert und deaktiviert die GPIOs
            if (header.indexOf("GET /26/on") >= 0) {
              Serial.println("GPIO 26 on");
              output26State = "on";
              digitalWrite(output26, HIGH);
            } else if (header.indexOf("GET /26/off") >= 0) {
              Serial.println("GPIO 26 off");
              output26State = "off";
              digitalWrite(output26, LOW);              
            } 
            
            else if (header.indexOf("GET /27/on") >= 0) {
              Serial.println("GPIO 27 on");
              output27State = "on";
              digitalWrite(output27, HIGH);
            } else if (header.indexOf("GET /27/off") >= 0) {
              Serial.println("GPIO 27 off");
              output27State = "off";
              digitalWrite(output27, LOW);
            } 
            
            
            
            else if (header.indexOf("GET /13/on") >= 0) {
              Serial.println("GPIO 13 on");
              output13State = "on";
              digitalWrite(output13, HIGH);
            } else if (header.indexOf("GET /13/off") >= 0) {
              Serial.println("GPIO 13 off");
              output13State = "off";
              digitalWrite(output13, LOW);
            }




              
            
            // Anzeigen der HTML-Webseite
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS Style on/off Buttons
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #FF0D0D;}</style></head>");
            
            // Webseite Kopf
            client.println("<body><h1>ESP32 Web Server</h1>");
            
            // Anzeigen des aktuellen Zustands und der Ein-/Aus-Tasten für GPIO 26  
            client.println("<p>GPIO 26 - Status " + output26State + "</p>");
            // Wenn der output26State deaktiviert ist, wird die ON-Taste angezeigt      
            if (output26State=="off") {
              client.println("<p><a href=\"/26/on\"><button class=\"button\">OFF</button></a></p>");
            } else {
              client.println("<p><a href=\"/26/off\"><button class=\"button button2\">ON</button></a></p>");
            } 
               
            // Anzeigen des aktuellen Zustands und der Ein-/Aus-Tasten für GPIO 27 
            client.println("<p>GPIO 27 - Status " + output27State + "</p>");
            // Wenn der output27State deaktiviert ist, wird die ON-Taste angezeigt      
            if (output27State=="off") {
              client.println("<p><a href=\"/27/on\"><button class=\"button\">OFF</button></a></p>");
            } else {
              client.println("<p><a href=\"/27/off\"><button class=\"button button2\">ON</button></a></p>");
            }

            // Anzeigen des aktuellen Zustands und der Ein-/Aus-Tasten für GPIO 13 
            client.println("<p>GPIO 13 - Status " + output13State + "</p>");
            // Wenn der output13State deaktiviert ist, wird die ON-Taste angezeigt      
            if (output13State=="off") {
              client.println("<p><a href=\"/13/on\"><button class=\"button\">OFF</button></a></p>");
            } else {
              client.println("<p><a href=\"/13/off\"><button class=\"button button2\">ON</button></a></p>");
            }


            
            client.println("</body></html>");
            
            // Die HTTP-Antwort endet mit einer weiteren Leerzeile
            client.println();
             break;
          } else { 
            currentLine = "";
          }
        } else if (c != '\r') {  // Wenn etwas anderes als ein Return-Zeichen dann,
          currentLine += c;      // füge es am Ende der currentLine hinzu
        }
      }
    }
    // Lösche header variable
    header = "";
    // Schließe Verbindung
    client.stop();
    Serial.println("Client getrennt");
    Serial.println("");
  }
}
