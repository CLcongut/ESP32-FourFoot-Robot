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
    void fan();       // number 3
    void forward();   // number 4
    void hello();     // number 5
    void left();      // number 6
    void lie();       // number 7
    void middle();    // number 8
    void normal();    // number 9
    void right();     // number 10
    void stand();     // number 11
    void sleep1();     // number 12
    void sleep2();     // number 13
    void surrender(); // number 14
    // void swing1();
    /*control command*/
    void controlNumber(int number);
    void ctlSingleServo(int servo, int angleStart, int angleEnd);
    void setFrequency(float frequency);
};
