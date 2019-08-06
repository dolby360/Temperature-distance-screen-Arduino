
#ifndef __UTIL__
#define __UTIL__

#include "stdfx.hpp"


void showDuck(LiquidCrystal_I2C& lcd);


String to_string(float num);
String to_string(int num);
String to_string(double num);

typedef enum State{
    OFF = 0,
    ON  = 1
}State;

class Button{
    public:

        State buttonState();
    private:
        boolean debounceButton();
};

#endif