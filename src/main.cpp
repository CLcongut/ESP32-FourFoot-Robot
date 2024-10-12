#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_PWMServoDriver.h>
#include <BluetoothSerial.h>

BluetoothSerial SerialBT;
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void sleep()
{
  pwm.setPWM(4, 0, 340);
  delay(100);
  pwm.setPWM(5, 0, 370);
  delay(100);
  pwm.setPWM(6, 0, 360);
  delay(100);
  pwm.setPWM(7, 0, 410);
  delay(100);
  pwm.setPWM(0, 0, 370);
  delay(100);
  pwm.setPWM(1, 0, 190);
  delay(100);
  pwm.setPWM(2, 0, 180);
  delay(100);
  pwm.setPWM(3, 0, 390);
}

void normal()
{
  pwm.setPWM(0, 0, 280);
  delay(100);
  pwm.setPWM(1, 0, 280);
  delay(100);
  pwm.setPWM(2, 0, 270);
  delay(100);
  pwm.setPWM(3, 0, 300);
  delay(100);
  pwm.setPWM(4, 0, 600);
  delay(100);
  pwm.setPWM(5, 0, 120);
  delay(100);
  pwm.setPWM(6, 0, 620);
  delay(100);
  pwm.setPWM(7, 0, 160);
}

void left()
{
  pwm.setPWM(4, 0, 450);
  pwm.setPWM(7, 0, 260);
  delay(100);
  pwm.setPWM(0, 0, 370);
  pwm.setPWM(3, 0, 390);
  delay(100);
  pwm.setPWM(4, 0, 600);
  pwm.setPWM(7, 0, 160);
  delay(100);
  pwm.setPWM(6, 0, 460);
  pwm.setPWM(5, 0, 280);
  delay(100);
  pwm.setPWM(2, 0, 450);
  pwm.setPWM(1, 0, 460);
  delay(100);
  pwm.setPWM(6, 0, 620);
  pwm.setPWM(5, 0, 120);
  delay(100);
  pwm.setPWM(0, 0, 280);
  pwm.setPWM(1, 0, 280);
  pwm.setPWM(2, 0, 270);
  pwm.setPWM(3, 0, 300);
  delay(100);
}

void right()
{
  pwm.setPWM(5, 0, 280);
  pwm.setPWM(6, 0, 490);
  delay(100);
  pwm.setPWM(1, 0, 190);
  pwm.setPWM(2, 0, 180);
  delay(100);
  pwm.setPWM(5, 0, 120);
  pwm.setPWM(6, 0, 620);
  delay(100);
  pwm.setPWM(7, 0, 260);
  pwm.setPWM(4, 0, 450);
  delay(100);
  pwm.setPWM(3, 0, 210);
  pwm.setPWM(0, 0, 190);
  delay(100);
  pwm.setPWM(7, 0, 160);
  pwm.setPWM(4, 0, 600);
  delay(100);
  pwm.setPWM(0, 0, 280);
  pwm.setPWM(1, 0, 280);
  pwm.setPWM(2, 0, 270);
  pwm.setPWM(3, 0, 300);
  delay(100);
}

void forward()
{
  pwm.setPWM(7, 0, 260);
  pwm.setPWM(4, 0, 450);
  delay(50);
  pwm.setPWM(3, 0, 390);
  pwm.setPWM(0, 0, 170);
  delay(100);
  pwm.setPWM(7, 0, 160);
  pwm.setPWM(4, 0, 600);
  delay(100);
  pwm.setPWM(0, 0, 280);
  pwm.setPWM(3, 0, 300);
  pwm.setPWM(6, 0, 490);
  pwm.setPWM(5, 0, 280);
  delay(50);
  pwm.setPWM(2, 0, 180);
  pwm.setPWM(1, 0, 400);
  delay(100);
  pwm.setPWM(6, 0, 620);
  pwm.setPWM(5, 0, 120);
  delay(100);
  pwm.setPWM(1, 0, 280);
  pwm.setPWM(2, 0, 270);
}

