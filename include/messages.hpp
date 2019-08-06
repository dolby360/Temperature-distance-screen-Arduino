
#ifndef __MESSAGES__
#define __MESSAGES__


#include "stdfx.hpp"
#include "timer.hpp"

template <class T>
class cout: public observer{
        std::vector<String> allMessages;
    public:
        cout(timer* myTimer,unsigned int interval = 100);
        void update();
        // friend std::ostream &operator << (std::ostream &output){
        //     String newMsg = 
        //     String( millis() ) +  ": " + String(output);
        //     allMessages.push_back(newMsg);
        // }
    private:

};

#endif