#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_PWMServoDriver.h>

typedef enum ServoNumber
{
    LULEG,
    RULEG,
    RDLEG,
    LDLEG,
    LUFOOT,
    RUFOOT,
    RDFOOT,
    LDFOOT,
} servoMap;

class Motion
{
private:
    Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x47, Wire1);

public:
    Motion();
    ~Motion();
    bool begin();
    /*movment function*/
    void backward();  // number 0
    void come();      // number 1
    void dog();       // number 2
    void dance();     // number 3
    void fan();       // number 4
    void forward();   // number 5
    void hello();     // number 6
    void left();      // number 7
    void lie();       // number 8
    void middle();    // number 9
    void normal();    // number 10
    void right();     // number 11
    void stand();     // number 12
    void sleep1();     // number 13
    void sleep2();     // number 14
    void surrender(); // number 15
    /*control command*/
    void controlNumber(int number);
    void ctlSingleServo(int servo, int angleStart, int angleEnd);
    void setFrequency(float frequency);
};
