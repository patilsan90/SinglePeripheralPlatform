#include <StorageUnit.h>
#include <JSONParser.h>
#include "FS.h"

void StorageUnit::init()
{
  Serial.println(F("Spiffs Storage Unit initializing....."));
  SPIFFS.begin();
}

int StorageUnit::convertStringToObj(String input)
{
  String msg;

  Serial.println(F("*********"));
  Serial.println(input);
  Serial.println(F("*********"));

  Serial.println(F("*****PARSING START****"));

  JSONParser *parser = new JSONParser();
  parser->parse(input);

  Serial.println(parser->total_pairs);
  int config_details_counter = 0;
  for (int i = 0; i < parser->total_pairs; i++)
  {
    if (strcmp(parser->pairs[i].key, "owner_id") == 0)
    {
      config_details_counter++;
      this->owner_id = (String)parser->pairs[i].val;
    }
    else if (strcmp(parser->pairs[i].key, "transact_server_url") == 0)
    {
      config_details_counter++;
      this->server_url = (String)parser->pairs[i].val;
    }
    else if (strcmp(parser->pairs[i].key, "wifi_ssid") == 0)
    {
      config_details_counter++;
      this->wifi_ssid = (String)parser->pairs[i].val;
    }
    else if (strcmp(parser->pairs[i].key, "wifi_psw") == 0)
    {
      config_details_counter++;
      this->wifi_psw = (String)parser->pairs[i].val;
    }
    else if (strcmp(parser->pairs[i].key, "update_url") == 0)
    {
      config_details_counter++;
      this->update_url = (String)parser->pairs[i].val;
    }
    else if (strcmp(parser->pairs[i].key, "configure_url") == 0)
    {
      config_details_counter++;
      this->configure_url = (String)parser->pairs[i].val;
    }

    Serial.print(parser->pairs[i].key);
    Serial.print(parser->pairs[i].val);
    Serial.println(" :: ");
  }

  if (config_details_counter >= 6)
    return 0;
  return -1;

  Serial.println(F("******PARSING DONE ......"));
}

int StorageUnit::saveConfiguration(String inputBuffer)
{
  this->init();
  if (this->convertStringToObj(inputBuffer) != 0)
    return -1;

  File file;
  SPIFFS.format();
  Serial.println(F("Spiffs formatted"));

  // Open file for writing
  file = SPIFFS.open("/wifi_ssid.txt", "w");
  if (!file)
  {
    Serial.println(F("wifi_ssid write open failed"));
  }
  else
  {
    Serial.println(F("====== Writing to SPIFFS wifi_ssid file ========="));
    file.println((String)this->wifi_ssid);
  }
  file.close();

  // Open file for writing
  file = SPIFFS.open("/wifi_psw.txt", "w");
  if (!file)
  {
    Serial.println(F("wifi_psw write open failed"));
  }
  else
  {
    Serial.println(F("====== Writing to SPIFFS wifi_psw file ========="));
    file.println((String)this->wifi_psw);
  }
  file.close();
  // Open file for writing
  file = SPIFFS.open("/owner_id.txt", "w");
  if (!file)
  {
    Serial.println(F("owner_id write open failed"));
  }
  else
  {
    Serial.println(F("====== Writing to SPIFFS owner_id file ========="));
    file.println((String)this->owner_id);
  }
  file.close();
  // Open file for writing
  file = SPIFFS.open("/server_url.txt", "w");
  if (!file)
  {
    Serial.println(F("server_url write open failed"));
  }
  else
  {
    Serial.println(F("====== Writing to SPIFFS server_url file ========="));
    file.println((String)this->server_url);
  }
  file.close();
  // Open file for writing
  file = SPIFFS.open("/update_url.txt", "w");
  if (!file)
  {
    Serial.println(F("update_url write open failed"));
  }
  else
  {
    Serial.println(F("====== Writing to SPIFFS update_url file ========="));
    file.println((String)this->update_url);
  }
  file.close();
  // Open file for writing
  file = SPIFFS.open("/configure_url.txt", "w");
  if (!file)
  {
    Serial.println(F("configure_url write open failed"));
  }
  else
  {
    Serial.println(F("====== Writing to SPIFFS configure_url file ========="));
    file.println((String)this->configure_url);
  }
  file.close();
  // Open file for writing
  file = SPIFFS.open("/local_ip.txt", "w");
  if (!file)
  {
    Serial.println(F("local_ip write open failed"));
  }
  else
  {
    Serial.println(F("====== Writing to SPIFFS local_ip file ========="));
    file.println((String)this->local_ip);
  }
  file.close();
  return 0;
}

