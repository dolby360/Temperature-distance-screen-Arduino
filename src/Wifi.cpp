
#include "../include/Wifi.hpp"

ESP8266WebServer* wifiServer::server;
wifiServer* wifiServer::instance = 0;

wifiServer* wifiServer::getInstance()
{
    if (instance == NULL)
    {
        return NULL;
    }
    return instance;
}

wifiServer* wifiServer::getInstanceAndTryToSetTimer(timer* myTimer)
{
    if (instance == NULL)
    {
        instance = new wifiServer(myTimer);
    }
    return instance;
}



wifiServer::wifiServer(timer* myTimer,int interval):
observer(myTimer,interval){
    server = new ESP8266WebServer(80);
    const char* ssid = STASSID;
    const char* password = STAPSK;
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    myState = state::IP_ADDRESS;
}

void wifiServer::toggleState(){
    state nextState = static_cast<state>( (static_cast<int>(myState) + 1) % (LAST_STATE + 1) ); 
    myState = nextState;
    if(myState == state::LAST_STATE){
        state firstState = static_cast<state>( 0 );  
        myState = firstState; 
    }
}

//Should be updated at most every 0.5s
void wifiServer::update(){
    //Serial.println("");
    // Wait for connection
    wl_status_t stat = WiFi.status();
    if(stat != WL_CONNECTED) {
        // Serial.print(".");
        this->ipAdress = "";
        this->handleClientFlag = true;
        return;
    }
    server->handleClient();
    
    // if (MDNS.begin("esp8266")) {
    //     // Serial.println("MDNS responder started");
    // }

    // Serial.println("HTTP server started");

    if(this->handleClientFlag){   
        this->handleClientFlag = false;
        server->on("/",wifiServer::handleRoot);
        // server->on("/changeState",wifiServer::changeState);
        server->onNotFound(handleNotFound);
        server->begin();
        this->ipAdress =  WiFi.localIP().toString();
        Serial.println("");
        Serial.println("IP address: ");
        Serial.println(this->ipAdress);
    }
}

void wifiServer::handleRoot(){
    String input = wifiServer::getArgsAsString();
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, input);
    JsonObject obj = doc.as<JsonObject>();
    String state = obj[String("state")];
    if(state == "createCreature"){
        wifiServer::getInstance()->myState = CHARACTERS;
    }
    server->send(200, "text/plain", "OK");
}


void wifiServer::handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server->uri();
  message += "\nMethod: ";
  message += (server->method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server->args();
  message += "\n";
  for (uint8_t i = 0; i < server->args(); i++) {
    message += " " + server->argName(i) + ": " + server->arg(i) + "\n";
  }
  server->send(404, "text/plain", message);
}

String wifiServer::getArgsAsString(){
    if(false == server->hasArg("plain")){
        Serial.println("Has not");
        Serial.println(server->argName(0));
        server->send(200, "text/plain", "no args");
    }
    // Serial.println(server->arg("plain"));
    String input = server->arg("plain");
    return input;
}
