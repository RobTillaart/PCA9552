//
//    FILE: PCA9552_test02.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2023-07-17
// PURPOSE: test PCA9552 library
//     URL: https://github.com/RobTillaart/PCA9552


#include "Arduino.h"
#include "Wire.h"
#include "PCA9552.h"


PCA9552 leds(0x62);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCA9551_LIB_VERSION: ");
  Serial.println(PCA9551_LIB_VERSION);
  Serial.println();

  Wire.begin();

  if (leds.begin() == false)
  {
    Serial.println("Could not connect.");
    while(1);
  }

}


void loop()
{
  //  random blink
  leds.digitalWrite(0, random(2));

  //  steady blink
  leds.digitalWrite(1, !leds.digitalRead(1));

  //  output 2 follows 3
  leds.digitalWrite(2, leds.digitalRead(3));
  leds.digitalWrite(3, random(2));
  delay(1000);
}


//  -- END OF FILE --
