//
// Created by cfraser on 2018-12-02.
//
#include <ArduinoOTA.h>
#include <Arduino.h>
#include <string>
#include <DNSServer.h>
#include <espconfig.h>
#include <ESP8266mDNS.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WebSocketsServer.h>
#include "wwwcontent.h"

ESP8266WebServer httpServer(80);
WebSocketsServer webSocket(81);
ESPConfig config;
DNSServer dnsServer;

const byte DNS_PORT = 53;
const int MS_PER_FRAME = 16; // 60 fps
const IPAddress CAPTIVE_IP(10, 0, 0, 1);
const IPAddress CAPTIVE_NETMASK(255, 255, 255, 0);



void startOTA(void) {
    Serial.println("Starting OTA");
    ArduinoOTA.setHostname(config.getHostName().c_str());
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
            //Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
        }
            break;
        case WStype_TEXT:                     // if new text data is received
            Serial.printf("[%u] get Text: %s\n", num, payload);
            if (payload[0] == '{') {
                String buf;
                buf = (const char*) payload;
                Serial.println("Received config: ");
                // TODO: store the config.
                Serial.println(buf);
            } else if (payload[0] == 'M') {

            }
            break;
        default:
            Serial.print("Unrecognized websocket event: ");
            Serial.println((char*) payload);
    }
}

void initWebSocket() {
    // Start a WebSocket httpServer
    webSocket.begin();                          // start the websocket httpServer
    webSocket.onEvent(webSocketEvent);          // if there's an incomming websocket message, go to function 'webSocketEvent'
}

String getContentType(String filename) { // convert the file extension to the MIME type
    if (filename.endsWith(".html") || filename.endsWith(".htm")) return "text/html";
    else if (filename.endsWith(".css")) return "text/css";
    else if (filename.endsWith(".js")) return "application/javascript";
    else if (filename.endsWith(".ico")) return "image/x-icon";
    return "text/plain";
}

void addNoCacheHeader() {
    httpServer.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
    httpServer.sendHeader("Pragma", "no-cache");
    httpServer.sendHeader("Expires", "-1");
}

void addGZipHeader() {
    httpServer.sendHeader("Content-Encoding",  "gzip");
}

void addContentLengthHeader(size_t length) {
    httpServer.sendHeader("Content-Length",  String(length));
}

const String responseCodeToString(int code) {
    switch (code) {
        case 100:
            return F("Continue");
        case 101:
            return F("Switching Protocols");
        case 200:
            return F("OK");
        case 201:
            return F("Created");
        case 202:
            return F("Accepted");
        case 203:
            return F("Non-Authoritative Information");
        case 204:
            return F("No Content");
        case 205:
            return F("Reset Content");
        case 206:
            return F("Partial Content");
        case 300:
            return F("Multiple Choices");
        case 301:
            return F("Moved Permanently");
        case 302:
            return F("Found");
        case 303:
            return F("See Other");
        case 304:
            return F("Not Modified");
        case 305:
            return F("Use Proxy");
        case 307:
            return F("Temporary Redirect");
        case 400:
            return F("Bad Request");
        case 401:
            return F("Unauthorized");
        case 402:
            return F("Payment Required");
        case 403:
            return F("Forbidden");
        case 404:
            return F("Not Found");
        case 405:
            return F("Method Not Allowed");
        case 406:
            return F("Not Acceptable");
        case 407:
            return F("Proxy Authentication Required");
        case 408:
            return F("Request Time-out");
        case 409:
            return F("Conflict");
        case 410:
            return F("Gone");
        case 411:
            return F("Length Required");
        case 412:
            return F("Precondition Failed");
        case 413:
            return F("Request Entity Too Large");
        case 414:
            return F("Request-URI Too Large");
        case 415:
            return F("Unsupported Media Type");
        case 416:
            return F("Requested range not satisfiable");
        case 417:
            return F("Expectation Failed");
        case 500:
            return F("Internal Server Error");
        case 501:
            return F("Not Implemented");
        case 502:
            return F("Bad Gateway");
        case 503:
            return F("Service Unavailable");
        case 504:
            return F("Gateway Time-out");
        case 505:
            return F("HTTP Version not supported");
        default:
            return F("");
    }
}

void sendRawHeader(int code, size_t contentLength) {
    String response = String(F("HTTP/1.1 "));
    response += String(code);
    response += " ";
    response += responseCodeToString(code);
    response += "\r\n";
    response += "Cache-Control: no-cache, no-store, must-revalidate\r\n";
    response += "Pragma: no-cache\r\n";
    response += "Expires: -1\r\n";
    response += "Content-Encoding: gzip\r\n";
//    response += "Accept-Ranges: none\r\n";
//    response += "Transfer-Encoding: chunked\r\n";
    response += "Connection: close\r\n";
    httpServer.sendContent(response);
}

