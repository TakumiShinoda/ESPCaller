#include "./ESPIFFS.h"

bool ESPIFFS::begin(){
  if(!SPIFFS.begin()) return false;
  else SPIFFSIni = true;
}

String ESPIFFS::readFile(String path){ 
  if(!SPIFFSIni) return "";

  File file = SPIFFS.open(utils->fixPath(path), "r");
  String result = "";
  
  if (!file){
    return "";
  }

  while (file.available()) {
    result += char(file.read());
  }

  return result;
}

bool ESPIFFS::writeFile(String path, String value){
  if(!SPIFFSIni) return false;

  File file = SPIFFS.open(utils->fixPath(path), "r");

  if(!file){
    file = SPIFFS.open(path, "a");
    if(!file) return false;
  }
  if(file.print(value)) return true;
  else return false;
}

void ESPIFFS::removeFile(String path){
  if(!SPIFFSIni) return;

  SPIFFS.remove(path);
}