#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <ConfigurationMode.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <JSONParser.h>
#include <ConfigStorage.h>

ESP8266WebServer config_server(1337);
IPAddress apIP(10, 10, 10, 1); // Private network address: local & gateway

static void handle_config_request()
{
  //config_server.sendHeader("Connection", "close");
  //config_server.sendHeader("Access-Control-Allow-Origin", "*");
  //config_server.send(200, "text/plain", "New hello from esp8266!");

  if (config_server.hasArg("plain") == true)
  {
    String msg;
    String message = config_server.arg("plain");
    ConfigStorage *storage = new ConfigStorage;
    storage->saveConfiguration(message);

    Serial.println("*********");
    Serial.println(message);
    Serial.println("*********");

    Serial.println("*****PARSING START****");

    JSONParser *parser = new JSONParser();
    parser->parse(message);

    Serial.println(parser->total_pairs);
    int config_details_counter = 0;
    for (int i = 0; i < parser->total_pairs; i++)
    {
      if (strcmp(parser->pairs[i].key, "owner_id") == 0)
      {
        config_details_counter++;
        storage->owner_id = parser->pairs[i].val;
      }
      else if (strcmp(parser->pairs[i].key, "transact_server_url") == 0)
      {
        config_details_counter++;
        storage->server_url = parser->pairs[i].val;
      }
      else if (strcmp(parser->pairs[i].key, "wifi_ssid") == 0)
      {
        config_details_counter++;
        storage->wifi_ssid = parser->pairs[i].val;
      }
      else if (strcmp(parser->pairs[i].key, "wifi_psw") == 0)
      {
        config_details_counter++;
        storage->wifi_psw = parser->pairs[i].val;
      }
      else if (strcmp(parser->pairs[i].key, "update_url") == 0)
      {
        config_details_counter++;
        storage->update_url = parser->pairs[i].val;
      }
      else if (strcmp(parser->pairs[i].key, "configure_url") == 0)
      {
        config_details_counter++;
        storage->configure_url = parser->pairs[i].val;
      }

      Serial.print(parser->pairs[i].key);
      Serial.print(parser->pairs[i].val);
      Serial.println(" :: ");
    }
    Serial.println("******PARSING DONE ......");

    if (config_details_counter >= 6)
    {
      msg = "{ \"is_success\":\"true\", \"mac_addr\": \"";
      msg += WiFi.macAddress();
      msg += "\"}";
      config_server.send(200, "text/plain", msg);
      delay(2000);
      ESP.reset();
    }
    else
    {
      msg = "{ \"is_success\":\"false\"}";
      config_server.send(200, "text/plain", msg);
    }
  }
  else
  {
    Serial.println("Error: No Data received");
  }
}

void ServerMode ::closeAPMode()
{
  config_server.close();
  config_server.stop();
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

  config_server.begin(); //Start server
  Serial.println("HTTP server started");
}

void ServerMode::handleClient()
{
  config_server.handleClient();
}