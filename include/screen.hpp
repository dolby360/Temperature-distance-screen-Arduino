

#ifndef __SCREEN__
#define __SCREEN__

#include "stdfx.hpp"
#include "timer.hpp"
#include "Temperature.hpp"

class screen : public observer{
    
    public:
        enum state{
            TEMP_HUMI,
            DISTANCE,
        };
        screen(timer* myTimer,unsigned int interval = 500);
        void update();
        void setTemperatureSensor(temp* tempSens); 
        void setState(state newState);
    private:
        temp* tempSens;
        LiquidCrystal_I2C* lcd;

        void updateTempAndHumidity();

        float lastTempValue;
        float lastHumidity; 
        state currentState;

        bool forceUpdate;
};

#endif