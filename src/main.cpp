#include <Arduino.h>
#include <BluetoothSerial.h>
#include <WiFi.h>
#include "motion.h"
#include "cconfig.h"

IPAddress remote_IP(192, 168, 31, 199);
uint32_t remoteUdpPort = 8080;

BluetoothSerial SerialBT;
WiFiUDP udp;
Motion motion;

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
    }
    vTaskDelay(1);
  }
}

void bluetooth_control(void *param)
{
  SerialBT.begin("ESP32-FFR");
  for (;;)
  {
    if (SerialBT.available())
    {
      String recvStr = SerialBT.readString();
      Serial.print("BT Received:");
      Serial.println(recvStr);
      int cmdNum = recvStr.toInt();
      motion.controlNumber(cmdNum);
    }
    vTaskDelay(1);
  }
}

void setup()
{
  Serial.begin(115200);
  motion.begin();
  // xTaskCreatePinnedToCore(udp_control, "udp_control", 2048, NULL, 2, NULL, 0);
  xTaskCreatePinnedToCore(bluetooth_control, "bluetooth_control", 2048, NULL, 2, NULL, 0);
}

void loop()
{
}
