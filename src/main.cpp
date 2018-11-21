#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "local_property.h"

#define TRY_CONNECT_AP 10

ESP8266WebServer server(80);
IPAddress ip(192, 168, 3, 1);
IPAddress subnet(255, 255, 255, 0);

void handle(){
  server.send(200, "text/html", "hoge");
}

void calling(){
  server.send(200, "text/html", "success");
  tone(5, 262, 200);
  delay(1000);
}

void setup() {
  uint8_t cnt = 0;

  Serial.begin(9600);

  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(STASSID, STAPASS);

  WiFi.softAPdisconnect(true);
  WiFi.softAPConfig(ip, ip, subnet);
  WiFi.softAP(APSSID, APPASS);
  WiFi.enableAP(true);

  while (WiFi.status() != WL_CONNECTED && cnt < TRY_CONNECT_AP){
    delay(500);
    Serial.print(".");
    cnt += 1;
  }
  if(WiFi.status() != WL_CONNECTED){
    Serial.println("failed");
    return;
  }

  Serial.println("\nWiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.print("AP SSID: ");
  Serial.println(WiFi.softAPSSID());
  Serial.print("AP IP Address: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handle);
  server.on("/call", calling);
  server.begin();
}

void loop(){
  server.handleClient();
}