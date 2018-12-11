#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "ServerObject.h"
#include "ChainArray.h"
#include "ESPIFFS.h"

#include "local_property.h"

#define TRY_CONNECT_AP 10

IPAddress ip(192, 168, 3, 1);
IPAddress subnet(255, 255, 255, 0);
ServerObject so;
ESPIFFS espiffs;

void testCallback(ChainArray params, String *response){
  Serial.println("hoge");
}

void setup(){
  Serial.begin(9600);
  uint8_t cnt = 0;
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(APSSID, APPASS);
  WiFi.softAPConfig(ip, ip, subnet);
  WiFi.begin(STASSID, STAPASS);

  if(!espiffs.begin()){
    Serial.println("ESPIFFS failed"); 
    return;
  }

  Serial.println(espiffs.readFile("test.txt"));

  return;

  while (WiFi.status() != WL_CONNECTED && cnt < TRY_CONNECT_AP){
    delay(500);
    Serial.print(".");
    cnt += 1;
  }

  if(WiFi.status() != WL_CONNECTED){
    Serial.println("failed");
    return;
  }
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  Html test("testetse", testCallback);

  so.setResponse("/test", &test);
  so.begin();
}

void loop(){
  so.requestHandle();
}