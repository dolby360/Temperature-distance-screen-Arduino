
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
        //Don't go blew 0.5s with interval value
        wifiServer(timer* myTimer,int interval = 1000);
        void update();
        void sendPlainText(String str);
        String childName(){
            return "wifiServer";
        }
        String getIPAddress(){
            return this->ipAdress;
        }

    private:
        static void handleRoot();
        static void handleNotFound();
        const char* ssid;
        const char* password;
        String ipAdress;
        static ESP8266WebServer* server;
};


#endif


