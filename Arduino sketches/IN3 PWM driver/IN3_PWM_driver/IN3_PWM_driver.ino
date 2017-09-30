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
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x60);
#define DEBUG
#define TWI_FREQ 400000L
uint8_t matrix[4][4] = {{3, 2, 1, 0}, {4, 5, 6, 7}, {11, 10, 9, 8}, {12, 13, 14, 15}};
uint16_t image[4][4];
float time_step[13] = {0., 0.479426, 0.841471, 0.997495, 0.909297, 0.598472, 0.14112, -0.350783, -0.756802, -0.97753, -0.958924, -0.70554, -0.279415};
int t = 0;

void setup()
{
  pinMode(A0, OUTPUT);
  digitalWrite(A0, LOW);
  
#ifdef DEBUG
  Serial.begin(9600);
  Serial.println("16 channel PWM test!");
#endif

  pwm.begin();
  pwm.setPWMFreq(500);  // This is the maximum PWM frequency
}

void loop()
{
  int8_t i, j; 
  
  
  for(i=0;i<4;i++)
  {
    for(j=0;j<4;j++)
    {
      image[i][j] = parabol(i,j,time_step[t]);
    }
  } 
  
  write_matrix();
  t++;
  if(t==13)
  {
    t = 0;
  }
  

}

void write_matrix(void)
{
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      pwm.setPWM(matrix[i][j],0, image[i][j]);
    }
  }
}

uint16_t parabol(int8_t x, int8_t y, float time)
{
  float brightness = 0;
  brightness = float(((x-1.5)*(x-1.5))+((y-1.5)*(y-1.5)))*time;
  brightness = map(brightness,-5,5,0,4000);
  delay(1);
  return int(brightness);  
}

