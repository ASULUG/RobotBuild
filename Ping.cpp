
#include "Arduino.h"
#include "Ping.h"

Ping::Ping(uint8_t trigPin, uint8_t echoPin) {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    _trigPin = trigPin;
    _echoPin = echoPin;
    _cm = 0;
    _duration = -1;
}

Ping::Ping(uint8_t trigPin, uint8_t echoPin, double cm) {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    _trigPin = trigPin;
    _echoPin = echoPin;
    _cm = cm;
    _duration = -1;
}

void Ping::fire()   {
    digitalWrite(_trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(_trigPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(_trigPin, LOW);
    _duration = pulseIn(_echoPin, HIGH);
    //Serial.print("Duration: ");
    //Serial.println(_duration);
}

int Ping::microseconds()    {
    return _duration;
}

double Ping::centimeters()   {
    if (_duration != -1)    {
        return _duration / 29 /2 ;//+ _cm / 2;
    }
    else return -1;

}
