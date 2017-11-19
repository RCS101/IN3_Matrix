#include <Wire.h>
//#include <Adafruit_PWMServoDriver.h>
#include "PCA9685.h"
#define SET 0xFFF
#define RESET 0

PCA9685 row[8] =
{
  pwmController1,
  pwmController2,
  pwmController3,
  pwmController4,
  pwmController5,
  pwmController6,
  pwmController7,
  pwmController8
};


// declare PWM driver objects.
//Adafruit_PWMServoDriver row[8] =
//{
//  Adafruit_PWMServoDriver(0x40),
//  Adafruit_PWMServoDriver(0x60),
//  Adafruit_PWMServoDriver(0x50),
//  Adafruit_PWMServoDriver(0x48),
//  Adafruit_PWMServoDriver(0x44),
//  Adafruit_PWMServoDriver(0x42),
//  Adafruit_PWMServoDriver(0x41),
//  Adafruit_PWMServoDriver(0x43)
//};

#define OE A0 // This enables/disables all drivers. Set high to turn PWM off

int i, j;

void setup()
{
  pinMode(OE, OUTPUT);
  digitalWrite(OE, LOW);

  Wire.begin();
  Wire.setClock(400000L); // 400kHz my arse. More like 280kHz

  for(int i=0;i<8;i++)
  {
    row[i].resetDevices();
  }
  
  row[0].init(0x40);
  row[0].setPWMFrequency(1000);
  row[1].init(0x60);
  row[1].setPWMFrequency(1000);
  row[2].init(0x50);
  row[2].setPWMFrequency(1000);
  row[3].init(0x48);
  row[3].setPWMFrequency(1000);
  row[4].init(0x44);
  row[4].setPWMFrequency(1000);
  row[5].init(0x42);
  row[5].setPWMFrequency(1000);
  row[6].init(0x41);
  row[6].setPWMFrequency(1000);
  row[7].init(0x43);
  row[7].setPWMFrequency(1000);

}

void loop()
{
  int pixel_delay_time = 1;

  for (i = 0; i < 8; i++)
  {
    row[i].setChannelsPWM(0,16,4096);
  }
  delay(2000);
  for (i = 0; i < 8; i++)
  {
    row[i].setChannelsPWM(0,16,0);
  }
  delay(2000);
}

/***************************
 * Name: write_pixel
 * Description: Writes any pixel to brightness. Write SET to max and RESET to off
 * ************************/
void write_pixel(int row_no, int column, int brightness)
{
  row[row_no].setPWM(column, 0, brightness);
}


