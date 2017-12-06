#ifndef __STORAGE_UNIT__
#define __STORAGE_UNIT__
#include <string.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>

typedef enum OPERATION_MODE {
  e_CONFIG_MODE,
  e_RECEPTION_MODE,
} OPERATION_MODE;

/*  Below code is to optimize overall code, take it in future. */
/*
typedef enum CONFIG_PARAMETER {
  WIFI_SSID,
  WIFI_PSW,
  OWNER_ID,
  SERVER_URL,
  UPDATE_URL,
  CONFIGURE_URL,
  LOCAL_IP,
  CONFIG_PARAMETER_COUNT
} CONFIG_PARAMETER;
*/
class StorageUnit
{
public:
  /*  Below code is to optimize overall code, uncomment and take it in future. */
  // String configs[CONFIG_PARAMETER_COUNT];

  String wifi_ssid;
  String wifi_psw;
  String owner_id;
  String server_url;
  String update_url;
  String configure_url;
  String local_ip;

  int saveConfiguration(String input);
  void loadConfiguration();
  bool saveIP();

  OPERATION_MODE getOperarionMode();

private:
  void init();
  int convertStringToObj(String input);
  String ipToString(IPAddress ip);
};

#endif
