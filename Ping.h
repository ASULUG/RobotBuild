
#ifndef Ping_h
#define Ping_h

#include <Arduino.h>

class Ping {
public:
    Ping(uint8_t trigPin, uint8_t echoPin); // constructor
    Ping(uint8_t trigPin, uint8_t echoPin, double cm); // constructor
    void fire();
    int microseconds();
    double centimeters();

private:
    int _trigPin;
    int _echoPin;
    double _cm;
    long _duration;
};

#endif
