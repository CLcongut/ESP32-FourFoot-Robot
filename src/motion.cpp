#include "Motion.h"

Motion::Motion()
{
}

Motion::~Motion()
{
}

bool Motion::begin()
{
    Wire1.setPins(17, 16);
    bool ret;
    ret = pwm.begin();
    pwm.setPWMFreq(60);
    return ret;
}

void Motion::backward()
{
    pwm.setPWM(RUFOOT, 0, 280);
    pwm.setPWM(RDFOOT, 0, 490);
    vTaskDelay(50);
    pwm.setPWM(RULEG, 0, 190);
    pwm.setPWM(LDLEG, 0, 450);
    vTaskDelay(100);
    pwm.setPWM(RUFOOT, 0, 140);
    pwm.setPWM(RDFOOT, 0, 600);
    vTaskDelay(100);
    pwm.setPWM(RULEG, 0, 300);
    pwm.setPWM(LDLEG, 0, 300);
    pwm.setPWM(LUFOOT, 0, 450);
    pwm.setPWM(LDFOOT, 0, 260);
    vTaskDelay(50);
    pwm.setPWM(LULEG, 0, 370);
    pwm.setPWM(RDLEG, 0, 140);
    vTaskDelay(100);
    pwm.setPWM(LUFOOT, 0, 600);
    pwm.setPWM(LDFOOT, 0, 140);
    vTaskDelay(100);
    pwm.setPWM(LULEG, 0, 250);
    pwm.setPWM(RDLEG, 0, 250);
}
// done
void Motion::come()
{
    pwm.setPWM(RDFOOT, 0, 460);
    vTaskDelay(500);
    pwm.setPWM(LULEG, 0, 120);
    pwm.setPWM(LUFOOT, 0, 280);
    vTaskDelay(500);
    pwm.setPWM(LUFOOT, 0, 110);
    vTaskDelay(200);
    pwm.setPWM(LUFOOT, 0, 340);
    vTaskDelay(400);
    pwm.setPWM(LUFOOT, 0, 110);
    vTaskDelay(200);
    pwm.setPWM(LUFOOT, 0, 340);
    vTaskDelay(400);
    pwm.setPWM(LULEG, 0, 250);
    pwm.setPWM(LUFOOT, 0, 600);
    pwm.setPWM(RDFOOT, 0, 600);
    // u8g2.clearBuffer();
    // u8g2.drawXBMP(2, 2, 128, 64, zhengchang);
    // u8g2.sendBuffer();
    // Serial.println(end - start);
    vTaskDelay(20);
}
// done
void Motion::dog()
{
    vTaskDelay(300);
    pwm.setPWM(LULEG, 0, 130);
    pwm.setPWM(RULEG, 0, 450);
    pwm.setPWM(LDLEG, 0, 430);
    pwm.setPWM(RDLEG, 0, 150);
    vTaskDelay(300);
    pwm.setPWM(LULEG, 0, 360);
    pwm.setPWM(RULEG, 0, 190);
    pwm.setPWM(LDLEG, 0, 180);
    pwm.setPWM(RDLEG, 0, 370);
}
// done
void Motion::fan()
{
    vTaskDelay(500);
    pwm.setPWM(LUFOOT, 0, 110);
    pwm.setPWM(RUFOOT, 0, 640);
    vTaskDelay(500);
    pwm.setPWM(LUFOOT, 0, 360);
    pwm.setPWM(RUFOOT, 0, 380);
}

