                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          #include <Wire.h>

#include <Adafruit_PWMServoDriver.h>


//#define DEBUG
//#define TWI_FREQ 400000 // set I2C clock to 400kHz

#define SET 4000
#define RESET 0


// declare PWM driver objects.
Adafruit_PWMServoDriver row[8] = 
{
  Adafruit_PWMServoDriver(0x40), 
  Adafruit_PWMServoDriver(0x60),
  Adafruit_PWMServoDriver(0x50),
  Adafruit_PWMServoDriver(0x48)
};




#define OE A0 // This enables/disables all drivers. Set high to turn PWM off
#define tau 10

int i, j;

void setup()
{
  pinMode(OE, OUTPUT);
  pinMode(12, OUTPUT);
  digitalWrite(OE, LOW);

  Wire.setClock(400000); // Set I2C clock to 400kHz. At default, 100kHz, clock it can refresh the display at about 12Hz. Therefore at 400kHz, should have a max refresh rate of about 50Hz.
  
  for(i=0;i<8;i++)
  {
    row[i].begin();
    row[i].setPWMFreq(1600);
  }
}

int bright = 500;

void loop()
{
  digitalWrite(12, LOW);
  for(i=0;i<4;i++)
  {
    for(j=0;j<16;j++)
    {
      write_pixel(i, j, SET);
    }
  }
  digitalWrite(12, HIGH);
}


/***************************
 * Name: write_pixel
 * Description: Writes any pixel to brightness. Write SET to max and RESET to off
 * ************************/
void write_pixel(int row_no, int column, int brightness)
{
  row[row_no].setPWM(column, 0, brightness);
}


