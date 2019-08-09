#include "Arduino.h"
#include "../include/stdfx.hpp"

#include "../include/timer.hpp"
#include "../include/distanceSensor.hpp"
#include "../include/Temperature.hpp"
#include "../include/screen.hpp"

timer myTimer;
distanceSensor* ds;
temp* tempSens; 
screen* myScreen;

volatile unsigned long lastTimeInterrupted; 
volatile int counter1 = 0;
volatile int counter2 = 0;

void ICACHE_RAM_ATTR buttonPressed();

void setup()
{         
  Serial.begin(115200);
  
  ds        = new distanceSensor(&myTimer);
  tempSens  = new temp(&myTimer);
  myScreen  = new screen(&myTimer);

  myScreen->setTemperatureSensor(tempSens);
  myScreen->setDistanceSensor(ds);
  //ds->setScreen(myScreen);

  lastTimeInterrupted = millis();
  attachInterrupt(digitalPinToInterrupt(D5), buttonPressed, RISING);
}

void loop(){
  myTimer.updateTimer();
}


void buttonPressed(){
  unsigned long timeNow = millis();
  if(timeNow - lastTimeInterrupted < 1000){
    return;
  }
  myScreen->toggleState();
  lastTimeInterrupted = millis();
}
