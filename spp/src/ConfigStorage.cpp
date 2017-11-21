#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <EEPROM.h>
#include <ConfigStorage.h>

char ConfigStorage::buffer[512] = {};
int ConfigStorage::size = 0;
void ConfigStorage ::loadConfiguration()
{
  EEPROM.begin(512);

  memset(ConfigStorage::buffer, '\0', sizeof(ConfigStorage::buffer));

  int i = 0;
  uint8_t ch;
  do
  {
    ch = EEPROM.read(i);
    ConfigStorage::buffer[i] = (char)ch;
    i++;
  } while (ch != 255);
  ConfigStorage::size = i - 2;
  /*EEPROM.read(0, storage.wifi_ssid);
  EEPROM.get(0 + sizeof(storage.wifi_ssid), storage.wifi_psw);
  EEPROM.get(0 + sizeof(storage.wifi_ssid) + sizeof(storage.wifi_psw), storage.owner_id);
  EEPROM.get(0 + sizeof(storage.wifi_ssid) + sizeof(storage.wifi_psw) + sizeof(storage.owner_id), storage.house_id);
  EEPROM.get(0 + sizeof(storage.wifi_ssid) + sizeof(storage.wifi_psw) + sizeof(storage.owner_id) + sizeof(storage.house_id), storage.room_id);
  */
  EEPROM.commit();
  EEPROM.end();

  Serial.println("Reading buffer ");
  
  for (i = 0; i < ConfigStorage::size; i++)
  {
    Serial.print(ConfigStorage::buffer[i]);
  }
  Serial.println("Reading buffer end");
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

  /*EEPROM.put(0 + sizeof(storage.wifi_ssid), storage.wifi_psw);
  EEPROM.put(0 + sizeof(storage.wifi_ssid) + sizeof(storage.wifi_psw), storage.owner_id);
  EEPROM.put(0 + sizeof(storage.wifi_ssid) + sizeof(storage.wifi_psw) + sizeof(storage.owner_id), storage.house_id);
  EEPROM.put(0 + sizeof(storage.wifi_ssid) + sizeof(storage.wifi_psw) + sizeof(storage.owner_id) + sizeof(storage.house_id), storage.room_id);
*/
  EEPROM.commit();
  EEPROM.end();
}
