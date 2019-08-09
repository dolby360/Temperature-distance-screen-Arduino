
#include "../include/timer.hpp"

observer::observer(timer* myTimer,unsigned int interval){
    this->myTimer = myTimer;
    this->myTimer->attach(this);
    this->interval = interval;
    this->clearTimes();
}

boolean observer::needToBeNotified(){
    if( (currentTime - startTime) > this->interval){
        this->clearTimes();
        return true;
    }
    return false;
}

void observer::clearTimes(){
    this->startTime = millis();
    this->currentTime = this->startTime;
}

void observer::setTime(unsigned long currentTime){
    this->currentTime = currentTime;
}

void timer::attach(observer* obs){
    obsList.push_back(obs);
}

void timer::updateTimer(){
    this->time = millis();
    notify(this->time);
} 

timer::timer(){
    this->time = 0;
}

void debugTimer(observer* o){
    static int debug = 0;
    if(o->childName() == "screen"){
        Serial.println(debug);
        debug = (debug + 1) % 10;
    }
}

void timer::notify(unsigned long currentTime){
    unsigned int i = 0;
    for(i = 0 ; i < obsList.size() ;i++){
        obsList[i]->setTime(currentTime);
        if( obsList[i]->needToBeNotified() ){
            //debugTimer(obsList[i]);
            obsList[i]->update();
        }
    }
}