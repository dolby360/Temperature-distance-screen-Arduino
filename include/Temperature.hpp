
#ifndef __TEMPERATUTE__
#define __TEMPERATUTE__

#include "stdfx.hpp"
#include "timer.hpp"

class temp : public observer{
    public: 
        temp(timer* myTimer,int interval = 3000);
        void update();
        float getHumidity();
        float getTemperature();
    private:
        DHT* dht;
        float humidity;
        float temperature;
}; 


#endif