#include <Wire.h>
//#include <Adafruit_PWMServoDriver.h>
#include "PCA9685.h"

PCA9685 pwmController;

int address[8] = {0x40, 0x60, 0x50, 0x48, 0x44, 0x42, 0x41, 0x43};

#define OE A0 // This enables/disables all drivers. Set high to turn PWM off

int i, j;

void setup()
{
  pinMode(OE, OUTPUT);
  digitalWrite(OE, LOW);

  Wire.begin();
  Wire.setClock(400000); // Apparently can go up to 1MHz, though it wont go above 400k. Don't know if that is a limit of the 328 peripheral
}

void loop()
{
  int pixel_delay_time = 1;
  const uint16_t SET[16] = {0xfff,  0xfff, 0xfff, 0xfff, 0xfff, 0xfff, 0xfff, 0xfff, 0xfff,0xfff, 0xfff, 0xfff,0xfff,0xfff,0xfff,0xfff};
  const uint16_t RESET[16] = {0x0,0x0, 0x0, 0x0,0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
  
  for (i = 0; i < 8; i++)
  {
    pwmController.init(address[i]);
    pwmController.setPWMFrequency(1000);
    pwmController.setChannelsPWM(0, 16, SET);
  }
  delay(2000);
  for (i = 0; i < 8; i++)
  {
    pwmController.init(address[i]);
    pwmController.setPWMFrequency(1000);
    pwmController.setChannelsPWM(0, 16, RESET);
  }
  delay(2000);
}



