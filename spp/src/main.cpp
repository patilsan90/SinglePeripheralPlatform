#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <ConfigurationMode.h>
#include <ReceptionMode.h>
#include <Peripheral.h>
#include <StorageUnit.h>
#include "pin_configuration.h"

void client_mode();
void printWiFiStatus();
void configure();

#define PERIPHRAL_CONNECTION_STATUS_PIN (0)

OPERATION_MODE mode;
//mode 1 is AP mode
// mode 0 will be normal mode

ServerMode serverMode;
ReceptionMode *dataReceptionMode = new ReceptionMode();
static StorageUnit *storage = new StorageUnit();

void peripheralConnectedIntr();

void setup()
{
  pinMode(PIN_PERIPHERAL_ACTIVATE_VCC, OUTPUT);
  digitalWrite(PIN_PERIPHERAL_ACTIVATE_VCC, 0);
  Serial.begin(115200);
  delay(2000);
  digitalWrite(PIN_PERIPHERAL_ACTIVATE_VCC, 1);

  /* TODO 
   * Enable power for peripheral
   */
  pinMode(LED_BUILTIN, OUTPUT); // Initialize the LED_BUILTIN pin as an output
                                //pinMode(PERIPHRAL_CONNECTION_STATUS_PIN, INPUT_PULLUP);
                                //attachInterrupt(digitalPinToInterrupt(PERIPHRAL_CONNECTION_STATUS_PIN), peripheralConnectedIntr, FALLING);

  pinMode(PIN_IS_CONNECTED, INPUT);

  storage->loadConfiguration();
  mode = storage->getOperarionMode();

  delay(1000);
  Serial.println("WIFI SSID = :: " + storage->wifi_ssid);
  Serial.println("WIFI PSW = :: " + storage->wifi_psw);
  //mode = e_CONFIG_MODE;

  // TODO
  // Below commented IF-ELSE is temporary just for testing mode purpose,
  // need to uncomment it in future.

  if (mode == e_CONFIG_MODE)
  {
    Serial.println(F("INIT in Config Mode"));
    serverMode.init();
  }
  else if (mode == e_RECEPTION_MODE)
  {
    delay(5000);
    //serverMode.init();
    Serial.println(F("INIT in Reception Mode"));
    dataReceptionMode->init(storage);
  }
}

void loop()
{

  int is_connected = digitalRead(PIN_IS_CONNECTED);
  Serial.printf("is Connected status :: %d\n", is_connected);
  // delay(1000);
  if (mode == e_CONFIG_MODE)
  {
    Serial.println(F("Working in Config Mode"));
    Serial.printf("Stations connected = %d \n", WiFi.softAPgetStationNum());
    serverMode.handleClient(); //Handle client requests
    delay(1000);
  }
  else if (mode == e_RECEPTION_MODE)
  {
    Serial.println(F("Working in Reception Mode"));
    Serial.println("Server URL = ::" + storage->server_url);
    dataReceptionMode->start();
  }
}
