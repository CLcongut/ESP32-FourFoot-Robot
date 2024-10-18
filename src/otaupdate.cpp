#include "otaupdata.h"

OTAUpdate::OTAUpdate()
{
}

OTAUpdate::~OTAUpdate()
{
}

void OTAUpdate::updataBin(String updateURL)
{
    Serial.println("Start Update!");

    httpUpdate.onStart(updataStart);       // 当升级开始时
    httpUpdate.onEnd(updataEnd);           // 当升级结束时
    httpUpdate.onProgress(updataProgress); // 当升级中
    httpUpdate.onError(updataError);       // 当升级失败时

    t_httpUpdate_return ret = httpUpdate.update(UpdateClient, updateURL);
    switch (ret)
    {
    case HTTP_UPDATE_FAILED: // 当升级失败
        Serial.println("[update] Update Failed.");
        break;
    case HTTP_UPDATE_NO_UPDATES: // 当无升级
        Serial.println("[update] Update No Update.");
        break;
    case HTTP_UPDATE_OK: // 当升级成功
        Serial.println("[update] Update Success.");
        break;
    }
}

void OTAUpdate::updataEnd()
{
    Serial.println("CALLBACK:  HTTP update process finished");
}

void OTAUpdate::updataError(int error)
{
    Serial.printf("CALLBACK:  HTTP update fatal error code %d\n", error);
}

void OTAUpdate::updataProgress(int progress, int total)
{
    Serial.printf("CALLBACK:  HTTP update process at %d of %d bytes...\n", progress, total);
    digitalWrite(SignalPin, !digitalRead(SignalPin));
}

void OTAUpdate::updataStart()
{
    Serial.println("CALLBACK:  HTTP update process started");
}
