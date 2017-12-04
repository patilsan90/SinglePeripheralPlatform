#ifndef __PERIPHERAL__
#define __PERIPHERAL__

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

class Peripheral
{
  int pin_number;

public:
  Peripheral(int pin_number)
  {
    this->pin_number=pin_number;
  }
  
  bool isConnected();
  String getDeviceID();
  String getDeviceStatus();
  String setDeviceStatus();
};

#endif