void backward()
{
  pwm.setPWM(5, 0, 280);
  pwm.setPWM(6, 0, 490);
  delay(50);
  pwm.setPWM(1, 0, 190);
  pwm.setPWM(2, 0, 450);
  delay(100);
  pwm.setPWM(5, 0, 120);
  pwm.setPWM(6, 0, 620);
  delay(100);
  pwm.setPWM(1, 0, 280);
  pwm.setPWM(2, 0, 270);
  pwm.setPWM(4, 0, 450);
  pwm.setPWM(7, 0, 260);
  delay(50);
  pwm.setPWM(0, 0, 370);
  pwm.setPWM(3, 0, 140);
  delay(100);
  pwm.setPWM(4, 0, 600);
  pwm.setPWM(7, 0, 160);
  delay(100);
  pwm.setPWM(0, 0, 280);
  pwm.setPWM(3, 0, 300);
}

void hello()
{
  pwm.setPWM(7, 0, 360);
  delay(100);
  pwm.setPWM(0, 0, 370);
  delay(200);
  pwm.setPWM(4, 0, 110);
  delay(300);
  pwm.setPWM(4, 0, 340);
  delay(300);
  pwm.setPWM(4, 0, 110);
  delay(300);
  pwm.setPWM(4, 0, 340);
  delay(300);
  pwm.setPWM(4, 0, 110);
  delay(300);
  pwm.setPWM(4, 0, 340);
  delay(500);
  pwm.setPWM(0, 0, 280);
  pwm.setPWM(4, 0, 600);
  pwm.setPWM(7, 0, 160);
  // u8g2.clearBuffer();
  // u8g2.drawXBMP(2, 2, 128, 64, zhengchang);
  // u8g2.sendBuffer();
  // Serial.println(end - start);
  delay(20);
}

void come()
{
  pwm.setPWM(7, 0, 360);
  delay(500);
  pwm.setPWM(0, 0, 120);
  pwm.setPWM(4, 0, 280);
  delay(500);
  pwm.setPWM(4, 0, 110);
  delay(200);
  pwm.setPWM(4, 0, 340);
  delay(400);
  pwm.setPWM(4, 0, 110);
  delay(200);
  pwm.setPWM(4, 0, 340);
  delay(400);
  pwm.setPWM(0, 0, 280);
  pwm.setPWM(4, 0, 600);
  pwm.setPWM(7, 0, 160);
  // u8g2.clearBuffer();
  // u8g2.drawXBMP(2, 2, 128, 64, zhengchang);
  // u8g2.sendBuffer();
  // Serial.println(end - start);
  delay(20);
}

void dog()
{
  delay(300);
  pwm.setPWM(0, 0, 120);
  pwm.setPWM(1, 0, 460);
  pwm.setPWM(2, 0, 450);
  pwm.setPWM(3, 0, 140);
  delay(300);
  pwm.setPWM(0, 0, 370);
  pwm.setPWM(1, 0, 190);
  pwm.setPWM(2, 0, 180);
  pwm.setPWM(3, 0, 390);
}

void middle()
{
  pwm.setPWM(7, 0, 360);
  delay(100);
  pwm.setPWM(0, 0, 120);
  delay(100);
  pwm.setPWM(4, 0, 110);
}

void surrender()
{
  delay(100);
  pwm.setPWM(4, 0, 110);
  pwm.setPWM(5, 0, 590);
  pwm.setPWM(6, 0, 110);
  pwm.setPWM(7, 0, 640);
}

