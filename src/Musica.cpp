#include "Musica.h"

Musica::Musica(uint8_t pin){
  Pin = pin;
}

void Musica::addMelody(std::vector<int> melodies, std::vector<unsigned long> rhythms){
  std::copy(melodies.begin(), melodies.end(), std::back_inserter(Melodies));
  if(rhythms.size() != 0) std::copy(rhythms.begin(), rhythms.end(), std::back_inserter(Rhythms));
}

void Musica::clear(){
  Melodies.clear();
  Melodies.shrink_to_fit();
  Rhythms.clear();
  Rhythms.shrink_to_fit();
} 

void Musica::play(){
  if(Melodies.size() == Rhythms.size()){
    for(int i = 0; i < Melodies.size(); i++){
      tone(Pin, Melodies[i], Rhythms[i]);
      delay(Rhythms[i]);
    }
  }else{
    Serial.println("play failed");
  }
}