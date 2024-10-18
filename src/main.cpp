#include <Arduino.h>
#include <WiFi.h>
#include <Preferences.h>
#include <FastLED.h>
#include <U8g2lib.h>
#include "motion.h"
#include "cconfig.h"
#include "display.h"
#include "otaupdata.h"

// static IPAddress remote_IP(192, 168, 31, 199);
static uint32_t remoteUdpPort = 8080;

static WiFiUDP udp;
static Motion motion;
static CRGB leds[2];
static Display display;
static Preferences prefs;

static TaskHandle_t xUDPTask = NULL;
static TaskHandle_t xMotionTask = NULL;
static TaskHandle_t xOLEDTask = NULL;
static TaskHandle_t xWS2812Task = NULL;
static TaskHandle_t xOTATask = NULL;

volatile bool isRGBenabled = false;
volatile bool isWiFiMode = false;
volatile bool isChoosed = false;

void ota_task(void *param)
{
  Serial.println("3 Second to update!");
  vTaskDelay(3000);
  xTaskNotify(xOLEDTask, 23, eSetValueWithOverwrite);

  for (;;)
  {
    OTAUpdate otaUpdate;
    otaUpdate.updataBin();

    vTaskDelay(1000);
    vTaskSuspend(NULL);
    vTaskDelete(NULL);
  }
}

