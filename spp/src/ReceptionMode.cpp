#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <ESP8266HTTPClient.h>
#include <ReceptionMode.h>
#include <peripheral.h>

const char *ssid = "Techies2.4";
const char *password = "passwordis1to8";
WiFiServer server(137);

static StorageUnit *storage; // =new StorageUnit();
void ReceptionMode ::init(StorageUnit *storage1)
{
  storage = storage1;
  WiFi.hostname("SinglePeripheralPlatform");
  WiFi.mode(WIFI_AP_STA);
  //WiFi.mode(WIFI_STA);
  WiFi.begin(storage->wifi_ssid.c_str(), storage->wifi_psw.c_str());
  // Start TCP server.
  //server.begin();
}

void ReceptionMode ::printWiFiStatus()
{
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

bool ReceptionMode ::isIPChanged()
{
  return storage->saveIP();
}

int ReceptionMode ::updateLocalIPToServer()
{
  String payload;
  if (WiFi.status() == WL_CONNECTED)
  {
    if (!isIPChanged())
      return 0;

    HTTPClient http;
    String url = (String)storage->server_url + "/" + (String) "update_ip";
    http.begin(url);

    http.addHeader("Content-Type", "application/json");

    int device_id = 10;
    char dev_id_str[2];
    sprintf(dev_id_str, "%d", device_id);

    String ip = ipToString(WiFi.localIP());
    String device = "{ \"device_id\":" + (String)dev_id_str;
    device += ",\"device_phy_id\":\"" + WiFi.macAddress() + "\"";
    device += ",\"dev_mac_addr\":\"" + WiFi.macAddress() + "\"";
    device += ",\"local_ip_addr\":\"" + ip + "\"";
    device += "}";

    int httpCode = http.POST(device);
    payload = http.getString();                                 //Get the response payload
    Serial.println("UPDATE_IP Request URL:: " + url);           //Print Request URL
    Serial.println("UPDATE_IP Request Data:: " + device);       //Print Request Data
    Serial.printf("UPDATE_IP HTTP code:: %d\n", httpCode);      //Print HTTP return code
    Serial.println("UPDATE_IP Response Payload :: " + payload); //Print request response payload
    http.end();                                                 //Close connection
  }
  else
  {
    Serial.println("Error in WiFi connection establishment");
  }
  delay(1000); //Send a request every 1 second
  return (0);
}

String ReceptionMode ::getUpdates()
{
  String payload;
  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;
    String url = (String)storage->server_url + "/" + (String)storage->update_url;
    http.begin(url);

    http.addHeader("Content-Type", "application/json");

    int device_id = 10;
    char dev_id_str[2];

    sprintf(dev_id_str, "%d", device_id);
    String device = "{ \"device_id\":" + (String)dev_id_str;
    device += ",\"device_phy_id\":\"" + WiFi.macAddress() + "\"";
    device += ",\"dev_mac_addr\":\"" + WiFi.macAddress() + "\"";
    device += "}";

    int httpCode = http.POST(device);
    payload = http.getString();                       //Get the response payload
    Serial.println("Request URL:: " + url);           //Print Request URL
    Serial.println("Request Data:: " + device);       //Print Request Data
    Serial.printf("HTTP code:: %d\n", httpCode);      //Print HTTP return code
    Serial.println("Response Payload :: " + payload); //Print request response payload
    http.end();                                       //Close connection
  }
  else
  {
    Serial.println("Error in WiFi connection establishment");
  }
  delay(1000); //Send a request every 1 second
  return (payload);
}

String ReceptionMode ::ipToString(IPAddress ip)
{
  String s = "";
  for (int i = 0; i < 4; i++)
    s += i ? "." + String(ip[i]) : String(ip[i]);
  return s;
}
