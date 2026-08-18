/*************************************************************************************************
                                      PROGRAMMINFO
**************************************************************************************************
  RoboCar
  Funktion: ESP32 WEB Server Richtungssteuerung und Speedcontrol 40%-100%, AP

**************************************************************************************************
  Version: 18.08.2026
**************************************************************************************************
  Board: ESP32 DEV KIT V4 Boardverwalter: ESP32 Dev Module V3.3.11
  https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
  http://arduino.esp8266.com/stable/package_esp8266com_index.json
  https://adafruit.github.io/arduino-board-index/package_adafruit_index.json
**************************************************************************************************
  Libraries:
**************************************************************************************************
  C++ Arduino IDE V1.8.19

**************************************************************************************************
  Einstellungen:
  https://dl.espressif.com/dl/package_esp32_index.json
  http://dan.drown.org/stm32duino/package_STM32duino_index.json
  http://arduino.esp8266.com/stable/package_esp8266com_index.json

          Motor A MotorB
          IN1 IN2 IN3 IN4
  Vorwärts  1   0   1   0
  Rückwärts 0   1   0   1
  rechts    1   0   0   0
  links     0   0   1   0

  const int pwmPin = 18;
  // Motor 1
  int motor1Pin1 = 2; //vor
  int motor1Pin2 = 0; //zurück
  // Motor 2
  int motor2Pin1 = 4; //rechts
  int motor2Pin2 = 16; //links

  L298N Infos:
  https://www.digi-electronics.de/de/blogs/l298n-motor-driver-guide-pinout-wiring-pwm-speed-control-troubleshooting/260.html

**************************************************************************************************/
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "RoboCar";
const char* password = "";

const int pwmPin = 18; // GPIO pin for PWM output
const int pwmChannel = 0;   // Channel speed (0–15)
const int pwmFreq = 5000;   // Frequency in Hz
const int pwmResolution = 8; // Resolution in bits (1–16)
const int res = 8; // 2^8 = 256


int value = 256;
int speed = 128;
WebServer server(80);

// Motor 1
int motor1Pin1 = 2; //vor
int motor1Pin2 = 0; //zurück

// Motor 2
int motor2Pin1 = 4; //rechts
int motor2Pin2 = 16; //links

// PWM Einstellungen
const int freq = 30000;
const int resolution = 8;
int dutyCycle = 0;

String valueString = String(0);

void handleRoot() {
  const char html[] PROGMEM = R"rawliteral(
  <!DOCTYPE HTML><html>
  <head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="icon" href="data:,">
    <style>
      html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center; }
      .button { -webkit-user-select: none; -moz-user-select: none; -ms-user-select: none; 
      user-select: none; background-color: #00BFFF; border: none; 
      color: white; padding: 12px 28px; text-decoration: none; font-size: 26px; margin: 1px; 
      width: 150px; height: 60px; cursor: pointer; }
      .button2 {background-color: #FE2E2E; width: 150px; height: 60px;}
    </style>
    <script>
      function moveForward() { fetch('/forward'); }
      function moveLeft() { fetch('/left'); }
      function stopRobot() { fetch('/stop'); }
      function moveRight() { fetch('/right'); }
      function moveReverse() { fetch('/reverse'); }

      function updateMotorSpeed(pos) {
        document.getElementById('motorSpeed').innerHTML = pos;
        fetch(`/speed?value=${pos}`);
      }
    </script>
  </head>
  <body>
    <h1>RoboCar</h1>
    <p><button class="button" onclick="moveForward()">vor</button></p>
    <div style="clear: both;">
      <p>
        <button class="button" onclick="moveLeft()">links</button>
        <button class="button button2" onclick="stopRobot()">stopp</button>
        <button class="button" onclick="moveRight()">rechts</button>
      </p>
    </div>
    <p><button class="button" onclick="moveReverse()">zurueck</button></p>
    <p>Motor Speed: <span id="motorSpeed">0</span></p>

<style>
  #motorSlider {
    width: 500px;
    height: 30px;
  }
</style>

<input
  type="range"
  min="40"
  max="100"
  step="10"
  id="motorSlider"
  oninput="updateMotorSpeed(this.value)"
  value="0"
/>   
     </html>)rawliteral";
  server.send(200, "text/html", html);
}

void handleForward() {
  Serial.println("vor");
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  server.send(200);
}

void handleReverse() {
  Serial.println("zurueck");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  server.send(200);
}

void handleLeft() {
  Serial.println("links");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  server.send(200);
}
void handleRight() {
  Serial.println("rechts");
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  server.send(200);
}

void handleStop() {
  Serial.println("stopp");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  server.send(200);
}

void handleSpeed() {
  if (server.hasArg("value")) {
    valueString = server.arg("value");
    int value = valueString.toInt();
    if (value == 0) {
      ledcWrite(pwmPin, 0);
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, LOW);
    } else {

      dutyCycle = (value * 3);
      ledcWrite(pwmPin, dutyCycle);
      Serial.println("Motor speed " + String(value));
      Serial.println("value " + String(value));
    }
  }
  server.send(200);
}

void setup() {
  Serial.begin(115200);
  ledcAttach(pwmPin, pwmFreq, res); // channel is chosen automatically
  // ledcAttachChannel(pwmPin, pwmFreq, res, pwmChannel); // choose channel youself

  // Motor pins
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);


  // ESP access point
  Serial.print("Set Access Point");
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP Adresse: ");
  Serial.println(IP);

  // routes
  server.on("/", handleRoot);
  server.on("/forward", handleForward);
  server.on("/left", handleLeft);
  server.on("/stop", handleStop);
  server.on("/right", handleRight);
  server.on("/reverse", handleReverse);
  server.on("/speed", handleSpeed);

  // Start Server
  server.begin();
}

void loop() {
  server.handleClient();
}
