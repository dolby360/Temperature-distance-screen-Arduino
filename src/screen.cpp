

#include "../include/screen.hpp"

screen::screen(timer* myTimer,unsigned int interval)
:observer(myTimer,interval){
    lcd = new LiquidCrystal_I2C(0x3f,20,4);
    lcd->init();  
    lcd->backlight();
    lcd->home();
    lcd->print("Hi");

    this->lastTempValue = 0;
    this->lastHumidity = 0;

    this->currentState = TEMP_HUMI;
    this->forceUpdate = true;
}

void screen::setTemperatureSensor(temp* tempSens){
    this->tempSens = tempSens;
}

void screen::setState(state newState){
    this->currentState = newState;
    this->forceUpdate = true;
}

void screen::update(){
    switch(this->currentState){
        case DISTANCE:
        break;
        case TEMP_HUMI:
            updateTempAndHumidity();
            Serial.println("TEMP_HUMI");
        break;
        default:
        break;
    }
    forceUpdate = false;
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