void handleNotFound(){
    httpServer.send(404, "text/html", "");
    httpServer.client().stop();
    Serial.println("\t" + httpServer.uri() + " was not found.");
}


void handleRequest() {
    Serial.println("handleRequest: [ GET: " + httpServer.hostHeader() + httpServer.uri() + "]");
    String resourcePath = httpServer.uri();

    // if a folder is specified append index.html
    if (resourcePath.endsWith("/")) {
        resourcePath += "index.html";
        Serial.println("\t" + resourcePath);
    }

    boolean found = false;
    for (size_t x = 0; x < sizeof(wwwContent) / sizeof(wwwContent[0]);x++) {
        if (resourcePath.endsWith(wwwContent[x].name)) {
            sendRawHeader(200, wwwContent[x].size);
            httpServer.sendContent("Content-Length: " + String(wwwContent[x].size) + "\r\n");
            httpServer.sendContent("Content-Type: " + getContentType(resourcePath) + "\r\n\r\n");
            httpServer.sendContent_P((char *) &wwwContentData[wwwContent[x].offset], wwwContent[x].size);
            found = true;
            break;
        }
    }

    if (!found) {
        handleNotFound();
    }
}

String toStringIp(IPAddress ip) {
    String res = "";
    for (int i = 0; i < 3; i++) {
        res += String((ip >> (8 * i)) & 0xFF) + ".";
    }
    res += String(((ip >> 8 * 3)) & 0xFF);
    return res;
}

void handleRedirect(){
        // if the requested file or page doesn't exist, redirect to root.
        httpServer.sendHeader("Location", String("http://") + toStringIp(httpServer.client().localIP()) + "/index.html", true);
        httpServer.send(302, "text/plain", "");
        httpServer.client().stop();
}



void initHttpServer() { // Start a HTTP httpServer with a file read handler and an upload handler
    httpServer.on("/generate_204", HTTP_GET, handleNotFound);
    httpServer.on("/fwlink", HTTP_GET, handleNotFound);
    httpServer.on("/wpad.dat", HTTP_GET, handleNotFound);
    httpServer.onNotFound(handleRequest);
    httpServer.begin();
}

void initDNS() {
    /* Setup the DNS server redirecting all the domains to the apIP */
    dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
    dnsServer.start(DNS_PORT, "*", CAPTIVE_IP);
}

void initCaptivePortal() {
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(CAPTIVE_IP, CAPTIVE_IP, CAPTIVE_NETMASK);
    WiFi.softAP(config.getSsid(), config.getPassword());
    Serial.printf("Config: Using AP mode with the SSID of [%s] and password [%s].\n", config.getSsid().c_str(), config.getPassword().c_str());
    Serial.printf("Config: My IP is: %s\n", WiFi.softAPIP().toString().c_str());
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
                    WiFi.disconnect();
                    Serial.printf("The ssid %s was could not be found!", config.getSsid().c_str());
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
            delay(1000);
        }
        WiFi.begin(config.getSsid(), config.getPassword());
        Serial.println("Captive portal IP is: ");
        Serial.println(WiFi.localIP());
    } else {
        // Start captive portal.
        initCaptivePortal();
        initDNS();
    }
}

void initMDNS() { // Start the mDNS responder

    // start the multicast domain name httpServer
    if (!MDNS.begin(config.getMdnsName())) {
        Serial.print("Unable to start mDNS responder!");
    } else {
        Serial.print("mDNS responder started: http://");
        Serial.print(config.getMdnsName());
        Serial.println(".local");

        MDNS.addService("http", "tcp", 80);
    }
}

void initSPIFFs() {
    SPIFFS.begin();
    Dir dir = SPIFFS.openDir("/");
//    while(dir.next()) {
//        Serial.println(dir.fileName());
//    }
}

void setup(void) {
    // Start Serial
    Serial.begin(74880);
    Serial.println("Starting.");

    if (!config.loadConfig()) {
        Serial.println("Config: Not found. Using defaults.");
    } else {
        Serial.println("Config: Loaded.");
    }
    initSPIFFs();
    Serial.println("SPIFFs: Ready.");
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
    dnsServer.processNextRequest();

    httpServer.handleClient();
    webSocket.loop();
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
    unsigned long frameDelay = MS_PER_FRAME - (millis() - start) < 0 ? 0 : (millis() - start);
    delay(frameDelay);
}