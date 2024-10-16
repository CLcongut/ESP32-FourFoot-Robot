#include "display.h"

Display::Display()
{
}

Display::~Display()
{
}

void Display::begin()
{
    oled.begin();
    oled.clearBuffer();
    oled.setFont(u8g2_font_crox2h_tr);
    oled.drawStr(22, 20, "Hello, ESP32!");
    oled.sendBuffer();
}

void Display::showNetworkIP(IPAddress IPAddress)
{
    oled.clearBuffer();
    oled.drawStr(0, 20, "IP Address:");
    oled.setCursor(0, 40);
    oled.println(IPAddress);
    oled.sendBuffer();
}

void Display::numberCtrl(int number)
{
}

void Display::test1()
{
    oled.clearBuffer();
    oled.drawStr(0, 20, "Test 1");
    oled.sendBuffer();
}

void Display::test2()
{
    oled.clearBuffer();
    oled.drawStr(0, 20, "Test 2");
    oled.sendBuffer();
}