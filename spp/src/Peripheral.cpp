
#include <string.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Peripheral.h>

#define DEVICE_ID_LEN (8)         //it is 8 bytes
#define PARENT_DEVICE_ID_LEN (17) //it is 8 bytes

char dev_id[DEVICE_ID_LEN];

#define RESP_WAIT_TIME_OUT 3000 //in ms
//static SoftwareSerial *perSerial = new SoftwareSerial(RX, TX, false, 256);

bool Peripheral::isConnected()
{
    //return digitalRead(this->pin_number))==1?true:false;
    return true;
}

String Peripheral::getDeviceType()
{
    String cmd = "{\"GDT\":\"\"}";
    perSerial->flush();
    perSerial->println(cmd);
    Serial.println(cmd);
    int i = 0;
    while (!perSerial->available())
    {
        delay(1);
        if (i++ >= RESP_WAIT_TIME_OUT)
            return "NO_RESPONSE";
    }

    String str = "";
    while (perSerial->available())
    {
        str = perSerial->readString();
    }
    return str;
}

void Peripheral::setDeviceRegID(String reg_id)
{
    String cmd = "{\"SDI\":\"" + reg_id + "\"}";
    perSerial->flush();
    perSerial->println(cmd);
    delay(2000);
    Serial.println(cmd);
}

String Peripheral::getDeviceRegID()
{
    String cmd = "{\"GDI\":\"\"}";

    perSerial->flush();

    perSerial->println(cmd);
    Serial.println(cmd);

    int i = 0;
    while (!perSerial->available())
    {
        delay(1);
        if (i++ >= RESP_WAIT_TIME_OUT)
            return "NO_RESPONSE";
    }

    //   i = 0;

    String str = "";
    while (perSerial->available())
    {
        // dev_id[i] = perSerial->read();
        str = perSerial->readString();
        //   i++;
    }
    // dev_id[i] = '\0';

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
