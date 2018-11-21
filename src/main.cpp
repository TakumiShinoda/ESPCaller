#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "ServerObject.h"
#include "ChainArray.h"

#include "local_property.h"

#define TRY_CONNECT_AP 10

IPAddress ip(192, 168, 3, 1);
IPAddress subnet(255, 255, 255, 0);
ServerObject so;

void setup(){
  Serial.begin(9600);
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(APSSID, APPASS);
  WiFi.softAPConfig(ip, ip, subnet);
  so.begin();
}

void loop(){
  so.requestHandle();
}