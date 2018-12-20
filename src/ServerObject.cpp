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
  delay(500);
  WiFiClient client = server.available();

  if(client.connected()){
    Serial.println("New Client");

    while(client.available()){
      String line = client.readStringUntil('\r');

      client.flush();
      if(line.indexOf("GET") >= 0){
        ChainArray analyzed = utils->analyzeGetRequest(line);
        String path = analyzed.get("path");

        Serial.print("From: ");
        Serial.println(client.remoteIP());
        Serial.print("Request: ");
        Serial.println(line);
        Serial.print("Path: ");
        Serial.println(path);

        for(int i = 0; i < Responses.size(); i++){
          if(Responses[i].url == path){
            String response = Responses[i].response;

            Responses[i].prevCallback(analyzed, &response);
            sendGetResponse(&client, response, "200");

            break;
          }else if(i == Responses.size() - 1){
            sendGetResponse(&client, "404", "404");
            break;
          }
        }
        client.disableKeepAlive();
        client.stopAll();
        break;
      }
    }
  }
}

void ServerObject::sendGetResponse(WiFiClient *client, String html, String status){
  if(client->available() && client->connected()){
    String contentLength = String(html.length());
    String statusResp = "HTTP/1.0 " + status + " OK";
    String contentLengthResp = "Content-Length: " + contentLength;
    String connectionResp = "Connection: close";
    String contentTypeResp = "Content-Type: text/html";
    String newLine = "\r\n";

    client->print(statusResp + newLine + contentLengthResp + newLine + connectionResp + newLine +contentTypeResp + newLine + newLine + html); 
  }else{
    Serial.println("Send failed");
  }
}