void udp_control(void *param)
{
  prefs.begin("OffLine");
  isWiFiMode = prefs.getBool("isWiFiMode", true);
  // Serial.println(prefs.getString("WiFiSSID"));
  // Serial.println(prefs.getString("WiFiPSWD"));
  prefs.end();

  if (isWiFiMode)
  {
    WiFi.mode(WIFI_STA);
    WiFi.setSleep(false);
    prefs.begin("OffLine");
    WiFi.begin(prefs.getString("WiFiSSID").c_str(), prefs.getString("WiFiPSWD").c_str());
    prefs.end();
    while (WiFi.status() != WL_CONNECTED)
    {
      vTaskDelay(200);
    }
  }
  else
  {
    WiFi.mode(WIFI_AP);
    WiFi.softAP("ESP32-FFR-AP");
  }

  // Serial.println(WiFi.getMode());
  Serial.print("Connected, IP Address: ");
  Serial.println(WiFi.localIP());
  xTaskNotify(xOLEDTask, 17, eSetValueWithOverwrite);
  udp.beginPacket("255.255.255.255", remoteUdpPort);
  udp.print("#FFR ");
  udp.print(WiFi.localIP());
  udp.print(" ");
  udp.print(WiFi.getMode());
  udp.print(" ");
  udp.print(isRGBenabled);
  udp.endPacket();
  udp.begin(remoteUdpPort);
  digitalWrite(SignalPin, LOW);
  for (;;)
  {
    // packetSize长度小于8时需要定义为8，并且使用memset清零
    size_t packetSize = udp.parsePacket();
    if (packetSize)
    {
      char val[packetSize];
      udp.read(val, packetSize);
      String recvStr = String(val);
      memset(val, 0, packetSize);
#ifdef UDPDEBUG
      Serial.print("UDP Received:");
      Serial.println(recvStr);

      udp.beginPacket(udp.remoteIP(), udp.remotePort());
      udp.print("Received:");
      udp.println(recvStr);
      udp.endPacket();

      if (recvStr.startsWith("/"))
      {
        if (recvStr.indexOf("motion") > 0)
        {
          String numberInCmd = recvStr.substring(recvStr.indexOf(" ") + 1);
          int cmdNum = numberInCmd.toInt();
          motion.controlNumber(cmdNum);
        }
        else if (recvStr.indexOf("single") > 0)
        {
          String singleCmd = recvStr.substring(recvStr.indexOf(" ") + 1);
          char singleCmdChar[singleCmd.length() + 1];
          singleCmd.toCharArray(singleCmdChar, singleCmd.length() + 1);
          int servo, angleS, angleE;
          sscanf(singleCmdChar, "%d %d %d", &servo, &angleS, &angleE);
          motion.ctlSingleServo(servo, angleS, angleE);
        }
        else if (recvStr.indexOf("freq") > 0)
        {
          String freqInCmd = recvStr.substring(recvStr.indexOf(" ") + 1);
          float cmdFreq = freqInCmd.toFloat();
          motion.setFrequency(cmdFreq);
        }
        else if (recvStr.indexOf("setWiFi") > 0)
        {
          if (WiFi.getMode() == WIFI_AP)
          {
            String rcvWiFiInfo = recvStr.substring(recvStr.indexOf(" ") + 1);
            String rcvWiFiSSID = rcvWiFiInfo.substring(0, rcvWiFiInfo.indexOf(" "));
            String rcvWiFiPSWD = rcvWiFiInfo.substring(rcvWiFiInfo.indexOf(" ") + 1);
            prefs.begin("OffLine");
            prefs.putString("WiFiSSID", rcvWiFiSSID);
            prefs.putString("WiFiPSWD", rcvWiFiPSWD);
            prefs.end();
            xTaskNotify(xOLEDTask, 21, eSetValueWithOverwrite);
          }
        }
        else if (recvStr.indexOf("WiFiMode") > 0)
        {
          String rcvWiFiMode = recvStr.substring(recvStr.indexOf(" ") + 1);
          int rcvNumWiFiMode = rcvWiFiMode.toInt() - 1;
          isWiFiMode = rcvNumWiFiMode;
          prefs.begin("OffLine");
          if (prefs.getBool("isWiFiMode") != isWiFiMode)
          {
            prefs.putBool("isWiFiMode", isWiFiMode);
          }
          prefs.end();
          xTaskNotify(xOLEDTask, 22, eSetValueWithOverwrite);
        }
        else if (recvStr.indexOf("update") > 0)
        {
          xTaskCreate(ota_task, "ota_task", 4096, NULL, 2, &xOTATask);
        }
      }
#endif
      if (recvStr.startsWith("#"))
      {
        String notifyValueStr = recvStr.substring(recvStr.indexOf("#") + 1);
        uint32_t notifyValue = notifyValueStr.toInt();
        if (notifyValue > 18)
        {
          switch (notifyValue)
          {
          case 19:
            vTaskSuspend(xWS2812Task);
            leds[0] = CRGB::Black;
            leds[1] = CRGB::Black;
            FastLED.show();
            prefs.begin("OffLine");
            prefs.putBool("isRGBenabled", false);
            prefs.end();
            break;
          case 20:
            vTaskResume(xWS2812Task);
            prefs.begin("OffLine");
            prefs.putBool("isRGBenabled", true);
            prefs.end();
            break;

          default:
            break;
          }
        }
        else
        {
          xTaskNotify(xMotionTask, notifyValue, eSetValueWithOverwrite);
          xTaskNotify(xOLEDTask, notifyValue, eSetValueWithOverwrite);
        }
      }
    }
    vTaskDelay(1);
  }
}

void motion_task(void *param)
{
  motion.begin();
  uint32_t ulMotionValue = 0;
  for (;;)
  {
    xTaskNotifyWait(0, 0xff, &ulMotionValue, portMAX_DELAY);
    motion.controlNumber(ulMotionValue);
    vTaskDelay(1);
  }
}

