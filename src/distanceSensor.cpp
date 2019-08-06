

#include "../include/distanceSensor.hpp"



distanceSensor::distanceSensor(timer* myTimer,int interval)
:observer(myTimer,interval){
    sensor = new SharpIR( SharpIR::GP2Y0A41SK0F, A0 );
}

void distanceSensor::update(){
    this->distance = sensor->getDistance();
}

distanceSensor::~distanceSensor(){
    delete sensor;
}

int distanceSensor::getDistance(){
    return this->distance;
}