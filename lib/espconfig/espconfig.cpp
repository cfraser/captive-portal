#include "espconfig.h"


bool ESPConfig::loadConfig() {
    loadSuccessful = false;

    File configFile = SPIFFS.open(CONFIG_FILE, "r");
    if (!configFile) {
        Serial.println("Failed to open config file");
        return false;
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

    StaticJsonDocument<1024> json;
    deserializeJson(json, buf.get());

    if (!json.isNull()) {
        Serial.println("Failed to parse config file");
        return false;
    }

    ssid = (const char *) json[SSID];
    password = (const char *) json[PASSWORD];
    hostName = (const char *) json[HOSTNAME];
    mdns = (const char *) json[MDNS];

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
    ssid = "";
    password = "newespwhodis";
    hostName = "esp8266-";
    mdns = "";

    uint8_t mac[6];
    char macStr[6] = { 0 };
    wifi_get_macaddr(0x0, mac);
    sprintf(macStr, "%02X%02X",  mac[4], mac[5]);
    hostName += macStr;
    mdns = hostName;
    ssid = hostName;
}

String ESPConfig::getSsid() const {
    return ssid;
}

String ESPConfig::getPassword() const {
    return password;
}

String ESPConfig::getHostName() const {
    return hostName;
}

String ESPConfig::getMdnsName() const {
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

String ESPConfig::getConfig() {
    return "{notimplemented: ''}";
}

String ESPConfig::getEspInfo() {
    DynamicJsonDocument json(1024);
    //ESPBy.getVcc() ⇒ may be used to measure supply voltage. ESP needs to reconfigure the ADC at startup in order for this feature to be available. ⇒ https://github.com/esp8266/Arduino/blob/master/doc/libraries.md#user-content-esp-specific-apis
    json["bootVersion"] =  ESP.getBootVersion();
    json["bootMode"] =  ESP.getBootMode();
    json["chipId"] =  ESP.getChipId();
    json["cpuFreqMhz"] =  ESP.getCpuFreqMHz();
    json["cycleCount"] =  ESP.getCycleCount();
    json["flashChipId"] =  ESP.getFlashChipId();
    json["flashChipRealSize"] =  ESP.getFlashChipRealSize();
    json["flashChipSize"] =  ESP.getFlashChipSize();
    json["flashChipSpeed"] =  ESP.getFlashChipSpeed();
    json["flashChipMode"] =  ESP.getFlashChipMode();
    json["flashChipSizeByChipId"] =  ESP.getFlashChipSizeByChipId();
    json["freeHeap"] =  ESP.getFreeHeap();
    json["freeSketchSpace"] =  ESP.getFreeSketchSpace();
    json["sdkVersion"] =  ESP.getSdkVersion();
    json["sketchSize"] =  ESP.getSketchSize();
    String retVal;
    serializeJson(json, retVal);
    return retVal;
}
