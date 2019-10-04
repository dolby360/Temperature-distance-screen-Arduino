
#ifndef __SCREEN_CHARACTERS__
#define __SCREEN_CHARACTERS__

#include "stdfx.hpp"

class screenCharacter{
    protected:
        std::vector<std::vector<byte>> getMuse();
        byte* vectorToByteArray(std::vector<byte> vec);
    private:
};

#endif