//
//    FILE: PCA9552_test01.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2023-07-16
// PURPOSE: test PCA9552 library
//     URL: https://github.com/RobTillaart/PCA9552


#include "Arduino.h"
#include "Wire.h"
#include "PCA9552.h"


PCA9552 leds(0x62);


void setup()
{
  Serial.begin(115200);
  Serial.print("PCA9552_LIB_VERSION: ");
  Serial.println(PCA9552_LIB_VERSION);
  Serial.println();

  if (leds.begin() == false)
  {
    Serial.println("Could not connect.");
    while(1);
  }

  //  default
  leds.setPrescaler(0, 255);
  leds.setPWM(0, 128);

  //  different
  leds.setPrescaler(1, 113);
  leds.setPWM(1, 32);

  //  all channels a different source
  leds.setLEDSource(0, 0);
  leds.setLEDSource(1, 1);
  leds.setLEDSource(2, 2);
  leds.setLEDSource(3, 3);

  Serial.println("done...");
}


void loop()
{
}


//  -- END OF FILE --
