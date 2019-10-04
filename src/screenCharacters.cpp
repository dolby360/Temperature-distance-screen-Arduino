

#include "../include/screenCharacters.hpp"

std::vector<std::vector<byte>> screenCharacter::getMuse(){
    std::vector<byte> stepA1 = {
        B00011,B00111,B00111,B00111,B00111,B00001,B00011,B00111};
    std::vector<byte> stepA2 = {
        B00001,B00001,B00011,B00011,B00011,B00001,B00000,B00001};
    std::vector<byte> stepA3 = {
        B11111,B11111,B11111,B11111,B11111,B11011,B10001,B10001};
    std::vector<byte> stepA4 = {
        B11111,B11111,B11101,B11101,B11111,B11111,B11111,B11111};
    std::vector<byte> stepA5 = {
        B11000,B11100,B11100,B11100,B11100,B10000,B11000,B11100};
    std::vector<byte> stepA6 = {
        B00000,B10000,B11000,B00000,B11000,B11100,B11000,B10000};

    std::vector<std::vector<byte>> vec;
    vec.push_back(stepA1);
    vec.push_back(stepA2);
    vec.push_back(stepA3);
    vec.push_back(stepA4);
    vec.push_back(stepA5);
    vec.push_back(stepA6);
    
    return vec;
}

byte* screenCharacter::vectorToByteArray(std::vector<byte> vec){
    byte* ret = new byte[vec.size()];
    unsigned int i = 0;
    for(i = 0; i < vec.size(); i++){
        ret[i] = vec[i];
    }
    return ret;
}
