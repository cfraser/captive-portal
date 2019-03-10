//
// Created by cfraser on 2018-12-02.
//
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include <espconfig.h>
#include <cstring>

ESP8266WebServer httpServer(80);
WebSocketsServer webSocket(81);
ESPConfig config;
const String INDEX_SOURCE = "<div style=\"position:absolute; left:280px; top:10px;\"></div><div style=\"padding: 15px\"> <button style=\"width: 175px;height: 100px;padding: 15px;margin: 20px\" onclick=\"on()\">On</button> <button style=\"width: 175px;height: 100px;padding: 15px;margin: 20px\" onClick=\"off()\">Off</button></div><script>var connection=new WebSocket('ws://' + location.hostname + ':81/', ['arduino']); connection.onopen=function(){connection.send('Connect ' + new Date());}; connection.onerror=function(error){console.log('WebSocket Error ', error);}; connection.onmessage=function(e){console.log('Server: ', e.data);}; connection.onclose=function(){console.log('WebSocket connection closed');}; function on(){connection.send(\"O\");}function off(){connection.send(\"F\");}</script>";
const int MS_PER_FRAME = 16; // 60 fps


void startOTA(void) {
    Serial.println("Starting OTA");
    ArduinoOTA.setHostname(config.getHostName());
    ArduinoOTA.onStart([]() { // switch off all the PWMs during upgrade
    });

    ArduinoOTA.onEnd([]() { // do a fancy thing with our board led at end
    });

    ArduinoOTA.onError([](ota_error_t error) {
        (void)error;
        delay(2000);
        ESP.restart();
    });

    /* setup the OTA httpServer */
    Serial.println("OTA Started");
    ArduinoOTA.begin();
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) { // When a WebSocket message is received
    switch (type) {
        case WStype_DISCONNECTED:             // if the websocket is disconnected
            Serial.printf("[%u] Disconnected!\n", num);
            break;
        case WStype_CONNECTED: {              // if a new websocket connection is established
            IPAddress ip = webSocket.remoteIP(num);
            Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
        }
            break;
        case WStype_TEXT:                     // if new text data is received
            Serial.printf("[%u] get Text: %s\n", num, payload);
            if (payload[0] == '#') {            // we get RGB data
            } else if (payload[0] == 'C') {
                char* buf = new char[length];
                strncpy(buf, (const char*) payload[1], length - 1);
                Serial.println("Received config: ");
                Serial.println(buf);
            } else if (payload[0] == 'M') {

            }
            break;
        default:
            Serial.print("Unrecognized websocket event: ");
            Serial.println((char*) payload);
    }
}

void initWebSocket() { // Start a WebSocket httpServer
    webSocket.begin();                          // start the websocket httpServer
    webSocket.onEvent(webSocketEvent);          // if there's an incomming websocket message, go to function 'webSocketEvent'
}

void handleNotFound(){ // if the requested file or page doesn't exist, return a 404 not found error
    httpServer.send(404, "text/plain", "404: File Not Found");
}


void handleRootPath() {
    httpServer.send(200, "text/html", INDEX_SOURCE );
}

void initHttpServer() { // Start a HTTP httpServer with a file read handler and an upload handler
    httpServer.on("/", handleRootPath);
    httpServer.onNotFound(handleNotFound);          // if someone requests any other file or page, go to function 'handleNotFound'
    httpServer.begin();                             // start the HTTP httpServer
    //Serial.println("HTTP httpServer started.");
}

void initWifi() {
    if (config.wasLoaded()) {
        WiFi.mode(WIFI_STA);
        WiFi.begin(config.getSsid(), config.getPassword());
        Serial.print("Connecting to ");
        Serial.print(config.getSsid());
        Serial.println(".");
        bool connected = false;
        while (!connected) {
            switch(WiFi.waitForConnectResult()) {
                case WL_CONNECT_FAILED:
                    switch (wifi_station_get_connect_status()) {
                        case STATION_CONNECT_FAIL:
                            Serial.println("Connect failed!");
                            break;
                        case STATION_WRONG_PASSWORD:
                            Serial.println("Incorrect password!");
                            break;
                        default:
                            break;
                    }
                    WiFi.mode(WIFI_AP);
                    break;
                case WL_NO_SSID_AVAIL:
                    Serial.printf("The ssid %s was could not be found!", config.getSsid());
                    WiFi.mode(WIFI_AP);
                    break;
                case WL_CONNECTED:
                    // Connected means it got an IP.
                    connected = true;
                    break;
                default:
                    break;
            }
            Serial.println("Retrying connection...");
        }
        WiFi.begin(config.getSsid(), config.getPassword());
        Serial.println("My IP is: ");
        Serial.println(WiFi.localIP());
    } else {
        WiFi.mode(WIFI_AP);
        WiFi.softAP(config.getSsid(), config.getPassword());
        Serial.printf("No config loaded, using AP mode with the SSID of [%s] and password [%s].\n", config.getSsid(), config.getPassword());
        Serial.printf("My IP is: %s\n", WiFi.softAPIP().toString().c_str());
    }
}

void initMDNS() { // Start the mDNS responder
    MDNS.begin(config.getMdnsName());                        // start the multicast domain name httpServer
    Serial.print("mDNS responder started: http://");
    Serial.print(config.getMdnsName());
    Serial.println(".local");
}

void setup(void)
{
    if (!config.loadConfig()) {
        Serial.println("Config not found. Using defaults.");
    }
    // Start Serial
    Serial.begin(74880);
    Serial.println("Starting.");
    delay(250);
    initWifi();
    Serial.println("WIFI: Ready.");
    initMDNS();
    Serial.println("MDNS: Ready.");
    initHttpServer();
    Serial.println("WWW: Ready.");
    initWebSocket();
    Serial.println("Websocket: Ready.");
    Serial.println("ESP Ready.");
}

void processInput() {
    webSocket.loop();                           // constantly check for websocket events
    httpServer.handleClient();                      // run the httpServer
}

void update() {
    ArduinoOTA.handle();
}

void render() {
}

void loop() {
    unsigned long start = millis();
    processInput();
    update();
    render();
    unsigned long frameDelay = MS_PER_FRAME - (millis() - start);
    delay(frameDelay);
}