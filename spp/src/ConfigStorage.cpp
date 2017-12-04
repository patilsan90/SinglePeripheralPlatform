#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <EEPROM.h>
#include <JSONParser.h>
#include <ConfigStorage.h>

char ConfigStorage::buffer[512] = {};
int ConfigStorage::size = 0;

void ConfigStorage ::loadConfiguration()
{
  EEPROM.begin(512);

  memset(ConfigStorage::buffer, '\0', sizeof(ConfigStorage::buffer));

  int i = 0;
  uint8_t ch;
  char chr;
  do
  {
    ch = EEPROM.read(i);
    ConfigStorage::buffer[i] = (char)ch;
    i++;
    chr = (char)ch;
  } while (chr != '}');
  ConfigStorage::size = i;

  EEPROM.commit();
  EEPROM.end();

  for (i = 0; i < ConfigStorage::size; i++)
  {
    Serial.print(ConfigStorage::buffer[i]);
  }
  buffer[i] = '\0';

  JSONParser *parser = new JSONParser();
  parser->parse(buffer);

  for (int i = 0; i < parser->total_pairs; i++)
  {
    if (strcmp(parser->pairs[i].key, "owner_id") == 0)
      this->owner_id = parser->pairs[i].val;
    else if (strcmp(parser->pairs[i].key, "transact_server_url") == 0)
      this->server_url = parser->pairs[i].val;
    else if (strcmp(parser->pairs[i].key, "wifi_ssid") == 0)
      this->wifi_ssid = parser->pairs[i].val;
    else if (strcmp(parser->pairs[i].key, "wifi_psw") == 0)
      this->wifi_psw = parser->pairs[i].val;
    else if (strcmp(parser->pairs[i].key, "update_url") == 0)
      this->update_url = parser->pairs[i].val;
    else if (strcmp(parser->pairs[i].key, "configure_url") == 0)
      this->configure_url = parser->pairs[i].val;

    Serial.printf("KEY = %s", parser->pairs[i].key);
    Serial.printf("   VALUE = %s \n", parser->pairs[i].val);
  }
  Serial.printf("WIFI SSID = %s \n", this->wifi_ssid);
  Serial.printf("WIFI PSW = %s \n", this->wifi_psw);
}

void ConfigStorage ::saveConfiguration(String inputBuffer)
{

  char buffer[512];
  memset(buffer, '\0', sizeof(buffer));
  inputBuffer.toCharArray(buffer, 512);

  EEPROM.begin(512);
  int i = 0;
  int len = strlen(buffer);
  for (i = 0; i < len; i++)
  {
    Serial.print(buffer[i]);
    EEPROM.write(i, buffer[i]);
  }

  EEPROM.commit();
  EEPROM.end();
}

void ConfigStorage ::saveConfiguration()
{
  String local_ip = this->ipToString(WiFi.localIP());

  char *current_ip = (char *)malloc(sizeof(char) * (local_ip.length() + 1));
  memset(current_ip, '\0', sizeof(current_ip));
  local_ip.toCharArray(current_ip, local_ip.length() + 1);

  if (this->local_ip == NULL || strncmp(this->local_ip, current_ip, (local_ip.length() + 1)) != 0)
  {
    //ip is changed update to server also.
    this->local_ip = current_ip;
  }

  String str = "{";
  str += "\"wifi_ssid\":\"" + (String)this->wifi_ssid + "\",";
  str += "\"wifi_psw\":\"" + (String)this->wifi_psw + "\",";
  str += "\"owner_id\":\"" + (String)this->owner_id + "\",";
  str += "\"server_url\":\"" + (String)this->server_url + "\",";
  str += "\"update_url\":\"" + (String)this->update_url + "\",";
  str += "\"configure_url\":\"" + (String)this->configure_url + "\",";
  str += "\"local_ip\":\"" + (String)this->local_ip + "\",";
  str += "\"peripheral_id\":\"" + (String)this->peripheral_id + "\"";
  str += "}";

  Serial.println("New OBject to store");
  Serial.print(str);

  this->saveConfiguration(str);
}

OPERATION_MODE ConfigStorage ::getOperarionMode()
{
  if (this->wifi_ssid != NULL)
    return e_RECEPTION_MODE;
  return e_CONFIG_MODE;
}

String ConfigStorage ::ipToString(IPAddress ip)
{
  String s = "";
  for (int i = 0; i < 4; i++)
    s += i ? "." + String(ip[i]) : String(ip[i]);
  return s;
}