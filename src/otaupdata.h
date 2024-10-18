#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include <httpUpdate.h>

class OTAUpdate
{
private:
    String updateURL = "http://bin.bemfa.com/b/3BcNjQ0MmU1YjEzYWZiNDY0ZWIzY2VjNTYxYmM4NzI4ZTk=esp32FFRota.bin";
    WiFiClient UpdateClient;
    static void updataEnd();
    static void updataError(int error);
    static void updataProgress(int progress, int total);
    static void updataStart();

public:
    OTAUpdate();
    ~OTAUpdate();
    void updataBin();
};