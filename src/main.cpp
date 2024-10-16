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
  xTaskNotify(xOLEDTask, 0x01, eSetBits);
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
    switch (ulOLEDValue)
    {
    case 0x01:
      display.showNetworkIP(WiFi.localIP());
      break;

    default:
      break;
    }
    vTaskDelay(1);
  }
}

void ws2812_task(void *param)
{
  FastLED.addLeds<WS2812B, 5, GRB>(leds, 2);
  for (;;)
  {
    // Turn the LED on, then pause
    leds[0] = CRGB::Blue;
    leds[1] = CRGB::Blue;
    FastLED.show();
    vTaskDelay(500);
    // Now turn the LED off, then pause
    leds[0] = CRGB::Black;
    leds[1] = CRGB::Black;
    FastLED.show();
    vTaskDelay(500);
  }
}

void Key1Interrupt()
{
  // display.test1();
  digitalWrite(SignalPin, !digitalRead(SignalPin));
}

void Key2Interrupt()
{
  // display.test2();
  digitalWrite(SignalPin, !digitalRead(SignalPin));
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
  xTaskCreate(ws2812_task, "ws2812_task", 1024, NULL, 2, &xWS2812Task);
}

void loop()
{
  vTaskDelete(NULL);
}
