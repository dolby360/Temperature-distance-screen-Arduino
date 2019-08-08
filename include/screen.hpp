

#ifndef __SCREEN__
#define __SCREEN__

#include "stdfx.hpp"
#include "timer.hpp"
#include "Temperature.hpp"
#include "distanceSensor.hpp"

class screen : public observer{
    
    public:
        enum state{
            TEMP_HUMI,
            DISTANCE,
        };
        screen(timer* myTimer,unsigned int interval = 500);
        void update();
        void setTemperatureSensor(temp* tempSens); 
        void setDistanceSensor(distanceSensor* ds);
        void toggleState();
    private:
        temp* tempSens;
        distanceSensor* ds;
        LiquidCrystal_I2C* lcd;

        void setState(state newState);
        void updateTempAndHumidity();
        void updateDistance();
        float lastTempValue;
        float lastHumidity; 
        state currentState;

        bool forceUpdate;
};

#endif