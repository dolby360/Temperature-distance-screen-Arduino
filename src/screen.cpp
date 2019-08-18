

#include "../include/screen.hpp"

screen::screen(timer* myTimer,unsigned int interval)
:observer(myTimer,interval){
    lcd = new LiquidCrystal_I2C(0x3f,20,4);
    lcd->init();  
    lcd->backlight();
    lcd->home();

    this->lastTempValue = 0;
    this->lastHumidity = 0;

    this->currentState = TEMP_HUMI;
    this->forceUpdate = true;
    this->sleeping = false;
    this->startTimeFromWakeUp = millis();
    this->timeToStayAwake = 10000;
}

void screen::setTemperatureSensor(temp* tempSens){
    this->tempSens = tempSens;
}

void screen::setDistanceSensor(distanceSensor* ds){
    this->ds = ds;
}

void screen::toggleState(){
    this->currentState = static_cast<state>( (static_cast<int>(this->currentState) + 1) % (DISTANCE + 1) );
    this->forceUpdate = true;
    //Serial.println( static_cast<int>(this->currentState) );
}

void screen::setState(state newState){
    this->currentState = newState;
    this->forceUpdate = true;
}

void screen::wakeUp(){
    
    if(false == this->sleeping){
        return;
    }
    this->sleeping = false;
    this->startTimeFromWakeUp = millis();
    lcd->backlight();
}

void screen::checkIfNeedToSleep(){
    unsigned long timeNow = millis();
    if(timeNow - this->startTimeFromWakeUp > this->timeToStayAwake){
        this->sleeping = true;
        lcd->noBacklight();
    }
}

void screen::update(){
    if(sleeping){
        return;
    }
    // Serial.println(static_cast<int>(this->currentState));
    switch(this->currentState){
        case DISTANCE:
            //Serial.println("Distance");
            updateDistance();
        break;
        case TEMP_HUMI:
            //Serial.println("Temp");
            updateTempAndHumidity();
        break;
        default:
        break;
    }
    forceUpdate = false;
    checkIfNeedToSleep();
}

void screen::updateDistance(){
    lcd->clear();
    lcd->setCursor(0,1);
    lcd->print("Distance:");
    lcd->setCursor(11,1);
    int dist = ds->getDistance();
    lcd->print( String(dist) );
}

void screen::updateTempAndHumidity(){
    float temp = this->tempSens->getTemperature();
    float humi = this->tempSens->getHumidity();

    if(
        (temp == lastTempValue && humi == lastHumidity) &&
        (false == forceUpdate)
        ){
        return;
    }
    lastTempValue = temp;
    lastHumidity = humi;

    lcd->clear();
    lcd->home();
    lcd->print("Humidity:");
    lcd->setCursor(0, 1);
    lcd->print(String(  (int)  humi)  );
    lcd->setCursor(0, 2);
    lcd->print("Temperature:");
    lcd->setCursor(0, 3);
    lcd->print(String(  (int)  temp)  );
}

