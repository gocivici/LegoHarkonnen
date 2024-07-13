/*
 * LEGO Harkonnen Display 
 * By Görkem Bozkurt
 * https://gorkem.cc
 * Requires AccelStepper.h and mp3tf16p.h libraries
 */


#include "mp3tf16p.h"
#include <AccelStepper.h>
#include <Stepper.h>

boolean playedOnce = false;
const int buttonLight = 5; //front button light
const int boxLight = 2; //LED strip inside box
const int buttonPin = 6; //front button pin
int stepperLoc = 0; //initial location of stepper motor

#define HALFSTEP 8

#define motorPin1  9     // IN1 on ULN2003 ==> Blue on 28BYJ-48
#define motorPin2  10     // IN2 on ULN2003 ==> Pink on 28BYJ-48
#define motorPin3  11    // IN3 on ULN2003 ==> Yellow on 28BYJ-48
#define motorPin4  12    // IN4 on ULN2003 ==> Orange on 28BYJ-48

MP3Player mp3(3,4); //initialize mp3 player module

AccelStepper mystepper(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  pinMode(buttonLight, OUTPUT);
  pinMode(boxLight, OUTPUT);
  mystepper.setMaxSpeed(800);
  mystepper.setAcceleration(120);
  mp3.initialize();
  digitalWrite(buttonLight,HIGH);
}

void loop() {

if(digitalRead(buttonPin)){
    mp3.playTrackNumber(1,20,false);
    digitalWrite(buttonLight,LOW);
    playedOnce = true;
    stepperLoc = 8000;
    
  }  

  mystepper.moveTo(stepperLoc);

  if(mp3.playCompleted()){  
    stepperLoc = 0;
    digitalWrite(buttonLight,HIGH);
    }

if(mystepper.distanceToGo()!=0){ 
  mystepper.enableOutputs();
    mystepper.run();
    }else{
      mystepper.disableOutputs();
      }
}
