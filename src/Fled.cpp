#include "Fled.h"

Fled::Fled(uint8_t _r, uint8_t _g, uint8_t _b, bool anode){
  r = _r;
  g = _g;
  b = _b;

  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);
  if(anode) On = LOW;
  off();
}

void Fled::off(){
  digitalWrite(r, !On);
  digitalWrite(g, !On);
  digitalWrite(b, !On);
}

void Fled::Red(){
  off();
  digitalWrite(r, On);
}

void Fled::Green(){
  off();
  digitalWrite(g, On);
}

void Fled::Blue(){
  off();
  digitalWrite(b, On);
}

void Fled::White(){
  off();
  analogWrite(r, 150);
  digitalWrite(g, On);
  digitalWrite(b, On);
}

void Fled::Yellow(){
  off();
  analogWrite(r, 150);
  digitalWrite(g, On);
}