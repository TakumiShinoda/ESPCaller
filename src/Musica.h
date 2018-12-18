#ifndef Musica_h
#define Musica_h

#include <Arduino.h>

#define C4 262	 	
#define D4 294 	 	
#define E4 330	
#define F4 349	 	
#define G4 392	 	
#define A4 440
#define B4 494

#define C5 523
#define D5 587
#define E5 659 	
#define F5 698	
#define G5 784
#define A5 880
#define B5 987

#define C6 1047
#define D6 1175
#define E6 1319
#define F6 1397
#define F6S 1480
#define G6 1568
#define G6S 1661
#define A6 1760
#define B6 1976

#define DIV8 125
#define DIV4 250
#define DIV2 500
#define NUT 1000

class Musica{
  private:
    uint8_t Pin;
    std::vector<int> Melodies;
    std::vector<unsigned long> Rhythms;

  public:
    Musica(uint8_t pin);
    void addMelody(std::vector<int> melodies, std::vector<unsigned long> rhythms = std::vector<unsigned long>());
    void clear();
    void play();
};

#endif