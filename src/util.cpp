
#include "../include/util.hpp"

void showDuck(LiquidCrystal_I2C &lcd){
    uint8_t duck[8]  = {0x0,0xc,0x1d,0xf,0xf,0x6,0x0};
    lcd.createChar(4, duck);
}