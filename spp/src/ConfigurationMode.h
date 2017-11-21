#ifndef __CONFIGURATION_MODE__
#define __CONFIGURATION_MODE__

#include <ESP8266WebServer.h>


class ServerMode
{
public:
  //void handle_config_request();
  void init();

  void handleClient();
};

#endif
