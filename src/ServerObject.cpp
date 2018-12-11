#include "ServerObject.h"

WiFiServer server(80);

ServerObject::ServerObject(){
  server.begin();
}

void ServerObject::begin(){
  server.begin();
}

void ServerObject::setResponse(String url, Html *response){
  Response res;

  res.url = url;
  res.response = response->getHtml();
  res.prevCallback = response->htmlObj.prev;
  Responses.push_back(res);
}

void ServerObject::requestHandle(){
  WiFiClient client = server.available();

  if(client.connected()){
    Serial.println("available");
    String line = client.readStringUntil('\r');
    ChainArray analyzed = utils->analyzeGetRequest(line);
    String path = analyzed.get("path");

    Serial.print("Request: ");
    Serial.println(line);
    Serial.print("Path: ");
    Serial.println(path);

    if(line.indexOf("GET") >= 0){
      for(int i = 0; i < Responses.size(); i++){
        if(Responses[i].url == path){
          String response = Responses[i].response;

          Responses[i].prevCallback(analyzed, &response);
          sendGetResponse(&client, response, "200");
        }else if(i == Responses.size() - 1){
          sendGetResponse(&client, "404", "404");
        }
      }
    }
  }
}

void ServerObject::sendGetResponse(WiFiClient *client, String html, String status){
  String contentLength = String(html.length());
  String statusResp = "HTTP/1.1 " + status + " OK";
  String contentLengthResp = "Content-Length: " + contentLength;
  String connectionResp = "Connection: close";
  String contentTypeResp = "Content-Type: text/html";
  String newLine = "\r\n";

  client->print(statusResp + newLine + contentLengthResp + newLine + connectionResp + newLine +contentTypeResp + newLine + newLine + html);
  client->stop();
}