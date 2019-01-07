#ifndef Fled_h
#define Fled_h

#include <Arduino.h>

class Fled{
  private:
    bool On = HIGH;
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;

  public:
    Fled(uint8_t _r, uint8_t g, uint8_t b, bool anode = false);
    void off();
    void Red();
    void Green();
    void Blue();
    void White();
    void Yellow();
};

#endif