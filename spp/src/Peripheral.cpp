
#include <string.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Peripheral.h>
#include <SoftwareSerial.h>

#define DEVICE_ID_LEN (8)         //it is 8 bytes
#define PARENT_DEVICE_ID_LEN (17) //it is 8 bytes

char dev_id[DEVICE_ID_LEN];

#define RX (13) //(14) // *** PB, Pin 0
#define TX (15) //(12) // *** PB, Pin 3

static SoftwareSerial *perSerial = new SoftwareSerial(RX, TX, false, 256);

bool Peripheral::isConnected()
{
    //return digitalRead(this->pin_number))==1?true:false;
    return true;
}

String Peripheral::getDeviceID()
{
    String cmd = "{\"GDI\":\"\"}";
    perSerial->begin(19200);

    perSerial->flush();

    perSerial->println(cmd);
    Serial.println(cmd);

    int i = 0;
    while (!perSerial->available())
    {
        delay(1);
        if (i++ >= 3000)
            return "NO_RESPONSE";
    }

    i = 0;

    String str = "";
    while (perSerial->available())
    {
        // dev_id[i] = perSerial->read();
        str = perSerial->readString();
        i++;
    }
    dev_id[i] = '\0';

    // return dev_id;
    return str;
}
String Peripheral::getDeviceStatus()
{
    return "Connected yeye";
}

String Peripheral::setDeviceStatus()
{

    return "Success device status set";
}
