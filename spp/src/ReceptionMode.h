#ifndef __RECEPTION_MODE__
#define __RECEPTION_MODE__

#include <ESP8266WebServer.h>
#include "StorageUnit.h"

class ReceptionMode
{
public:
  void init(StorageUnit *storage);
  String getUpdates();

  void printWiFiStatus();
  int updateLocalIPToServer();

private:
  bool is_peripheral_change;
  String ipToString(IPAddress ip);
  bool isIPChanged();
};

#endif
