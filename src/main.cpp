#include "Arduino.h"
#include "../include/stdfx.hpp"

#include "../include/timer.hpp"
#include "../include/distanceSensor.hpp"
#include "../include/Temperature.hpp"
#include "../include/screen.hpp"
#include "../include/Wifi.hpp"

timer myTimer;
distanceSensor* ds;
temp* tempSens; 
screen* myScreen;
wifiServer* myWifi;

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
  myWifi    = wifiServer::getInstanceAndTryToSetTimer(&myTimer);
  myScreen->setTemperatureSensor(tempSens);
  myScreen->setDistanceSensor(ds);
  myScreen->setWifi(myWifi);
  ds->setScreen(myScreen);

  lastTimeInterrupted = millis();
  attachInterrupt(digitalPinToInterrupt(D5), buttonPressed, RISING);
}

void loop(){
  myTimer.updateTimer();
  // if(counter1 != counter2){
  //   Serial.println(counter1);
  //   counter2 = counter1;
  // }
}

void buttonPressed(){
  unsigned long timeNow = millis();
  if(timeNow - lastTimeInterrupted < 1000){
    return;
  }
  counter1 +=1;
  if(false == myScreen->isSleeping()){
    myScreen->toggleState();
  }
  myScreen->wakeUp();
  lastTimeInterrupted = millis();
}
