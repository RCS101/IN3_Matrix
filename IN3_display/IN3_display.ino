#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define SET 0xFFF
#define RESET 0

// declare PWM driver objects.
Adafruit_PWMServoDriver row[8] =
{
  Adafruit_PWMServoDriver(0x40),
  Adafruit_PWMServoDriver(0x60),
  Adafruit_PWMServoDriver(0x50),
  Adafruit_PWMServoDriver(0x48),
  Adafruit_PWMServoDriver(0x44)
};

#define OE A0 // This enables/disables all drivers. Set high to turn PWM off

int i, j;

void setup()
{
  Wire.setClock(400000);
  pinMode(OE, OUTPUT);
  digitalWrite(OE, LOW);

  for (i = 0; i < 8; i++)
  {
    row[i].begin();
    row[i].setPWMFreq(1000);
  }
}

void loop()
{
  for (i =0; i < 5; i++)
  {
    for (j = 0; j < 16; j++)
    {
      write_pixel(i, j, SET);
       delay(5);
    }
  }
  for (i = 0; i < 5; i++)
  {
    for (j = 0; j < 16; j++)
    {
      write_pixel(i, j, RESET);
       delay(  5);
    }
  }
}

/***************************
 * Name: write_pixel
 * Description: Writes any pixel to brightness. Write SET to max and RESET to off
 * ************************/
void write_pixel(int row_no, int column, int brightness)
{
  row[row_no].setPWM(column, 0, brightness);
}


