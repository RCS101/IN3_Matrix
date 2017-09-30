/***************************************************
  This is an example for our Adafruit 16-channel PWM & Servo driver
  PWM test - this will drive 16 PWMs in a 'wave'

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/815

  These displays use I2C to communicate, 2 pins are required to
  interface. For Arduino UNOs, thats SCL -> Analog 5, SDA -> Analog 4

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want

Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x40);//0x60
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x60);

#define DEBUG
#define TWI_FREQ 400000
#define OE A0

void setup()
{
  pinMode(OE, OUTPUT);
  digitalWrite(OE, LOW);
  
  pwm1.begin();
  pwm2.begin();
  pwm1.setPWMFreq(1600);  // This is the maximum PWM frequency, 1.6kHz max
  pwm2.setPWMFreq(1600);
}

void loop()
{
  float time = 0;
  for(int j = 100; j < 4000; j+=20){
    for(int i = 0; i < 16; i++){
      pwm1.setPWM(i, 0, j);
      pwm2.setPWM(i, 0, j);
    }
  }
  for(int j = 4000; j > 100; j-=20){
    for(int i = 0; i < 16; i++){
      pwm1.setPWM(i, 0, j);
      pwm2.setPWM(i, 0, j);
    }
  }
}