void oled_task(void *param)
{
  display.begin();
  uint32_t ulOLEDValue = 0;
  for (;;)
  {
    if (xTaskNotifyWait(0, 0xff, &ulOLEDValue, 10) == pdTRUE && ulOLEDValue <= 16)
    {
      display.pairWithMotion(ulOLEDValue);
    }
    else
    {
      switch (ulOLEDValue)
      {
      case 17:
        display.showNetworkIP(WiFi.localIP());
        break;
      case 18:
        static int i = 0;
        display.showExpression(i);
        if (++i > 8)
        {
          i = 0;
        }
        break;
      case 21:
        display.configNetwork();
        break;
      case 22:
        display.modeSwitch(isWiFiMode);

        vTaskSuspend(xUDPTask);
        vTaskDelete(xUDPTask);
        xTaskCreatePinnedToCore(udp_control, "udp_control", 2048, NULL, 2, &xUDPTask, 0);
        break;
      case 23:
        display.showOTAUpdate();
        break;
      }
    }

    if (isChoosed)
    {
      digitalWrite(SignalPin, HIGH);
      isChoosed = false;
      prefs.begin("OffLine");
      isWiFiMode = prefs.getBool("isWiFiMode", true);
      prefs.end();
      while (!isChoosed)
      {
        display.menuWiFiMode(isWiFiMode);
        if (!digitalRead(BootPin))
        {
          vTaskDelay(20);
          while (!digitalRead(BootPin))
          {
          }
          xTaskCreate(ota_task, "ota_task", 4096, NULL, 2, &xOTATask);
          vTaskDelay(20);
        }
      }
      prefs.begin("OffLine");
      isChoosed = false;
      if (prefs.getBool("isWiFiMode") != isWiFiMode)
      {
        prefs.putBool("isWiFiMode", isWiFiMode);

        vTaskSuspend(xUDPTask);
        vTaskDelete(xUDPTask);
        xTaskCreatePinnedToCore(udp_control, "udp_control", 2048, NULL, 2, &xUDPTask, 0);
      }
      prefs.end();
      display.modeSwitch(isWiFiMode);
    }
    vTaskDelay(1);
  }
}

void ws2812_task(void *param)
{
  FastLED.addLeds<WS2812B, 5, GRB>(leds, 2);
  FastLED.setBrightness(255);
  FastLED.clear();
  FastLED.show();

  if (!isRGBenabled)
  {
    vTaskSuspend(NULL);
  }

  for (;;)
  {
    for (int i = 0; i < 256; i++)
    {
      leds[0] = CHSV(i, 255, 255);
      leds[1] = CHSV(i, 255, 255);
      FastLED.show();
      FastLED.delay(10);
    }
    for (int i = 255; i >= 0; i--)
    {
      leds[0] = CHSV(i, 255, 255);
      leds[1] = CHSV(i, 255, 255);
      FastLED.show();
      FastLED.delay(10);
    }
  }
}

void Key1Interrupt()
{
  // xTaskNotify(xOLEDTask, 21, eSetValueWithOverwrite);
  isWiFiMode = !isWiFiMode;
}

void Key2Interrupt()
{
  // xTaskNotify(xOLEDTask, 21, eSetValueWithOverwrite);
  isChoosed = true;
}

void setup()
{
  Serial.begin(115200);
  pinMode(SignalPin, OUTPUT);
  pinMode(BootPin, INPUT_PULLUP);

  prefs.begin("OffLine");
  isRGBenabled = prefs.getBool("isRGBenabled", false);
  prefs.end();

  attachInterrupt(Key1, Key1Interrupt, RISING);
  attachInterrupt(Key2, Key2Interrupt, RISING);

  xTaskCreatePinnedToCore(udp_control, "udp_control", 2048, NULL, 2, &xUDPTask, 0);
  xTaskCreatePinnedToCore(motion_task, "motion_task", 2048, NULL, 2, &xMotionTask, 0);
  xTaskCreate(oled_task, "oled_task", 2048, NULL, 2, &xOLEDTask);
  xTaskCreatePinnedToCore(ws2812_task, "ws2812_task", 2028, NULL, 2, &xWS2812Task, 0);
}

void loop()
{
  vTaskDelete(NULL);
  // digitalWrite(SignalPin, !digitalRead(SignalPin));
  // vTaskDelay(1000);
}
