
#include "../include/Temperature.hpp"

temp::temp(timer* myTimer,int interval):observer(myTimer,interval){
    dht = new DHT();
    dht->setup(0,DHT::DHT_MODEL_t::DHT11);
}

void temp::update(){
    this->humidity = dht->getHumidity();
    this->temperature = dht->getTemperature();
}

float temp::getHumidity(){
    return this->humidity;
}

float temp::getTemperature(){
    return this->temperature;
}