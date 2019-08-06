
#include "../include/messages.hpp"

template <class T>
cout<T>::cout(timer* myTimer,unsigned int interval)
:observer(myTimer,interval){

}

template <class T>
void cout<T>::update(){
    for(int i = 0; i < allMessages.size(); i++){
        Serial.write("");
    }
}

