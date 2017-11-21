#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <ConfigurationMode.h>
#include <ConfigStorage.h>
#include <ReceptionMode.h>

void client_mode();
void printWiFiStatus();
void configure();


int mode = 1;
//mode 1 is AP mode
// mode 0 will be normal mode

ServerMode serverMode;
ReceptionMode dataReceptionMode;
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT); // Initialize the LED_BUILTIN pin as an output
  Serial.begin(19200);
  mode = 1;

  if (mode == 1)
  {
    serverMode.init();
  }
  else if (mode == 0)
  {
    dataReceptionMode.init();
  }
}

// the loop function runs over and over again forever
void loop()
{

  if (mode == 1)
  {
    Serial.printf("Stations connected = %d\n", WiFi.softAPgetStationNum());

    ConfigStorage cstorage;
    cstorage.loadConfiguration();
    serverMode.handleClient(); //Handle client requests
    delay(3000);

  }
  else if (mode == 0)
  {
    dataReceptionMode.receiveCommand();
  }
}


