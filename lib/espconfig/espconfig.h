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
    String getEspInfo();
    String getConfig();

    String getSsid() const;
    String getPassword() const;
    String getHostName() const;
    String getMdnsName() const;

protected:
    void setSsid(char *ssid);
    void setPassword(char *password);
    void setHostName(char *hostName);
    void setMdns(char *mdns);

private:
    bool loadSuccessful = false;

    const String CONFIG_FILE = "/config.json";
    const String SSID = "ssid";
    const String PASSWORD = "pw";
    const String HOSTNAME = "hn";
    const String MDNS = "mdns";

    String ssid;
    String password;
    String hostName;
    String mdns;
};


#endif //MINIMAL_CONFIG_H