void StorageUnit::loadConfiguration()
{
  String s;
  File file;

  // Open file for Reading
  file = SPIFFS.open("/wifi_ssid.txt", "r");
  if (!file)
  {
    Serial.println(F("wifi_ssid write open failed"));
  }
  else
  {
    Serial.println(F("====== Reading to SPIFFS wifi_ssid file ========="));
    this->wifi_ssid = file.readStringUntil('\n');
    Serial.println(this->wifi_ssid);
  }
  file.close();

  // Open file for Reading
  file = SPIFFS.open("/wifi_psw.txt", "r");
  if (!file)
  {
    Serial.println(F("wifi_psw write open failed"));
  }
  else
  {
    Serial.println(F("====== Reading to SPIFFS wifi_psw file ========="));
    this->wifi_psw = file.readStringUntil('\n'); //file.println((String)this->wifi_psw);
    Serial.println(this->wifi_psw);
  }
  file.close();
  // Open file for Reading
  file = SPIFFS.open("/owner_id.txt", "r");
  if (!file)
  {
    Serial.println(F("owner_id write open failed"));
  }
  else
  {
    Serial.println(F("====== Reading to SPIFFS owner_id file ========="));
    this->owner_id = file.readStringUntil('\n'); // file.println((String)this->owner_id);
    Serial.println(this->owner_id);
  }
  file.close();
  // Open file for Reading
  file = SPIFFS.open("/server_url.txt", "r");
  if (!file)
  {
    Serial.println(F("server_url write open failed"));
  }
  else
  {
    Serial.println(F("====== Reading to SPIFFS server_url file ========="));
    this->server_url = file.readStringUntil('\n'); //file.println((String)this->server_url);
    Serial.println(this->server_url);
  }
  file.close();
  // Open file for Reading
  file = SPIFFS.open("/update_url.txt", "r");
  if (!file)
  {
    Serial.println(F("update_url write open failed"));
  }
  else
  {
    Serial.println(F("====== Reading to SPIFFS update_url file ========="));
    this->update_url = file.readStringUntil('\n'); //file.println((String)this->update_url);
    Serial.println(this->update_url);
  }
  file.close();
  // Open file for Reading
  file = SPIFFS.open("/configure_url.txt", "r");
  if (!file)
  {
    Serial.println(F("configure_url write open failed"));
  }
  else
  {
    Serial.println(F("====== Reading to SPIFFS configure_url file ========="));
    this->configure_url = file.readStringUntil('\n'); // file.println((String)this->configure_url);
    Serial.println(this->configure_url);
  }
  file.close();
  // Open file for Reading
  file = SPIFFS.open("/local_ip.txt", "r");
  if (!file)
  {
    Serial.println(F("local_ip write open failed"));
  }
  else
  {
    Serial.println(F("====== Reading to SPIFFS local_ip file ========="));
    this->local_ip = file.readStringUntil('\n'); // file.println((String)this->local_ip);
    Serial.println(this->local_ip);
  }
  file.close();
}

OPERATION_MODE StorageUnit::getOperarionMode()
{
  if (this->wifi_ssid != NULL)
    return e_RECEPTION_MODE;
  return e_CONFIG_MODE;
}

String StorageUnit::ipToString(IPAddress ip)
{
  String s = "";
  for (int i = 0; i < 4; i++)
    s += i ? "." + String(ip[i]) : String(ip[i]);
  return s;
}

bool StorageUnit ::saveIP()
{
  String local_ip = this->ipToString(WiFi.localIP());

  if (this->local_ip.compareTo(local_ip) == 0)
  {
    //ip is changed update to server also.
    this->local_ip = local_ip;

    File file = SPIFFS.open("/local_ip.txt", "w");
    if (!file)
    {
      Serial.println(F("local_ip write open failed"));
    }
    else
    {
      Serial.println(F("====== Writing to SPIFFS local_ip file ========="));
      file.println(this->local_ip);
    }
    file.close();
  }
}
