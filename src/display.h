#pragma once
#include <Arduino.h>
#include <U8g2lib.h>
#include "expression.h"

class Display
{
private:
    U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled = U8G2_SSD1306_128X64_NONAME_F_HW_I2C(U8G2_R2);

public:
    Display();
    ~Display();

    void begin();
    void menuWiFiMode(bool mode);
    void numberCtrl(int number);
    void pairWithMotion(int expression);
    void showExpression(int expression);
    void showNetworkIP(IPAddress IPAddress);
};