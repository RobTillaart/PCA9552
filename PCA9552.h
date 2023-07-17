#pragma once
//
//    FILE: PCA9552.h
//  AUTHOR: Rob Tillaart
//    DATE: 2023-07-17
// VERSION: 0.1.0
// PUPROSE: Arduino library for for I2C PCA9552 16 channel PWM
//     URL: https://github.com/RobTillaart/PCA9552


#include "Arduino.h"
#include "Wire.h"


#define PCA9552_LIB_VERSION         (F("0.1.0"))


//  REGISTERS
#define PCA9552_INPUT0      0x00
#define PCA9552_INPUT1      0x01
#define PCA9552_PSC0        0x02
#define PCA9552_PWM0        0x03
#define PCA9552_PSC1        0x04
#define PCA9552_PWM1        0x05
#define PCA9552_LS0         0x06
#define PCA9552_LS1         0x07
#define PCA9552_LS2         0x08
#define PCA9552_LS3         0x09


//  LED SOURCE MASKS
//  TODO


//  ERROR CODES (not all used yet)
#define PCA9552_OK          0x00
#define PCA9552_ERROR       0xFF
#define PCA9552_ERR_WRITE   0xFE
#define PCA9552_ERR_CHAN    0xFD
#define PCA9552_ERR_MODE    0xFC
#define PCA9552_ERR_REG     0xFB
#define PCA9552_ERR_I2C     0xFA


/////////////////////////////////////////////////////
//
//  CLASS
//
class PCA9552
{
public:
  explicit PCA9552(const uint8_t deviceAddress, TwoWire *wire = &Wire);

#if defined (ESP8266) || defined(ESP32)
  bool     begin(int sda, int scl);
#endif
  bool     begin();
  bool     isConnected();

  uint8_t  getAddress();
  uint8_t  channelCount();

  //  GPIO
  uint16_t getInput();
  void     digitalWrite(uint8_t led, uint8_t val);
  uint8_t  digitalRead(uint8_t led);

  //  PRESCALERS
  void     setPrescaler(uint8_t gen, uint8_t psc = 255);
  uint8_t  getPrescaler(uint8_t gen);

  //  PWM
  void     setPWM(uint8_t gen, uint8_t pwm = 128);
  uint8_t  getPWM(uint8_t gen);


  //  LED SOURCE SELECTOR
  //  led = 0..15

  //  source:
  //    00 = output is set LOW (LED on)
  //    01 = output is set high-impedance (LED off; default)
  //    10 = output blinks at PWM0 rate
  //    11 = output blinks at PWM1 rate
  bool     setLEDSource(uint8_t led, uint8_t source);
  uint8_t  getLEDSource(uint8_t led);


private:
  uint8_t  writeReg(uint8_t reg, uint8_t value);
  uint8_t  readReg(uint8_t reg);

  uint8_t  _address;
  uint8_t  _channelCount;
  uint8_t  _error;

  TwoWire* _wire;
};


//  -- END OF FILE --

