

#include "../include/screenCharacters.hpp"


void screenCharacter::drawCross(int row,int col){
    lcd->createChar(this->cellCounter, cross);
    lcd->setCursor(col,row);
    lcd->write(this->cellCounter++);
}

void screenCharacter::drawCheck(int row,int col){
    lcd->createChar(this->cellCounter, check);
    lcd->setCursor(col,row);
    lcd->write(this->cellCounter++);
}

void screenCharacter::drawHeart(int row,int col){
    lcd->createChar(this->cellCounter, heart);
    lcd->setCursor(col,row);
    lcd->write(this->cellCounter++);
}

void screenCharacter::drawClock(int row,int col){
    lcd->createChar(this->cellCounter, clock);
    lcd->setCursor(col,row);
    lcd->write(this->cellCounter++);
}

void screenCharacter::drawBell(int row,int col){
    lcd->createChar(this->cellCounter, bell);
    lcd->setCursor(col,row);
    lcd->write(this->cellCounter++);
}

void screenCharacter::drawNote(int row,int col){
    lcd->createChar(this->cellCounter, note);
    lcd->setCursor(col,row);
    lcd->write(this->cellCounter++);
}

void screenCharacter::drawDuck(int row,int col){
    lcd->createChar(this->cellCounter, duck);
    lcd->setCursor(col,row);
    lcd->write(this->cellCounter++);
}


std::vector<std::vector<byte>> screenCharacter::thumbDown(){
    std::vector<byte> thumb1 = {B00011,B00000,B00000,B00000,B00000,B00000,B00000,B00000};
    std::vector<byte> thumb2 = {B00001,B00010,B00011,B00100,B00011,B00100,B00011,B00100};
    std::vector<byte> thumb3 = {B00000,B11110,B01000,B10001,B10010,B10010,B01100,B00000};
    std::vector<byte> thumb4 = {B11110,B00001,B00000,B00000,B00000,B00000,B00000,B00000};
    std::vector<byte> thumb5 = {B00110,B01000,B10000,B00000,B00000,B00000,B00000,B00000};
    std::vector<byte> thumb6 = {B00000,B10000,B01110,B00010,B00010,B00010,B00010,B00010};
    

    std::vector<std::vector<byte>> vec;
    vec.push_back(thumb1);
    vec.push_back(thumb2);
    vec.push_back(thumb3);
    vec.push_back(thumb4);
    vec.push_back(thumb5);
    vec.push_back(thumb6);

    
    return vec;
}



std::vector<std::vector<byte>> screenCharacter::getSmile(){
    std::vector<byte> AHB1 = {B00000,B00000,B01110,B01010,B01110,B01010,B01110,B00000};
    std::vector<byte> AHB2 = {B00000,B00000,B00000,B00000,B00000,B00000,B00100,B00100};
    std::vector<byte> AHB3 = {B00000,B00000,B01110,B01010,B01110,B01010,B01110,B00000};
    std::vector<byte> AHB4 = {B00000,B00000,B00100,B00010,B00001,B00000,B00000,B00000};
    std::vector<byte> AHB5 = {B00100,B01110,B00000,B00000,B00000,B11111,B00000,B00000};
    std::vector<byte> AHB6 = {B00000,B00000,B00100,B01000,B10000,B00000,B00000,B00000};

    std::vector<std::vector<byte>> vec;
    vec.push_back(AHB1);
    vec.push_back(AHB2);
    vec.push_back(AHB3);
    vec.push_back(AHB4);
    vec.push_back(AHB5);
    vec.push_back(AHB6);
    
    return vec;
}

std::vector<std::vector<byte>> screenCharacter::getWalkingMan(){
    std::vector<byte> stepA1 = {B00011,B00111,B00111,B00111,B00111,B00001,B00011,B00111};
    std::vector<byte> stepA2 = {B00001,B00001,B00011,B00011,B00011,B00001,B00000,B00001};
    std::vector<byte> stepA3 = {B11111,B11111,B11111,B11111,B11111,B11011,B10001,B10001};
    std::vector<byte> stepA4 = {B11111,B11111,B11101,B11101,B11111,B11111,B11111,B11111};
    std::vector<byte> stepA5 = {B11000,B11100,B11100,B11100,B11100,B10000,B11000,B11100};
    std::vector<byte> stepA6 = {B00000,B10000,B11000,B00000,B11000,B11100,B11000,B10000};

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