void Motion::forward()
{
    pwm.setPWM(LDFOOT, 0, 260);
    pwm.setPWM(LUFOOT, 0, 450);
    vTaskDelay(50);
    pwm.setPWM(RDLEG, 0, 390);
    pwm.setPWM(LULEG, 0, 170);
    vTaskDelay(100);
    pwm.setPWM(LDFOOT, 0, 140);
    pwm.setPWM(LUFOOT, 0, 600);
    vTaskDelay(100);
    pwm.setPWM(LULEG, 0, 250);
    pwm.setPWM(RDLEG, 0, 250);
    pwm.setPWM(RDFOOT, 0, 490);
    pwm.setPWM(RUFOOT, 0, 280);
    vTaskDelay(50);
    pwm.setPWM(LDLEG, 0, 180);
    pwm.setPWM(RULEG, 0, 400);
    vTaskDelay(100);
    pwm.setPWM(RDFOOT, 0, 600);
    pwm.setPWM(RUFOOT, 0, 140);
    vTaskDelay(100);
    pwm.setPWM(RULEG, 0, 300);
    pwm.setPWM(LDLEG, 0, 300);
}
// done
void Motion::hello()
{
    pwm.setPWM(RDFOOT, 0, 460);
    vTaskDelay(100);
    pwm.setPWM(LULEG, 0, 370);
    vTaskDelay(200);
    pwm.setPWM(LUFOOT, 0, 110);
    vTaskDelay(300);
    pwm.setPWM(LUFOOT, 0, 340);
    vTaskDelay(300);
    pwm.setPWM(LUFOOT, 0, 110);
    vTaskDelay(300);
    pwm.setPWM(LUFOOT, 0, 340);
    vTaskDelay(300);
    pwm.setPWM(LUFOOT, 0, 110);
    vTaskDelay(300);
    pwm.setPWM(LUFOOT, 0, 340);
    vTaskDelay(500);
    pwm.setPWM(LULEG, 0, 250);
    pwm.setPWM(LUFOOT, 0, 600);
    pwm.setPWM(RDFOOT, 0, 600);
    // u8g2.clearBuffer();
    // u8g2.drawXBMP(2, 2, 128, 64, zhengchang);
    // u8g2.sendBuffer();
    // Serial.println(end - start);
    vTaskDelay(20);
}

void Motion::left()
{
    pwm.setPWM(LUFOOT, 0, 450);
    pwm.setPWM(LDFOOT, 0, 260);
    vTaskDelay(100);
    pwm.setPWM(LULEG, 0, 370);
    pwm.setPWM(RDLEG, 0, 390);
    vTaskDelay(100);
    pwm.setPWM(LUFOOT, 0, 600);
    pwm.setPWM(LDFOOT, 0, 140);
    vTaskDelay(100);
    pwm.setPWM(RDFOOT, 0, 460);
    pwm.setPWM(RUFOOT, 0, 280);
    vTaskDelay(100);
    pwm.setPWM(LDLEG, 0, 450);
    pwm.setPWM(RULEG, 0, 460);
    vTaskDelay(100);
    pwm.setPWM(RDFOOT, 0, 600);
    pwm.setPWM(RUFOOT, 0, 140);
    vTaskDelay(100);
    pwm.setPWM(LULEG, 0, 250);
    pwm.setPWM(RULEG, 0, 300);
    pwm.setPWM(LDLEG, 0, 300);
    pwm.setPWM(RDLEG, 0, 250);
    vTaskDelay(100);
}
// done
void Motion::lie()
{
    pwm.setPWM(LUFOOT, 0, 360);
    vTaskDelay(100);
    pwm.setPWM(RUFOOT, 0, 380);
    vTaskDelay(100);
    pwm.setPWM(RDFOOT, 0, 320);
    vTaskDelay(100);
    pwm.setPWM(LDFOOT, 0, 400);
    vTaskDelay(100);
    pwm.setPWM(LULEG, 0, 130);
    pwm.setPWM(RULEG, 0, 450);
    pwm.setPWM(LDLEG, 0, 430);
    pwm.setPWM(RDLEG, 0, 150);
}
// done
void Motion::middle()
{
    pwm.setPWM(LULEG, 0, 130);
    vTaskDelay(100);
    pwm.setPWM(LUFOOT, 0, 110);
}
// done
void Motion::normal()
{
    pwm.setPWM(LULEG, 0, 250);
    vTaskDelay(100);
    pwm.setPWM(RULEG, 0, 300);
    vTaskDelay(100);
    pwm.setPWM(LDLEG, 0, 300);
    vTaskDelay(100);
    pwm.setPWM(RDLEG, 0, 250);
    vTaskDelay(100);
    pwm.setPWM(LUFOOT, 0, 600);
    vTaskDelay(100);
    pwm.setPWM(RUFOOT, 0, 140);
    vTaskDelay(100);
    pwm.setPWM(RDFOOT, 0, 600);
    vTaskDelay(100);
    pwm.setPWM(LDFOOT, 0, 140);
}

