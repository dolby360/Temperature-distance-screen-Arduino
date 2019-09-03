#ifndef __SCREEN__
#define __SCREEN__

#include "stdfx.hpp"
#include "timer.hpp"
#include "Temperature.hpp"
#include "distanceSensor.hpp"
#include "Wifi.hpp"

class distanceSensor;

class screen : public observer{
    
    public:
        enum state{
            TEMP_HUMI,
            DISTANCE,
            WIFI,
            LAST_STATE,
        };
        screen(timer* myTimer,unsigned int interval = 100);
        void update();
        void setTemperatureSensor(temp* tempSens); 
        void setDistanceSensor(distanceSensor* ds);
        void setWifi(wifiServer* wifi);
        void toggleState();
        void wakeUp();
        bool isSleeping(){
            return sleeping;
        }
        void wifiUpdateMethod();
        String childName(){
            return "screen";
        }
    private:
        wifiServer* wifi;
        temp* tempSens;
        distanceSensor* ds;
        LiquidCrystal_I2C* lcd;

        void setState(state newState);
        void updateTempAndHumidity();
        void updateDistance();
        void checkIfNeedToSleep();
        float lastTempValue;
        float lastHumidity; 
        String lastIPValue;
        state currentState;
        unsigned long startTimeFromWakeUp;
        bool forceUpdate;
        bool sleeping;
        bool firstTimeInThisState;
        unsigned int timeToStayAwake;
};

#endif