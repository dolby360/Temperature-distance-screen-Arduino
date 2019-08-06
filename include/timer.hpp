
#ifndef __TIMER__
#define __TIMER__

#include "stdfx.hpp"

class observer;

class timer{
    public:
        unsigned long time; 
        void attach(observer* obs);
        timer();
        void notify(unsigned long currentTime);
        unsigned long getTime();
        void updateTimer();
    private:
        std::vector<class observer* > obsList;
};

class observer{
    public:
        timer* myTimer;
        observer(timer* myTimer,unsigned int interval);
        virtual void update() = 0;
        boolean needToBeNotified();
        void clearTimes();
        void setTime(unsigned long currentTime);
    private:
        unsigned long startTime;
        unsigned long currentTime;
        unsigned long interval;
};

#endif