void Motion::right()
{
    pwm.setPWM(RUFOOT, 0, 280);
    pwm.setPWM(RDFOOT, 0, 490);
    vTaskDelay(100);
    pwm.setPWM(RULEG, 0, 190);
    pwm.setPWM(LDLEG, 0, 180);
    vTaskDelay(100);
    pwm.setPWM(RUFOOT, 0, 140);
    pwm.setPWM(RDFOOT, 0, 600);
    vTaskDelay(100);
    pwm.setPWM(LDFOOT, 0, 260);
    pwm.setPWM(LUFOOT, 0, 450);
    vTaskDelay(100);
    pwm.setPWM(RDLEG, 0, 210);
    pwm.setPWM(LULEG, 0, 190);
    vTaskDelay(100);
    pwm.setPWM(LDFOOT, 0, 140);
    pwm.setPWM(LUFOOT, 0, 600);
    vTaskDelay(100);
    pwm.setPWM(LULEG, 0, 250);
    pwm.setPWM(RULEG, 0, 300);
    pwm.setPWM(LDLEG, 0, 300);
    pwm.setPWM(RDLEG, 0, 250);
    vTaskDelay(100);
}

void Motion::stand()
{
    pwm.setPWM(LULEG, 0, 250);
    pwm.setPWM(RULEG, 0, 300);
    pwm.setPWM(LDLEG, 0, 300);
    pwm.setPWM(RDLEG, 0, 250);
    pwm.setPWM(LUFOOT, 0, 600);
    pwm.setPWM(RUFOOT, 0, 140);
    pwm.setPWM(RDFOOT, 0, 600);
    pwm.setPWM(LDFOOT, 0, 140);
}
// done
void Motion::sleep1()
{
    pwm.setPWM(LUFOOT, 0, 360);
    vTaskDelay(100);
    pwm.setPWM(RUFOOT, 0, 380);
    vTaskDelay(100);
    pwm.setPWM(RDFOOT, 0, 320);
    vTaskDelay(100);
    pwm.setPWM(LDFOOT, 0, 400);
    vTaskDelay(100);
    pwm.setPWM(LULEG, 0, 360);
    vTaskDelay(100);
    pwm.setPWM(RULEG, 0, 190);
    vTaskDelay(100);
    pwm.setPWM(LDLEG, 0, 180);
    vTaskDelay(100);
    pwm.setPWM(RDLEG, 0, 370);
}

void Motion::sleep2()
{
    pwm.setPWM(LUFOOT, 0, 420);
    pwm.setPWM(RUFOOT, 0, 300);
    pwm.setPWM(RDFOOT, 0, 400);
    pwm.setPWM(LDFOOT, 0, 340);
    pwm.setPWM(LULEG, 0, 250);
    pwm.setPWM(RULEG, 0, 300);
    pwm.setPWM(LDLEG, 0, 300);
    pwm.setPWM(RDLEG, 0, 250);
}
// done
void Motion::surrender()
{
    vTaskDelay(100);
    pwm.setPWM(LUFOOT, 0, 110);
    pwm.setPWM(RUFOOT, 0, 640);
    pwm.setPWM(RDFOOT, 0, 110);
    pwm.setPWM(LDFOOT, 0, 660);
}

// 加一个左右摇摆

void Motion::controlNumber(int num)
{
    switch (num)
    {
    case 0:
        backward();
        break;
    case 1:
        come();
        break;
    case 2:
        dog();
        break;
    case 3:
        fan();
        break;
    case 4:
        forward();
        break;
    case 5:
        hello();
        break;
    case 6:
        left();
        break;
    case 7:
        lie();
        break;
    case 8:
        middle();
        break;
    case 9:
        normal();
        break;
    case 10:
        right();
        break;
    case 11:
        stand();
        break;
    case 12:
        sleep1();
        break;
    case 13:
        sleep2();
        break;
    case 14:
        surrender();
        break;
    default:
        break;
    }
}

void Motion::ctlSingleServo(int servo, int angleStart, int angleEnd)
{
    pwm.setPWM(servo, angleStart, angleEnd);
}

void Motion::setFrequency(float frequency)
{
    pwm.setPWMFreq(frequency);
}