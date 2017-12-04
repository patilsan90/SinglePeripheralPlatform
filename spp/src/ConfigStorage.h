#ifndef __CONFIG_STORAGE__
#define __CONFIG_STORAGE__

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <ConfigurationMode.h>

//using namespace transact;

typedef enum OPERATION_MODE {
  e_CONFIG_MODE,
  e_RECEPTION_MODE,
} OPERATION_MODE;

class ConfigStorage
{
public:
  static char buffer[512];
  static int size;

  char *wifi_ssid = NULL;
  char *wifi_psw = NULL;
  char *owner_id = NULL;
  char *server_url = NULL;
  char *update_url = NULL;
  char *configure_url = NULL;
  char *local_ip = NULL;
  char *peripheral_id = NULL;
  void loadConfiguration();
  void saveConfiguration(String inputBuffer);
  void saveConfiguration();
  
  OPERATION_MODE getOperarionMode();

  String ipToString(IPAddress ip);
};

#endif