void swing()
{
  delay(50);
  pwm.setPWM(4, 0, 450);
  pwm.setPWM(7, 0, 260);
  delay(50);
  pwm.setPWM(0, 0, 370);
  pwm.setPWM(3, 0, 390);
  delay(50);
  pwm.setPWM(4, 0, 600);
  pwm.setPWM(7, 0, 160);
  delay(50);
  pwm.setPWM(5, 0, 280);
  pwm.setPWM(6, 0, 490);
  delay(50);
  pwm.setPWM(1, 0, 190);
  pwm.setPWM(2, 0, 180);
  delay(50);
  pwm.setPWM(5, 0, 120);
  pwm.setPWM(6, 0, 620);
  delay(500);
  pwm.setPWM(4, 0, 450);
  pwm.setPWM(5, 0, 120);
  pwm.setPWM(6, 0, 470);
  pwm.setPWM(7, 0, 160);
  delay(400);
  pwm.setPWM(4, 0, 600);
  pwm.setPWM(5, 0, 270);
  pwm.setPWM(6, 0, 620);
  pwm.setPWM(7, 0, 310);
  delay(400);
  pwm.setPWM(4, 0, 450);
  pwm.setPWM(5, 0, 120);
  pwm.setPWM(6, 0, 470);
  pwm.setPWM(7, 0, 160);
  delay(400);
  pwm.setPWM(4, 0, 600);
  pwm.setPWM(5, 0, 270);
  pwm.setPWM(6, 0, 620);
  pwm.setPWM(7, 0, 310);
  delay(400);
  pwm.setPWM(4, 0, 450);
  pwm.setPWM(5, 0, 120);
  pwm.setPWM(6, 0, 470);
  pwm.setPWM(7, 0, 160);
  delay(400);
  pwm.setPWM(4, 0, 600);
  pwm.setPWM(5, 0, 270);
  pwm.setPWM(6, 0, 620);
  pwm.setPWM(7, 0, 310);
  delay(400);
  pwm.setPWM(4, 0, 450);
  pwm.setPWM(5, 0, 120);
  pwm.setPWM(6, 0, 470);
  pwm.setPWM(7, 0, 160);
  delay(400);
  pwm.setPWM(4, 0, 600);
  pwm.setPWM(5, 0, 270);
  pwm.setPWM(6, 0, 620);
  pwm.setPWM(7, 0, 310);
  delay(400);
  pwm.setPWM(4, 0, 450);
  pwm.setPWM(5, 0, 120);
  pwm.setPWM(6, 0, 470);
  pwm.setPWM(7, 0, 160);
  delay(400);
  pwm.setPWM(4, 0, 600);
  pwm.setPWM(5, 0, 270);
  pwm.setPWM(6, 0, 620);
  pwm.setPWM(7, 0, 310);
  delay(400);
}

void lie()
{
  pwm.setPWM(4, 0, 340);
  delay(100);
  pwm.setPWM(5, 0, 370);
  delay(100);
  pwm.setPWM(6, 0, 360);
  delay(100);
  pwm.setPWM(7, 0, 410);
  delay(100);
  pwm.setPWM(0, 0, 120);
  pwm.setPWM(1, 0, 460);
  pwm.setPWM(2, 0, 450);
  pwm.setPWM(3, 0, 140);
}

void fan()
{
  delay(500);
  pwm.setPWM(4, 0, 110);
  pwm.setPWM(5, 0, 590);
  delay(500);
  pwm.setPWM(4, 0, 310);
  pwm.setPWM(5, 0, 340);
}

uint8_t i;
char temp;

void read_usart()
{
  i = Serial.available(); // 返回目前串口接收区内的已经接受的数据量
  if (i != 0)
  {
    while (i--)
    {
      temp = Serial.read(); // 读取一个数据并且将它从缓存区删除
    }
    Serial.println("");
    // data_analyse();    //至关重要的一步，也就是把读取回来的数据进行分步截取直接拿到我们想要的数据，我下一篇博文会讲如何自己写这个函数
  }
}

void read_bluetooth()
{
  if (SerialBT.available()) // 判断蓝牙串口是否收到数据
  {
    char res = SerialBT.read(); // 将收到的数据读取出来，下面分别处理
    temp = res;
    // Serial.println(res);
  }
  delay(10);
}

void setup()
{
  Serial.begin(115200);
  SerialBT.begin();
  pwm.begin();
  pwm.setPWMFreq(60);
}

void loop()
{
  read_bluetooth();
  read_usart();
  switch (temp)
  {
  case '0':
    sleep();
    break;

  case '1':
    forward();
    break;

  case '2':
    backward();
    break;

  case '3':
    left();
    break;

  case '4':
    right();
    break;

  case '5':
    break;

  case '6':
    break;

  case '7':
    break;

  case '8':
    break;

  case '9':
    break;
  }
}
