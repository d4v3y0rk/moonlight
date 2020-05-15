#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <WiFiClient.h>

const char *ssid = "Cityflicker";
const char *password = "Lmsobr22";

const String serverName = "https://d4v3y0rk.com/moon";
const String upServer = "https://d4v3y0rk.com/moon/up";

const int LEDONE = 16;
const int LEDTWO = 5;
const int LEDTHREE = 4;
const int LEDFOUR = 0;
const int LEDFIVE = 2;
const int LEDSIX = 14;
unsigned long lastTime = 0;
unsigned long timerDelay = 600000;
bool firstRun = true;

void lightItUp(const int leds)
{
  if (leds == 0)
  {
    digitalWrite(LEDONE, LOW);
    digitalWrite(LEDTWO, LOW);
    digitalWrite(LEDTHREE, LOW);
    digitalWrite(LEDFOUR, LOW);
    digitalWrite(LEDFIVE, LOW);
    digitalWrite(LEDSIX, LOW);
  }
  if (leds == 1)
  {
    digitalWrite(LEDONE, HIGH);
  }
  if (leds == 2)
  {
    digitalWrite(LEDONE, HIGH);
    digitalWrite(LEDTWO, HIGH);
  }
  if (leds == 3)
  {
    digitalWrite(LEDONE, HIGH);
    digitalWrite(LEDTWO, HIGH);
    digitalWrite(LEDTHREE, HIGH);
  }
  if (leds == 4)
  {
    digitalWrite(LEDONE, HIGH);
    digitalWrite(LEDTWO, HIGH);
    digitalWrite(LEDTHREE, HIGH);
    digitalWrite(LEDFOUR, HIGH);
  }
  if (leds == 5)
  {
    digitalWrite(LEDONE, HIGH);
    digitalWrite(LEDTWO, HIGH);
    digitalWrite(LEDTHREE, HIGH);
    digitalWrite(LEDFOUR, HIGH);
    digitalWrite(LEDFIVE, HIGH);
  }
  if (leds == 6)
  {
    digitalWrite(LEDONE, HIGH);
    digitalWrite(LEDTWO, HIGH);
    digitalWrite(LEDTHREE, HIGH);
    digitalWrite(LEDFOUR, HIGH);
    digitalWrite(LEDFIVE, HIGH);
    digitalWrite(LEDSIX, HIGH);
  }
}

void startUp()
{
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(LEDONE, LOW);
  digitalWrite(LEDTWO, LOW);
  digitalWrite(LEDTHREE, LOW);
  digitalWrite(LEDFOUR, LOW);
  digitalWrite(LEDFIVE, LOW);
  digitalWrite(LEDSIX, LOW);
  delay(1000);
  digitalWrite(LEDONE, HIGH);
  delay(1000);
  digitalWrite(LEDTWO, HIGH);
  delay(1000);
  digitalWrite(LEDTHREE, HIGH);
  delay(1000);
  digitalWrite(LEDFOUR, HIGH);
  delay(1000);
  digitalWrite(LEDFIVE, HIGH);
  delay(1000);
  digitalWrite(LEDSIX, HIGH);
  delay(5000);
}

void setup()
{
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected to WiFi network.");
  
  pinMode(LEDONE, OUTPUT);
  pinMode(LEDTWO, OUTPUT);
  pinMode(LEDTHREE, OUTPUT);
  pinMode(LEDFOUR, OUTPUT);
  pinMode(LEDFIVE, OUTPUT);
  pinMode(LEDSIX, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  startUp();
}

void loop()
{
  if ((millis() - lastTime) > timerDelay || firstRun) {
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient ledNum;
      HTTPClient up;
      ledNum.begin(serverName.c_str(), "74 99 EA 91 DB 99 1A 4D 05 44 06 5F DB 60 1E C8 26 BA 34 4F");
      up.begin(upServer.c_str(), "74 99 EA 91 DB 99 1A 4D 05 44 06 5F DB 60 1E C8 26 BA 34 4F");
      int httpResponseCode = ledNum.GET();
      int UpResponseCode = up.GET();

      if (httpResponseCode > 0 && UpResponseCode > 0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = ledNum.getString();
        String onOrOff = up.getString();
        Serial.printf("Number of LEDS to light up: %s\n", payload.c_str());
        Serial.printf("Is the moon up? %s\n", onOrOff.c_str());
        if (onOrOff == "true") {
          Serial.println("The moon is up.");
          lightItUp(payload.toInt());
        } else {
          Serial.println("The moon is not up.");
          lightItUp(0);
        }
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      ledNum.end();
      up.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
    firstRun = false;
  }
}