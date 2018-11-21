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
  Serial.println("waiting");

  if(client.connected()){
    Serial.println("available");
    String line = client.readStringUntil('\r');
    Serial.println(line);

    if(line.indexOf("GET") >= 0){
      Serial.println("hoge");
      client.print("hogehoge");
    }
  }

  // WiFiClient client = server.available();
  // String rstr;
  // if (client.connected()) {
  //   Serial.println("Connected to client");
 
  //   //コマンド文字列受信（文字列が来なければタイムアウトする）
  //   rstr = client.readStringUntil('\r');
  //   Serial.print("[");
  //   Serial.print(rstr);
  //   Serial.println("]");
 
  //   //応答送信
  //   client.print("OK\r");
 
  //   //接続をクローズ
  //   client.stop();
  //   Serial.println("Closed");
  // }
}