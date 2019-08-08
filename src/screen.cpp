

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
}

void screen::setState(state newState){
    this->currentState = newState;
    this->forceUpdate = true;
}

void screen::update(){
    // Serial.println(static_cast<int>(this->currentState));
    switch(this->currentState){
        case DISTANCE:
            updateDistance();
        break;
        case TEMP_HUMI:
            updateTempAndHumidity();
        break;
        default:
        break;
    }
    forceUpdate = false;
}

void screen::updateDistance(){
    lcd->clear();
    lcd->home();
    lcd->print("Distance:");
    lcd->setCursor(11,0);
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

