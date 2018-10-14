/*
taken from https://github.com/FRC4014/SRTester/blob/master/SRTester.ino
*/
/*
This code runs one wheel from -100 to +100 PWM
*/
 
/* This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>. */

#include <Servo.h>

//User configuration:
int percent = 20;  //between -100 and 100, indicates how fast the motor 
      //will be moving when the arduino boots
int pins[] = {5,6,7,8};//, 6}; //the signal output pins (as many as you'd like)


const int arraySize = sizeof(pins)/sizeof(int);
Servo controllers[arraySize];

void setup() {
  Serial.begin(9600);
  //Serial.println("you called, master?\n");
  for (int i=0; i<arraySize; i++)
    controllers[i].attach(pins[i]); //associate the object to a pin
  delay(1000);
  
}


void loop() {
  /*int PWMvalue = percent * 5 + 1500; //scale up to 1000-2000

  for (int i=0; i<arraySize; i++)
    controllers[i].writeMicroseconds(PWMvalue);
*/
  forward(20, 2000);
  reverse(20, 2000);
  strafeLeft(20,2000);
  strafeRight(20,2000);
  turnLeft(20,2000);
  turnRight(20,2000);
  stationary(2000);
}

void stationary(int time)  {
 for (int i=0; i<arraySize; i++)  {
   controllers[i].writeMicroseconds(0);
 } 
 delay(time);
}

void forward(int percent, int time)  {
   int PWMvalue = percent * 5 + 1500;
   for (int i=0; i< arraySize; i++)  {
     controllers[i].writeMicroseconds(PWMvalue);
   } 
   delay(time);
}

void reverse(int percent, int time)  {
   percent = percent * -1;
   int PWMvalue = percent * 5 + 1500;
   for (int i=0; i<arraySize; i++)  {
     controllers[i].writeMicroseconds(PWMvalue);
   }
   delay(time);
}

void strafeLeft(int percent, int time)  {
  
  controllers[0].writeMicroseconds(percent * -5 + 1500);
  controllers[1].writeMicroseconds(percent * 5 + 1500);
  controllers[2].writeMicroseconds(percent * 5 + 1500);
  controllers[3].writeMicroseconds(percent * -5 + 1500);
  delay(time);
}

void strafeRight(int percent, int time)  {
  controllers[0].writeMicroseconds(percent * 5 + 1500);
  controllers[1].writeMicroseconds(percent * -5 + 1500);
  controllers[2].writeMicroseconds(percent * -5 + 1500);
  controllers[3].writeMicroseconds(percent * 5 + 1500);
  delay(time);
}

void turnLeft(int percent, int time)  {
  controllers[0].writeMicroseconds(percent * -5 + 1500);
  controllers[1].writeMicroseconds(percent * -5 + 1500);
  controllers[2].writeMicroseconds(percent * 5 + 1500);
  controllers[3].writeMicroseconds(percent * 5 + 1500);
  delay(time);
}

void turnRight(int percent, int time)  {
  controllers[0].writeMicroseconds(percent * 5 + 1500);
  controllers[1].writeMicroseconds(percent * 5 + 1500);
  controllers[2].writeMicroseconds(percent * -5 + 1500);
  controllers[3].writeMicroseconds(percent * -5 + 1500);
  delay(time);
}
