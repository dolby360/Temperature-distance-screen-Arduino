
#include "../include/Wifi.hpp"

ESP8266WebServer* wifiServer::server;

wifiServer::wifiServer(timer* myTimer,int interval):
observer(myTimer,interval){
    server = new ESP8266WebServer(80);
    const char* ssid = STASSID;
    const char* password = STAPSK;
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

}

//Should be updated at most every 0.5s
void wifiServer::update(){
    //Serial.println("");
    // Wait for connection
    if(WiFi.status() != WL_CONNECTED) {
        // Serial.print(".");
        this->ipAdress = "";
        return;
    }else{
        server->handleClient();
        MDNS.update();
    }
    // Serial.println("");
    // Serial.print("Connected to ");
    // Serial.println(ssid);
    // Serial.print("IP address: ");
    // Serial.println(WiFi.localIP());
    this->ipAdress =  WiFi.localIP().toString();
    // Serial.println(this->ipAdress);
    
    if (MDNS.begin("esp8266")) {
        Serial.println("MDNS responder started");
    }
    server->on("/",wifiServer::handleRoot);
    server->on("/inline", []() {
        server->send(200, "text/plain", "this works as well");
    });
    server->onNotFound(handleNotFound);
    server->begin();
    // Serial.println("HTTP server started");
}

void wifiServer::handleRoot(){
    if(false == server->hasArg("plain")){
        Serial.println("Has not");
        Serial.println(server->argName(0));
        server->send(200, "text/plain", "no args");
        return;
    }
    Serial.println(server->arg("plain"));
    String input = server->arg("plain");
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, input);
    JsonObject obj = doc.as<JsonObject>();
    String f = obj[String("firstParam")];
    String s = obj[String("secondParam")];

    Serial.println(f);
    Serial.println(s);

    server->send(200, "text/plain", "hello from esp8266!");
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