
#include <Arduino.h>
#include <Servo.h>
#include "Ping.h"

//User configuration:
int percent = 20;  //between -100 and 100, indicates how fast the motor
//will be moving when the Arduino boots
int motorPins[] = {5,6,7,8};//, 6}; //the signal output pins (as many as you'd like)

//long duration, cm;   // used for ping sensor

const int arraySize = sizeof(motorPins)/sizeof(int);
Servo controllers[arraySize];

unsigned long timeNow = 0;
unsigned long timeLast = 0;
String driveState = "stationary";

/**********************************
 * Function prototypes
 *********************************/
long ping(void);
long microsecondsToCentimeters(long);
void stationary(int);
void forward(int, int);
void reverse(int, int);

Ping pingFront = Ping(1,2);     // ping object for front sensor


void setup()    {
    Serial.begin(9600);
    for (int i=0; i<arraySize; i++) {           // set up motor pins
        controllers[i].attach(motorPins[i]);
    }
    delay(500);     // give it a moment to settle

}

void loop() {
    pingFront.fire();
    int dist = pingFront.centimeters();
    Serial.println(dist, DEC);
    if(dist < 100)   {
        stationary(2000);

    }
    else forward(20,1000);

    delay(500);


    //pingFront.fire();
    //Serial.println(pingFront.centimeters());
    /*
    static int state = 1;
    static unsigned long timeLast = 0;
    static unsigned long timeNow = 0;

    switch(state)   {
        case 1:
            pingFront.fire();
            if (pingFront.centimeters() <= 100) {
                stationary(2000);
            }
            else forward(20, 2000);
            break;

        case 2:

            break;

    }
*/
}


void stationary(int time)   {
    for (int i = 0; i < arraySize; i++) {
        controllers[i].writeMicroseconds(0);
    }
    delay(time);
}

void forward(int percent, int time) {
    int PWMvalue = percent * 5 + 1500;
    timeNow = millis();
    for (int i=0; i< arraySize; i++)  {
        controllers[i].writeMicroseconds(PWMvalue);
    }
    driveState = "forward";
    if (timeNow - timeLast >= time) {
        stationary(2000);
        driveState = "stationary";
        timeLast = timeNow;
    }
}

void reverse(int percent, int time) {
    timeNow = millis();
    driveState = "reverse";
    if (timeNow - timeLast >= time) {
        stationary(2000);
        driveState = "stationary";
        timeLast = timeNow;
    }

}







/*
#include <Arduino.h>
int ledPin = 13;

void setup()    {
    pinMode(ledPin, OUTPUT);
}

void loop() {
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
}
 */