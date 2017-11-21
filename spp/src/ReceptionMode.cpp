#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <json_parser.h>
#include <ReceptionMode.h>

const char *ssid = "Techies2.4";
const char *password = "passwordis1to8";
WiFiServer server(137);

void ReceptionMode ::init()
{
  WiFi.begin(ssid, password);
  // Start TCP server.
  server.begin();
}

void ReceptionMode ::receiveCommand()
{
  // Check if module is still connected to WiFi.
  if (WiFi.status() != WL_CONNECTED)
  {
    while (WiFi.status() != WL_CONNECTED)
    {
      delay(500);
    }
    // Print the new IP to Serial.
    printWiFiStatus();
  }

  WiFiClient client = server.available();

  if (client)
  {
    Serial.println("Client connected.");

    while (client.connected())
    {
      if (client.available())
      {
        uint8_t *buff;
        //char command = client.read();
        // String command = client.readStringUntil('\r');
        String command = client.readString();
        Serial.println(command);
      }
    }
    Serial.println("Client disconnected.");
    client.stop();
  }
}

void ReceptionMode :: printWiFiStatus()
{
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}