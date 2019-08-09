#ifndef __DISTANCE_SENSOR__
#define __DISTANCE_SENSOR__

#include "stdfx.hpp"
#include "timer.hpp"
#include "screen.hpp"
#include <map>

class screen;

class distanceSensor : public observer{
    public:
        distanceSensor(timer* myTimer,int interval = 100);
        ~distanceSensor();
        void update();
        int getDistance();
        void setScreen(screen* myScreen);
        String childName(){
            return "distanceSensor";
        }
    private:
        std::map<int,int> sensorValueToCm;
        screen* myScreen;   
        void wakeUpTheScreen();
        int calcAvgAs_cm();
        unsigned int* buff;
        int avgDistance;
        int buffSize;
        int distance;
        int buffIndex;
};


#endif