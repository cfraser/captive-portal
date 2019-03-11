//
// Created by cfraser on 2019-03-03.
//

#ifndef MINIMAL_CONFIG_H
#define MINIMAL_CONFIG_H

#include <ArduinoJson.h>
#include <FS.h>
#include <memory>
#include <cstring>
#include <user_interface.h>

class ESPConfig {
public:
    ESPConfig();

    bool loadConfig();
    bool saveConfig();
    bool wasLoaded();
    char* getEspInfo();

    char* getSsid() const;
    char* getPassword() const;
    char* getHostName() const;
    char* getMdnsName() const;

protected:
    void setSsid(char *ssid);
    void setPassword(char *password);
    void setHostName(char *hostName);
    void setMdns(char *mdns);

private:
    bool loadSuccessful = false;

    const char* CONFIG_FILE = "/config.json";
    const char* SSID = "ssid";
    const char* PASSWORD = "pw";
    const char* HOSTNAME = "hn";
    const char* MDNS = "mdns";

    char* ssid;
    char* password;
    char* hostName;
    char* mdns;
};


#endif //MINIMAL_CONFIG_H
