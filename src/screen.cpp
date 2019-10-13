

#include "../include/screen.hpp"

screen::screen(timer* myTimer,unsigned int interval)
:observer(myTimer,interval){
    lcd = new LiquidCrystal_I2C(0x3f,20,4);
    lcd->init();  
    lcd->backlight();
    lcd->home();

    this->lastTempValue = 0;
    this->lastHumidity = 0;

    this->currentState = TEMP_HUMI;
    this->forceUpdate = true;
    this->sleeping = false;
    this->startTimeFromWakeUp = millis();
    this->timeToStayAwake = 10000;
}

void screen::setTemperatureSensor(temp* tempSens){
    this->tempSens = tempSens;
}

void screen::setDistanceSensor(distanceSensor* ds){
    this->ds = ds;
}

void screen::setWifi(wifiServer* wifi){
    this->wifi = wifi;
}

void screen::toggleState(){
    this->currentState = static_cast<state>( (static_cast<int>(this->currentState) + 1) % (LAST_STATE + 1) );
    this->forceUpdate = true;
    this->firstTimeInThisState = true;
    // Serial.println( static_cast<int>(this->currentState) );
}

void screen::setState(state newState){
    this->currentState = newState;
    this->forceUpdate = true;
}

void screen::wakeUp(){
    
    if(false == this->sleeping){
        this->startTimeFromWakeUp = millis();
        return;
    }
    this->sleeping = false;
    this->startTimeFromWakeUp = millis();
    lcd->backlight();
}

void screen::checkIfNeedToSleep(){
    //in case there is some connection 
    //do not go to sleep.
    if(wifi->getIPAddress() != ""){
        return;
    }
    unsigned long timeNow = millis();
    if(timeNow - this->startTimeFromWakeUp > this->timeToStayAwake){
        this->sleeping = true;
        lcd->noBacklight();
    }
}


void screen::update(){
    if(sleeping){
        return;
    }
    // Serial.println(static_cast<int>(this->currentState));
    switch(this->currentState){
        case DISTANCE:
            //Serial.println("Distance");
            updateDistance();
        break;
        case TEMP_HUMI:
            //Serial.println("Temp");
            updateTempAndHumidity();
        break;
        case WIFI:
            wifiUpdateMethod();
        break;
        case LAST_STATE:
            toggleState();
        break;
        default:
        break;
    }
    this->firstTimeInThisState = false;
    forceUpdate = false;
    checkIfNeedToSleep();
}

void screen::updateDistance(){
    lcd->clear();
    lcd->setCursor(0,1);
    lcd->print("Distance:");
    lcd->setCursor(11,1);
    int dist = ds->getDistance();
    lcd->print( String(dist) );
}

void screen::updateTempAndHumidity(){
    float temp = this->tempSens->getTemperature();
    float humi = this->tempSens->getHumidity();

    if(
        (temp == lastTempValue && humi == lastHumidity) &&
        (false == forceUpdate)
        ){
        return;
    }
    lastTempValue = temp;
    lastHumidity = humi;

    lcd->clear();
    lcd->home();
    lcd->print("Humidity:");
    lcd->setCursor(0, 1);
    lcd->print(String(  (int)  humi)  );
    lcd->setCursor(0, 2);
    lcd->print("Temperature:");
    lcd->setCursor(0, 3);
    lcd->print(String(  (int)  temp)  );
}

void screen::write6blockCharacterStandartWay(){
    int row = wifiServer::getInstance()->getRow();
    int col = wifiServer::getInstance()->getCol();
    int a = col;
    int b = a + 1;
    int c = a + 2;
    lcd->setCursor(a,row + 0);
    lcd->write(0);
    lcd->setCursor(b,row + 0);
    lcd->write(1);
    lcd->setCursor(c,row + 0);
    lcd->write(2);
    lcd->setCursor(a,row + 1);
    lcd->write(3);
    lcd->setCursor(b,row + 1);
    lcd->write(4);
    lcd->setCursor(c,row + 1);
    lcd->write(5);
}

void screen::write6blockCharacter(){
    int row = wifiServer::getInstance()->getRow();
    int col = wifiServer::getInstance()->getCol();
    int a = col;
    int b = a + 1;
    int c = a + 2;
    lcd->setCursor(a,row + 1);
    lcd->write(0);
    lcd->setCursor(a,row + 0);
    lcd->write(1);
    lcd->setCursor(b,row + 1);
    lcd->write(2);
    lcd->setCursor(b,row + 0);
    lcd->write(3);
    lcd->setCursor(c,row + 1);
    lcd->write(4);
    lcd->setCursor(c,row + 0);
    lcd->write(5);
}

