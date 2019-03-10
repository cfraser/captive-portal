//
// Created by cfraser on 2019-03-03.
//
#include "espconfig.h"


bool ESPConfig::loadConfig() {
    loadSuccessful = false;

    File configFile = SPIFFS.open(CONFIG_FILE, "r");
    if (!configFile) {
        Serial.println("Failed to open config file");
    }

    size_t size = configFile.size();
    if (size > 1024) {
        Serial.println("Config file size is too large");
        return false;
    }

    // Allocate a buffer to store contents of the file.
    std::unique_ptr<char[]> buf(new char[size]);

    // We don't use String here because ArduinoJson library requires the input
    // buffer to be mutable. If you don't use ArduinoJson, you may as well
    // use configFile.readString instead.
    configFile.readBytes(buf.get(), size);
    configFile.flush();
    configFile.close();

    StaticJsonDocument<20> json;
    deserializeJson(json, buf.get());

    if (!json.isNull()) {
        Serial.println("Failed to parse config file");
        return false;
    }

    strcpy(ssid, json[SSID]);
    strcpy(password, json[PASSWORD]);
    strcpy(hostName, json[HOSTNAME]);
    strcpy(mdns, json[MDNS]);

    Serial.print("Loaded serverName: ");
    Serial.println(getSsid());
    Serial.print("Loaded password: ");
    Serial.println(getPassword());
    Serial.print("Loaded hostname: ");
    Serial.println(getHostName());

    loadSuccessful = true;
    return loadSuccessful;
}

bool ESPConfig::wasLoaded() {
    return loadSuccessful;
}

bool ESPConfig::saveConfig() {
    DynamicJsonDocument json(20);

    json[SSID] = ssid;
    json[PASSWORD] = password;
    json[HOSTNAME] = hostName;
    json[MDNS] = mdns;

    File configFile = SPIFFS.open(CONFIG_FILE, "w");
    if (!configFile) {
        Serial.println("Failed to open config file for writing");
        return false;
    }

    serializeJson(json, configFile);
    return true;
}



ESPConfig::ESPConfig() {
    ssid = (char*) "";
    password = (char*) "newphonewhodis";
    hostName = (char*) "esp8266-";
    mdns = (char*) "";

    uint8_t mac[6];
    char macStr[6] = { 0 };
    wifi_get_macaddr(0x0, mac);
    sprintf(macStr, "%02X%02X",  mac[4], mac[5]);
    strcat(hostName, macStr);
    strcpy(mdns, hostName);
}

char *ESPConfig::getSsid() const {
    return ssid;
}

char *ESPConfig::getPassword() const {
    return password;
}

char *ESPConfig::getHostName() const {
    return hostName;
}

char *ESPConfig::getMdnsName() const {
    return mdns;
}

void ESPConfig::setSsid(char *ssid) {
    ESPConfig::ssid = ssid;
}

void ESPConfig::setPassword(char *password) {
    ESPConfig::password = password;
}

void ESPConfig::setHostName(char *hostName) {
    ESPConfig::hostName = hostName;
}

void ESPConfig::setMdns(char *mdns) {
    ESPConfig::mdns = mdns;
}
