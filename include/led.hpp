#ifndef __LED_HPP__
#define __LED_HPP__

#include "stdfx.hpp"
#include "timer.hpp"
#include "Temperature.hpp"

#define MAXIMUM_TOLERANCE_FOR_HEAT 28
#define MAXIMUM_TOLERANCE_FOR_COLD 23
class led : public observer{
    public:
        led(timer* myTimer,int interval = 1000):observer(myTimer,interval){

        }
        ~led();
        void update(){
            if( myTemp->getTemperature() >= MAXIMUM_TOLERANCE_FOR_HEAT || 
                myTemp->getTemperature() <= MAXIMUM_TOLERANCE_FOR_COLD ){
                digitalWrite(D7,HIGH);
            }else{
                digitalWrite(D7,LOW);
            }
        }
        void setTemp(temp* value){
            myTemp = value;
        }
        String childName(){
            return "led";
        }
    private:
        temp* myTemp;
};


#endif