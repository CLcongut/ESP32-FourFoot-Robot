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

void Display::configNetwork()
{
    oled.clearBuffer();
    oled.drawStr(10, 20, "WiFi Config!");
    oled.sendBuffer();
}

void Display::menuWiFiMode(bool mode)
{
    oled.clearBuffer();
    oled.drawStr(0, 20, "AP Mode");
    oled.drawStr(0, 40, "STA Mode");
    oled.drawStr(0, 60, "OTA Update");
    oled.setFont(u8g2_font_crox1h_tr);
    oled.drawStr(100, 60, "boot");
    oled.setFont(u8g2_font_crox2h_tr);
    switch (mode)
    {
    case 0:
        oled.drawTriangle(80, 15, 90, 10, 90, 20);
        break;
    case 1:
        oled.drawTriangle(80, 35, 90, 30, 90, 40);
        break;
    }
    oled.sendBuffer();
}

void Display::modeSwitch(bool mode)
{
    oled.clearBuffer();
    if (!mode)
    {
        oled.drawStr(20, 20, "Switch to");
        oled.drawStr(20, 40, "AP Mode!");
    }
    else
    {
        oled.drawStr(20, 20, "Switch to");
        oled.drawStr(20, 40, "STA Mode!");
    }
    oled.sendBuffer();
}

// void Display::numberCtrl(int number)
// {
// }

void Display::pairWithMotion(int expression)
{
    oled.clearBuffer();
    switch (expression)
    {
    case 0:
        oled.drawXBMP(2, 2, 128, 64, zhengchang); // backward();
        break;
    case 1:
        oled.drawXBMP(2, 2, 128, 64, laia); // come();
        break;
    case 2:
        oled.drawXBMP(2, 2, 128, 64, goupao); // dog();
        break;
    case 3:
        oled.drawXBMP(2, 2, 128, 64, yaobai); // dance();
        break;
    case 4:
        oled.drawXBMP(2, 2, 128, 64, shanzi); // fan();
        break;
    case 5:
        oled.drawXBMP(2, 2, 128, 64, zhengchang); // forward();
        break;
    case 6:
        oled.drawXBMP(2, 2, 128, 64, nihao); // hello();
        break;
    case 7:
        oled.drawXBMP(2, 2, 128, 64, zhengchang); // left();
        break;
    case 8:
        oled.drawXBMP(2, 2, 128, 64, goupao); // lie();
        break;
    case 9:
        oled.drawXBMP(2, 2, 128, 64, laia); // middle();
        break;
    case 10:
        oled.drawXBMP(2, 2, 128, 64, zhengchang); // normal();
        break;
    case 11:
        oled.drawXBMP(2, 2, 128, 64, zhengchang); // right();
        break;
    case 12:
        oled.drawXBMP(2, 2, 128, 64, zhengchang); // stand();
        break;
    case 13:
        oled.drawXBMP(2, 2, 128, 64, shuijiao); // sleep1();
        break;
    case 14:
        oled.drawXBMP(2, 2, 128, 64, shuijiao); // sleep2();
        break;
    case 15:
        oled.drawXBMP(2, 2, 128, 64, touxiang); // surrender();
        break;
    default:
        break;
    }
    oled.sendBuffer();
}

void Display ::showExpression(int expression)
{
    oled.clearBuffer();
    switch (expression)
    {
    case 0:
        oled.drawXBMP(2, 2, 128, 64, youhao);
        break;
    case 1:
        oled.drawXBMP(2, 2, 128, 64, zhengchang);
        break;
    case 2:
        oled.drawXBMP(2, 2, 128, 64, shuijiao);
        break;
    case 3:
        oled.drawXBMP(2, 2, 128, 64, nihao);
        break;
    case 4:
        oled.drawXBMP(2, 2, 128, 64, laia);
        break;
    case 5:
        oled.drawXBMP(2, 2, 128, 64, goupao);
        break;
    case 6:
        oled.drawXBMP(2, 2, 128, 64, touxiang);
        break;
    case 7:
        oled.drawXBMP(2, 2, 128, 64, yaobai);
        break;
    case 8:
        oled.drawXBMP(2, 2, 128, 64, shanzi);
        break;

    default:
        break;
    }
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

void Display::showOTAUpdate()
{
    oled.clearBuffer();
    oled.drawStr(14, 30, "OTA Updating...");
    // oled.setCursor(0, 40);
    // oled.println(progress);
    oled.sendBuffer();
}

void Display::showOTAURLchanged()
{
    oled.clearBuffer();
    oled.drawStr(5, 30, "OTA URL Changed!");
    oled.sendBuffer();
}