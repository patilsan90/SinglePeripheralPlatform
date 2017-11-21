#ifndef __RECEPTION_MODE__
#define __RECEPTION_MODE__

#include <ESP8266WebServer.h>

class ReceptionMode
{
public:
  //void handle_config_request();
  void init();

  void receiveCommand();

  void printWiFiStatus();
};

#endif
