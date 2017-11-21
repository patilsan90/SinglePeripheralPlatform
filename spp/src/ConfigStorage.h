#ifndef __CONFIG_STORAGE__
#define __CONFIG_STORAGE__

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <json_parser.h>
#include <ConfigurationMode.h>

//using namespace transact;

class ConfigStorage
{
public:

  static char buffer[512];
  static int size;
  char *ssid;
  String wifi_ssid = "NO";
  String wifi_psw = "NO";
  String owner_id = "NO";
  String house_id = "NO";
  String room_id = "NO";

  void loadConfiguration();
  void saveConfiguration(String inputBuffer);
};

#endif
