#ifndef HARDWARE_INTERFACE_H
#define HARDWARE_INTERFACE_H

#include "Hardware_Interface.h"
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>

struct IIC_OLED_91{
    uint8_t SDA;
    uint8_t SCL;
    uint8_t SCREEN_WIDTH;
    uint8_t SCREEN_HEIGHT;
    uint8_t OLED_RESET;
    uint8_t SCREEN_ADDRESS;
};

struct GPIO_Button{
    uint8_t PIN;
};

struct GPIO_PWM{
    uint8_t PIN;
};

class Hardware_Interface{

    public:
        struct GPIO_Button Button1 = {39};
        struct GPIO_Button Button2 = {36};
        struct GPIO_Button Button3 = {34};
        struct IIC_OLED_91 OLED = {21,22,128,32,-1,0x3C};
        struct GPIO_PWM PWM = {27};

        void init_hardware();
};


#endif
