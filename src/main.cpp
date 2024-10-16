#include <Arduino.h>
#include <WiFi.h>
#include <FastLED.h>
#include <U8g2lib.h>
#include "motion.h"
#include "cconfig.h"
#include "display.h"

static IPAddress remote_IP(192, 168, 31, 199);
static uint32_t remoteUdpPort = 8080;

static WiFiUDP udp;
static Motion motion;
static CRGB leds[2];
static Display display;

static TaskHandle_t xMotionTask = NULL;
static TaskHandle_t xOLEDTask = NULL;
static TaskHandle_t xWS2812Task = NULL;

volatile bool WS2812Enable = true;

void udp_control(void *param)
{
  WiFi.mode(WIFI_STA);
  WiFi.setSleep(false);
  WiFi.begin(wifi_SSID, wifi_PSWD);
  while (WiFi.status() != WL_CONNECTED)
  {
    vTaskDelay(200);
  }
  Serial.print("Connected, IP Address: ");
  Serial.println(WiFi.localIP());
  xTaskNotify(xOLEDTask, 17, eSetValueWithOverwrite);
  udp.begin(remoteUdpPort);
  for (;;)
  {
    // packetSize长度小于8时需要定义为8，并且使用memset清零
    size_t packetSize = udp.parsePacket();
    if (packetSize)
    {
      char val[packetSize];
      udp.read(val, packetSize);
      String recvStr = String(val);
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
      }
#endif
      if (recvStr.startsWith("#"))
      {
        String notifyValueStr = recvStr.substring(recvStr.indexOf("#") + 1);
        uint32_t notifyValue = notifyValueStr.toInt();
        xTaskNotify(xMotionTask, notifyValue, eSetValueWithOverwrite);
        xTaskNotify(xOLEDTask, notifyValue, eSetValueWithOverwrite);
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
    xTaskNotifyWait(0, 0xff, &ulOLEDValue, portMAX_DELAY);
    if (ulOLEDValue <= 16)
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
      default:
        break;
      }
    }
    vTaskDelay(1);
  }
}

void ws2812_task(void *param)
{
  FastLED.addLeds<WS2812B, 5, GRB>(leds, 2);
  FastLED.setBrightness(255);
  FastLED.clear();
  leds[0] = CRGB::Red;
  leds[1] = CRGB::Red;
  FastLED.show();

  for (;;)
  {
    if (WS2812Enable)
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
    else
    {
      leds[0] = CRGB::Black;
      leds[1] = CRGB::Black;
      FastLED.show();
    }
  }
}

void Key1Interrupt()
{
  digitalWrite(SignalPin, !digitalRead(SignalPin));
  xTaskNotify(xOLEDTask, 18, eSetValueWithOverwrite);
}

void Key2Interrupt()
{
  digitalWrite(SignalPin, !digitalRead(SignalPin));
  WS2812Enable = !WS2812Enable;
}

void setup()
{
  Serial.begin(115200);
  pinMode(SignalPin, OUTPUT);

  attachInterrupt(Key1, Key1Interrupt, RISING);
  attachInterrupt(Key2, Key2Interrupt, RISING);

  xTaskCreatePinnedToCore(udp_control, "udp_control", 2048, NULL, 2, NULL, 0);
  xTaskCreate(motion_task, "motion_task", 2048, NULL, 2, &xMotionTask);
  xTaskCreate(oled_task, "oled_task", 2048, NULL, 2, &xOLEDTask);
  xTaskCreate(ws2812_task, "ws2812_task", 2028, NULL, 2, &xWS2812Task);
}

void loop()
{
  vTaskDelete(NULL);
}
