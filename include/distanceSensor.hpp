#ifndef __DISTANCE_SENSOR__
#define __DISTANCE_SENSOR__

class observer;

#include "stdfx.hpp"
#include "timer.hpp"

class distanceSensor : public observer{
    public:
        distanceSensor(timer* myTimer,int interval = 100);
        ~distanceSensor();
        void update();
        int getDistance();
    private:
        SharpIR* sensor;
        int distance;
};


#endif