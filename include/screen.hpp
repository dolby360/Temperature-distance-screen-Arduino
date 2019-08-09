#ifndef __SCREEN__
#define __SCREEN__

#include "stdfx.hpp"
#include "timer.hpp"
#include "Temperature.hpp"
#include "distanceSensor.hpp"

class distanceSensor;

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
        void wakeUp();
        String childName(){
            return "screen";
        }
    private:
        temp* tempSens;
        distanceSensor* ds;
        LiquidCrystal_I2C* lcd;

        void setState(state newState);
        void updateTempAndHumidity();
        void updateDistance();
        void checkIfNeedToSleep();
        float lastTempValue;
        float lastHumidity; 
        state currentState;
        unsigned long startTimeFromWakeUp;
        bool forceUpdate;
        bool sleeping;
};

#endif