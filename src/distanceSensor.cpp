
#include "../include/distanceSensor.hpp"

distanceSensor::distanceSensor(timer* myTimer,int interval)
:observer(myTimer,interval){
    sensorValueToCm = {  
        {108,20},   {111,19},   {114,18},
        {120,17},   {126,16},   {149,15},
        {157,14},   {169,13},   {182,12},
        {188,11},   {207,10},   {226,9},
        {245,8},    {271,7},    {315,6},
        {366,5},    {438,4},    {541,3},
        {716,2}
    };
    buffSize = 10;
    buff = new unsigned int[buffSize];

    int sum = 0;
    for(int i = 0; i < buffSize; i++){
        buff[i] = analogRead(A0);
        sum += buff[i];
    }
    avgDistance = sum / buffSize;
    buffIndex = 0;
}

void distanceSensor::wakeUpTheScreen(){
    myScreen->wakeUp();
}

void distanceSensor::setScreen(screen* myScreen){
    this->myScreen = myScreen;
}

int distanceSensor::calcAvgAs_cm(){
    int sum = 0;
    for(int i = 0; i < buffSize; i++){
        sum += buff[i];
    }
    int res = sum / buffSize;
    auto it = sensorValueToCm.begin();
    if(res < it->first){
        return it->second; //minimum value
    }
    for (it = sensorValueToCm.begin(); it != sensorValueToCm.end(); it++){
        auto temp = it;
        temp++;
		if(temp == sensorValueToCm.end()){
            return temp->second; //max value
        }
        //Check if in range;
        if(res >= it->first && res <= temp->first){
            //Check what is closest.
            int floor   = res - it->first;
            int top     = it->second - res; 
            return floor >= top ? it->second : temp->second; 
        }
	}
    //in some very weird case that may happen.
    return 0;
}

void distanceSensor::update(){
    buff[buffIndex] = analogRead(A0);
    buffIndex = (buffIndex + 1) % (buffSize);
    
    if(buffIndex == buffSize - 1){
        avgDistance = calcAvgAs_cm();
        //Serial.println(avgDistance);
    }
    if(avgDistance < 10){
        wakeUpTheScreen();
    }
}

distanceSensor::~distanceSensor(){

}

int distanceSensor::getDistance(){
    return this->avgDistance;
}