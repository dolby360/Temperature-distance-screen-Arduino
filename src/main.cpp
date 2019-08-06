#include "Arduino.h"
#include "../include/stdfx.hpp"
#include "../include/util.hpp"
#include "../include/timer.hpp"
#include "../include/distanceSensor.hpp"
#include "../include/Temperature.hpp"
#include "../include/screen.hpp"

timer myTimer;
distanceSensor* ds;
temp* tempSens; 
screen* myScreen;

void setup()
{         
  Serial.begin(115200);
  pinMode(D8,INPUT);
  
  ds        = new distanceSensor(&myTimer);
  tempSens  = new temp(&myTimer);
  myScreen  = new screen(&myTimer);

  myScreen->setTemperatureSensor(tempSens);
}

void loop(){
  myTimer.updateTimer();
}


