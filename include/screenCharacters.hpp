
#ifndef __SCREEN_CHARACTERS__
#define __SCREEN_CHARACTERS__

#include "stdfx.hpp"

class screenCharacter{
    protected:
        //TODO:: everything should be draw here...
        //I did a mistake with the design
        /**************Draw here**************/
        void drawDuck(int row,int col);
        void drawNote(int row,int col);
        void drawBell(int row,int col);
        void drawClock(int row,int col);
        void drawHeart(int row,int col);
        void drawCheck(int row,int col);
        void drawCross(int row,int col);
        /*************************************/
        std::vector<std::vector<byte>> thumbDown();
        std::vector<std::vector<byte>> getSmile();
        std::vector<std::vector<byte>> getWalkingMan();
        byte* vectorToByteArray(std::vector<byte> vec);

        LiquidCrystal_I2C* lcd;
        int cellCounter;
    private:
        uint8_t duck[8]  = {0x0,0xc,0x1d,0xf,0xf,0x6,0x0};
        uint8_t note[8]  = {0x2,0x3,0x2,0xe,0x1e,0xc,0x0};
        uint8_t bell[8]  = {0x4,0xe,0xe,0xe,0x1f,0x0,0x4};
        uint8_t clock[8] = {0x0,0xe,0x15,0x17,0x11,0xe,0x0};
        uint8_t heart[8] = {0x0,0xa,0x1f,0x1f,0xe,0x4,0x0};
        uint8_t check[8] = {0x0,0x1,0x3,0x16,0x1c,0x8,0x0};
        uint8_t cross[8] = {0x0,0x1b,0xe,0x4,0xe,0x1b,0x0};
};

#endif