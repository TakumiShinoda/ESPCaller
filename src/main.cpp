#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

#include "ServerObject.h"
#include "ChainArray.h"
#include "ESPIFFS.h"
#include "Musica.h"
#include "Fled.h"
#include "Utils.h"

#include "local_property.h"

#define DEVICE_MODE_RECV 0
#define DEVICE_MODE_SEND 1
#define DEVICE_MODE DEVICE_MODE_RECV

#define TRY_CONNECT_AP 10
#define BUTA 13
#define BUTB 5
#define BUTC 14
#define BUTD 4

#define STATUS_LED_PIN 16
#define SOUND_PIN 5
#define LED_R_PIN 13
#define LED_B_PIN 12
#define LED_G_PIN 14

IPAddress ip(192, 168, 3, 1);
IPAddress subnet(255, 255, 255, 0);
ServerObject so;
ESPIFFS espiffs;
Musica famima(SOUND_PIN);
Fled recvNotifyLed(LED_R_PIN, LED_G_PIN, LED_B_PIN, true);
Utils utils;

void testCallback(ChainArray params, String *response){
  recvNotifyLed.White();
  delay(1000);
  famima.play();
  recvNotifyLed.off();
}

void fromESPIFFS(ChainArray params, String *response){
  *response = espiffs.readFile(*response);
}

String getRequest(String host) {
  HTTPClient http;

  http.begin(host);
  int httpCode = http.GET();

  String result = "";

  if (httpCode < 0) {
    result = http.errorToString(httpCode);
  } else if (http.getSize() < 0) {
    result =  "size is invalid";
  } else {
    result = http.getString();
  }

  http.end();
  return result;
}

void setup(){
  uint8_t cnt = 0;

  pinMode(STATUS_LED_PIN, OUTPUT);
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(APSSID, APPASS);
  WiFi.softAPConfig(ip, ip, subnet);
  WiFi.begin(STASSID, STAPASS);
  Serial.begin(9600);
  delay(500);

  famima.addMelody(
    {F6S, D6, A5, D6, E6, A6, A6, E6, F6S, E6, A5, D6},
    {DIV8, DIV8, DIV8, DIV8, DIV8, DIV4, DIV8, DIV8, DIV8, DIV8, DIV8, DIV8}
  );

  if(!espiffs.begin()){
    Serial.println("ESPIFFS failed"); 
    return;
  }

  while (WiFi.status() != WL_CONNECTED && cnt < TRY_CONNECT_AP){
    Serial.print(".");
    digitalWrite(STATUS_LED_PIN, LOW);
    cnt += 1;
    delay(500);
    digitalWrite(STATUS_LED_PIN, HIGH);
    delay(50);
  }

  if(WiFi.status() != WL_CONNECTED){
    Serial.println("failed");
    digitalWrite(STATUS_LED_PIN, LOW);
    return;
  }else{
    digitalWrite(STATUS_LED_PIN, HIGH);
  }

  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  if(DEVICE_MODE == DEVICE_MODE_RECV){
    Html test("testetse", testCallback);
    Html makeTone("/test.txt", fromESPIFFS);

    so.setResponse("/test", &test);
    so.setResponse("/maketone", &makeTone);
  }else if(DEVICE_MODE == DEVICE_MODE_SEND){
    pinMode(BUTA, INPUT);
    pinMode(BUTB, INPUT);
    pinMode(BUTC, INPUT);
    pinMode(BUTD, INPUT);
  }

  so.begin();
}

void loop(){
  so.requestHandle();

  if(DEVICE_MODE == DEVICE_MODE_SEND){
    if(!digitalRead(BUTA)){
      Serial.println(getRequest("http://" + RECV_IP + "/test"));
    }else if(!digitalRead(BUTB)){
      Serial.println("BUTB");
    }else if(!digitalRead(BUTC)){
      Serial.println("BUTC");
    }else if(!digitalRead(BUTD)){
      Serial.println("BUTD");
    }
  }
}