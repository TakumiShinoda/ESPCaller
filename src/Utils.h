#ifndef Utils_h
#define Utils_h

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <vector>
#include "ChainArray.h"

class Utils{
  public:
    ChainArray analyzeGetRequest(String request);
    String split(String target, char sep, uint8_t index);
    ChainArray analyzeQuery(String str);
    std::vector<uint8_t> vector_find(std::vector<String> target, String str);
    String ints2utf8(std::vector<uint8_t> data);
    String fixPath(String path);
    String getMAC();
};

#endif
