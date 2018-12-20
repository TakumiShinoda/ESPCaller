#ifndef ServerObject_h
#define ServerObject_h

#include <Arduino.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <vector>

#include "ChainArray.h"
#include "Utils.h"
#include "Html.h"

#define RESPTYPE_HTML "text/html"
#define RESPTYPE_JSON "application/json"
#define RESPTYPE_CSV "text/csv"

class Utils;
class ServerObject{
  private:
    struct Response{
      String url;
      String response;
      void (*prevCallback)(ChainArray, String*);
    };
    std::vector<Response> Responses;
    Utils *utils = new Utils();
    void sendGetResponse(WiFiClient *client, String html, String status);

  public:
    ServerObject();
    void begin();
    void requestHandle();
    void setResponse(String url, Html *response);
};

// public:
//     void addServer(uint8_t port);
//     void addServer(std::vector<uint8_t> ports);
//     void openServer(uint8_t port);
//     void openServer(std::vector<uint8_t> ports);
//     void openAllServers();
//     void requestHandle(uint8_t port);
//     void requestHandle(std::vector<uint8_t> ports);
//     void setResponse(uint8_t port, String url, Html *response);
//     void setNotFound(String resp);

//   private:
//     void addServer_proc(uint8_t port);
//     void openServer_proc(uint8_t port);
//     void requestHandle_proc(uint8_t port);
//     void sendGetResponse(WiFiClient *client, String html, String status);
//     struct Response{
//       String url;
//       String response;
//       void (*prevCallback)(ChainArray, String*);
//     };
//     struct Server{
//       uint8_t port;
//       WiFiServer server;
//       std::vector<struct Response> Responses;
//       void setResponse(String url, Html *response){
//         struct Response resObj;
//         Html *test = response;

//         resObj.url = url;
//         resObj.response = response->getHtml();
//         resObj.prevCallback = response->htmlObj.prev;
//         Responses.push_back(resObj);
//       };
//       int16_t findPath(String path){
//         int16_t result = -1;

//         for(int i = 0; i < Responses.size(); i++){
//           if(Responses[i].url == path) result = i;
//         }
//         return result;
//       };
//       void updateResponse(String url, Html *response){
//         int16_t objIndex = findPath(url);

//         if(objIndex >= 0){
//           Responses[objIndex].url = url;
//           Responses[objIndex].response = response->getHtml();
//           Responses[objIndex].prevCallback = response->htmlObj.prev;
//         }
//       };
//     };
//     String notFoundResp = "404";
//     std::vector<struct Server> Servers;
//     Utils *utils = new Utils();

#endif