void screen::testChar(){
}

void screen::buildChar(std::vector<std::vector<byte>> vec){
    unsigned int i = 0;
    for(i = 0; i < vec.size(); i++){
        lcd->createChar(i, this->vectorToByteArray( vec[i] ) );
    }
}


void screen::wifiState_showChar(bool forceUpdate){
    long rand;
    if(false == forceUpdate){
        if( wifiServer::getInstance()->isCreatureUpdated() == false ){
            return;
        }
        wifiServer::getInstance()->setCreatureUpdated();
    }
    Serial.print("creature state:   ");
    Serial.println( static_cast<int>(  wifiServer::getInstance()->getCreatureToShow()  ) );
    switch ( wifiServer::getInstance()->getCreatureToShow() )
    {
        case wifiServer::creatures::WALKING_MAN :
            lcd->clear();
            buildChar(this->getWalkingMan());
            write6blockCharacter();
            break;
        case wifiServer::creatures::SMILE:
            lcd->clear();
            Serial.println("->Smile<-");
            buildChar(this->getSmile());
            write6blockCharacterStandartWay();
            break;
        case wifiServer::creatures::THUMB_DOWN:
            lcd->clear();
            buildChar(this->thumbDown());
            write6blockCharacter();
            break;
        case wifiServer::creatures::ROULETTE:
            rand = random(0,6);
            setRandomChar(rand);
            break;
        default:
            break;
    }

    
    return;
}

void screen::setRandomChar(int rand){
    if(wifiServer::getInstance()->isRandomSymbolUpdated() == false){
        return;
    }
    wifiServer::getInstance()->setRandomSymbolUpdated(false);

    int row = wifiServer::getInstance()->getRow();
    int col = wifiServer::getInstance()->getCol();
    switch (rand)
    {
    case 0:
        drawDuck(row,col);
    break;
    case 1:
        drawNote(row,col);
    break;
    case 2:
        drawBell(row,col);
    break;
    case 3:
        drawClock(row,col);
    break;
    case 4:
        drawHeart(row,col);
    break;
    case 5:
        drawCheck(row,col);
    break;
    case 6:
        drawCross(row,col);
    break;
    default:
        break;
    }
}

void screen::wifiState_showIP(bool forceUpdate){
    if(false == forceUpdate){
        if( wifi->getState() == wifiLastState &&
            lastIPValue == wifi->getIPAddress()){ 
                return; 
            }
    }

    lcd->clear();
    lcd->setCursor(0,1);
    lcd->print("IP address:");
    lcd->setCursor(0,2);
    String ip = wifi->getIPAddress();
    lcd->print( ip );
    lastIPValue = ip;
}

void screen::wifiState_createCharacter(bool forceUpdate){
    if( wifiServer::getInstance()->isCreatureUpdated() == false ){
        return;
    }
    wifiServer::getInstance()->setCreatureUpdated();
    std::vector<byte> cell = wifiServer::getInstance()->getCellArray();
    int row = wifiServer::getInstance()->getRow();
    int col = wifiServer::getInstance()->getCol();
    Serial.println("Update");
    lcd->createChar(this->cellCounter, this->vectorToByteArray( cell ) );
    lcd->setCursor(col,row);
    lcd->write(this->cellCounter++);
}

void screen::wifiUpdateMethod(){
    wifiServer::state currentState = wifi->getState();

    if(wifiLastState != currentState){
        Serial.print("wifi state:   ");
        Serial.println( static_cast<int>(  currentState  ) );
    }

    switch(currentState){
        case wifiServer::state::IP_ADDRESS :
            wifiState_showIP(this->firstTimeInThisState);
        break;
        case wifiServer::state::CHOOSE_CHARACTER :
            wifiState_showChar(this->firstTimeInThisState);
        break;
        case wifiServer::state::CREATE_YOUR_OWN_CREATURE:
            wifiState_createCharacter(this->firstTimeInThisState);
        break; 
        case wifiServer::state::LAST_STATE:
        break;
        default:
        break;
    }
    wifiLastState = currentState;
    if(  wifiServer::getInstance()->getClearScreen()   ){
        Serial.println("clear");
        lcd->clear();
        this->cellCounter = 0;
        wifiServer::getInstance()->setScreenCleared();
    }
}