#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <ConfigurationMode.h>
#include <ReceptionMode.h>
#include <Peripheral.h>
#include <StorageUnit.h>

//#include <FirebaseArduino.h>

void client_mode();
void printWiFiStatus();
void configure();

#define PERIPHRAL_CONNECTION_STATUS_PIN (0)
#define NO_ID ("NO_ID")

OPERATION_MODE mode;
//mode 1 is AP mode
// mode 0 will be normal mode

ServerMode serverMode;
ReceptionMode *dataReceptionMode = new ReceptionMode();
static StorageUnit *storage = new StorageUnit();

static Peripheral *per = new Peripheral(PERIPHRAL_CONNECTION_STATUS_PIN);
void peripheralConnectedIntr();

void sendPeripheralsListToServer();
void gatherPeripherals();
void updatePeripheralIDs();
bool isGatherPeriList = true;

void setup()
{
  Serial.begin(115200);
  delay(2000);

  pinMode(LED_BUILTIN, OUTPUT); // Initialize the LED_BUILTIN pin as an output
  pinMode(PERIPHRAL_CONNECTION_STATUS_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PERIPHRAL_CONNECTION_STATUS_PIN), peripheralConnectedIntr, FALLING);

  // storage->loadConfiguration();

  //mode = storage->getOperarionMode();

  delay(1000);
  Serial.println("WIFI SSID = :: " + storage->wifi_ssid);
  Serial.println("WIFI PSW = :: " + storage->wifi_psw);
  mode = e_CONFIG_MODE;

  // TODO
  // Below commented IF-ELSE is temporary just for testing mode purpose,
  // need to uncomment it in future.

  if (mode == e_CONFIG_MODE)
  {
    Serial.println("INIT in Config Mode");
    serverMode.init();
  }
  else if (mode == e_RECEPTION_MODE)
  {
    serverMode.init();
    Serial.println("INIT in Reception Mode");
    dataReceptionMode->init(storage);
  }
}

// the loop function runs over and over again forever

void peripheralConnectedIntr()
{
  Serial.println("New Peripheral connected interrupt");
  if (WiFi.status() == WL_CONNECTED)
  {
    //gatherPeripherals();
    //sendPeripheralsListToServer();
  }
}

void onReceptionMode();
void loop()
{
  if (mode == e_CONFIG_MODE)
  {
    Serial.println("Working in Config Mode");
    Serial.printf("Stations connected = %d \n", WiFi.softAPgetStationNum());
    serverMode.handleClient(); //Handle client requests
    delay(2000);
  }
  else if (mode == e_RECEPTION_MODE)
  {
    onReceptionMode();
  }
}

void onReceptionMode()
{
  Serial.println("Working in Reception Mode");
  Serial.println("Server URL = ::" + storage->server_url);
  gatherPeripherals();
  if (WiFi.status() == WL_CONNECTED && isGatherPeriList == true)
  {
    gatherPeripherals();
    updatePeripheralIDs();
    sendPeripheralsListToServer();
  }

  if (WiFi.status() == WL_CONNECTED)
  {
    dataReceptionMode->updateLocalIPToServer();
    String output = dataReceptionMode->getUpdates();
    Serial.println("Output String :: " + output);
  }

  delay(2000);
}

void updatePeripheralIDs()
{
  //if (strcmp(storage->peripheral_id, NO_ID) == 0)
  {
    // get new id from server and assign it to peripheral
  }
}

void gatherPeripherals()
{
  //storage->peripheral_id = per->getDeviceID();
  Serial.println(per->getDeviceID());
  isGatherPeriList = false;
}

void sendPeripheralsListToServer()
{

  //if (strcmp(storage->peripheral_id, (char *)NO_ID) == 0)
  {
      //need to assign peripheral device id;
      // send type of device to server too.
  }
  //else
  {
    //send this peripheral id to server
  }
}
