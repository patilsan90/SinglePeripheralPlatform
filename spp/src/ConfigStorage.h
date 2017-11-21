#ifndef __CONFIG_STORAGE__
#define __CONFIG_STORAGE__

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <ConfigurationMode.h>

//using namespace transact;

class ConfigStorage
{
public:
  static char buffer[512];
  static int size;
  char *ssid = NULL;
  char *wifi_ssid = NULL;
  char *wifi_psw = NULL;
  char *owner_id = NULL;
  char *house_id = NULL;
  char *room_id = NULL;
  char *server_url = NULL;

  void loadConfiguration();
  void saveConfiguration(String inputBuffer);
};

#endif
