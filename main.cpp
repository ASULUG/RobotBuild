
#include <Arduino.h>
#include <Servo.h>
#include "Ping.h"
#include "NewPing"

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
void stationary();
void forward(int, int);
void forward(int);
void reverse(int, int);
void reverse(int);

Ping pingFront = Ping(11,12);     // ping object for front sensor
Ping pingRear = Ping(9,10);     // ping object for rear ping sensor
double distFront, distRear, lastDistFront, lastDistRear;

void setup()    {
    Serial.begin(9600);
    for (int i=0; i<arraySize; i++) {           // set up motor pins
        controllers[i].attach(motorPins[i]);
    }
    delay(500);     // give it a moment to settle

}

void loop() {

    pingFront.fire();
    delay(10);
    pingRear.fire();
    delay(10);
    distFront = pingFront.centimeters();
    distRear = pingRear.centimeters();

    if((distFront - lastDistFront >= 50) || (lastDistFront - distFront >= 50))    {// if big difference between last and current read
        distFront = pingFront.centimeters();                                    // read again
    }

    if ((distRear - lastDistRear >= 50) || (lastDistRear - distRear >= 50)) {
        distRear = pingRear.centimeters();
    }

    Serial.print("Front: ");
    Serial.println(distFront);
    Serial.print("Rear: ");
    Serial.println(distRear);

    if (distFront < 100 && distRear < 100) {   // if we are sandwiched in
        stationary();                           // STOP!
        Serial.print("STOP!");
        delay(3000);

    } else if (distRear - distFront <= 10) {           //if we have an object behind us
        forward(20);                            // and difference between front & back is 30cm,
        Serial.println("Forwards");             // go forwards

    } else if (distFront - distRear <=10) {           // if we have an object in front
        reverse(-20);                            // go backwards
        Serial.println("Reverse");
    }
    lastDistFront = distFront;      // save these for
    lastDistRear = distRear;        // next time around

}


void forward(int percent)   {
    int PWMvalue = percent * 5 + 1500;
    for (int i=0; i< arraySize; i++)  {
        controllers[i].writeMicroseconds(PWMvalue);
    }
}

void stationary()   {
    int PWMvalue = 1500;
    for (int i=0; i< arraySize; i++)  {
        controllers[i].writeMicroseconds(PWMvalue);
    }
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


void reverse(int percent)   {
    int PWMvalue = percent * 5 + 1500;
    for (int i=0; i< arraySize; i++) {
        controllers[i].writeMicroseconds(PWMvalue);
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
