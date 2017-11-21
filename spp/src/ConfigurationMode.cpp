#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <ConfigurationMode.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <json_parser.h>
#include "ConfigStorage.h"
ESP8266WebServer config_server(1337);
IPAddress apIP(10, 10, 10, 1); // Private network address: local & gateway

String wifi_name;
String wifi_psw;
String room_name;
int room_id;
int owner_id;
int house_id;

static void handle_config_request()
{
  //config_server.sendHeader("Connection", "close");
  //config_server.sendHeader("Access-Control-Allow-Origin", "*");
  //config_server.send(200, "text/plain", "New hello from esp8266!");
  char input_buffer[100];
  JSONParser json_parser;

  if (config_server.hasArg("plain") == true)
  {
    String message = config_server.arg("plain");
    ConfigStorage *storage = new ConfigStorage;
    storage->saveConfiguration(message);
    String msg = "{ \"response\":\"e_DEVICE_CONFIGURED\", \"message\": \"";
    msg += WiFi.macAddress();
    msg += "\"}";

    config_server.send(200, "text/plain", msg);

    Serial.println("*********");

    Serial.println(message);
    Serial.println("*********");
    Serial.println(msg);
    Serial.println("*********");

    // memset(input_buffer, '\0', sizeof(input_buffer));
    // message.toCharArray(input_buffer, 100);
    // Serial.println(json_parser.get_key(input_buffer,"Dev"));
  }
  else
  {
    Serial.println("Error: No Data received");
  }
}

void ServerMode ::init()
{
  ServerMode serverMode;
  Serial.println("In Configuration mode");
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0)); // subnet FF FF FF 00

  boolean result = WiFi.softAP("SmartHomeDevCon", "transactsmarthome");
  if (result == true)
  {
    Serial.println("Smart home configuration mode is Ready");
  }
  else
  {
    Serial.println("Smart home configuration mode Failed!");
  }

  IPAddress myIP = WiFi.softAPIP(); //Get IP address
  Serial.print("HotSpt IP:");
  Serial.println(myIP);

  config_server.on("/smart_home/device/configure", handle_config_request); //Which routine to handle at root location
  config_server.begin();                                                   //Start server
  Serial.println("HTTP server started");
}

void ServerMode::handleClient()
{
  config_server.handleClient();
}