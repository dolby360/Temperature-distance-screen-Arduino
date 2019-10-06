
#ifndef __WIFI__
#define __WIFI__

#include "stdfx.hpp"
#include "timer.hpp"

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ArduinoJson.h>

#ifndef STASSID
#define STASSID "Pixel"
#define STAPSK  "somePasswordHere"
#endif

class wifiServer : public observer{
    public:
        static wifiServer* getInstance();
        static wifiServer* getInstanceAndTryToSetTimer(timer* myTimer);
        void update();
        void sendPlainText(String str);
        String childName(){
            return "wifiServer";
        }
        String getIPAddress(){
            return this->ipAdress;
        }

        enum state{
            IP_ADDRESS,
            CHARACTERS,
            CREATE_YOUR_OWN_CREATURE,
            LAST_STATE,
        };
        state getState(){
            return myState;
        }
        static JsonObject getArgs();
        static String getArgsAsString();

        /****Create new creature*****/
        int getRow(){return row;}
        int getCol(){return col;}
        std::vector<byte> getCellArray(){return cellArray;}
        bool isCreatureUpdated(){return creatureUpdated;}
        void setCreatureUpdated(){ this->creatureUpdated = false;}
        /****************************/

        bool getClearScreen(){return this->clearScreen;}
        void setScreenCleared(){this->clearScreen = false;}
    private:
        //Don't go blew 0.5s with interval value
        wifiServer(timer* myTimer,int interval = 1000);
        static void handleClearScreen(){
            wifiServer::getInstance()->clearScreen = true;
            server->send(200, "text/plain", "OK");
        }
        bool clearScreen;
        static void handleRoot();
        static void handleNotFound();
        /****Create new creature*****/
        static void handleCreateChar();
        void storeNewCreatureData(String _row,String _col,String _cell);
        int row;
        int col;
        bool creatureUpdated;
        std::vector<byte> cellArray;
        /****************************/
        void toggleState();
        state myState;
        const char* ssid;
        const char* password;
        String ipAdress;
        static ESP8266WebServer* server;
        
        static wifiServer* instance;
        bool handleClientFlag;
};


#endif


