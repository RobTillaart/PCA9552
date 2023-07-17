//
//    FILE: PCA9552.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2023-07-17
// VERSION: 0.1.0
// PURPOSE: Arduino library for for I2C PCA9552 16 channel PWM
//     URL: https://github.com/RobTillaart/PCA9552


#include "PCA9552.h"


//////////////////////////////////////////////////////////////
//
//  Constructor
//
PCA9552::PCA9552(const uint8_t deviceAddress, TwoWire *wire)
{
  _address = deviceAddress;
  _wire    = wire;
  _channelCount = 16;
}


#if defined (ESP8266) || defined(ESP32)
bool PCA9552::begin(int sda, int scl)
{
  _wire = &Wire;
  if ((sda < 255) && (scl < 255))
  {
    _wire->begin(sda, scl);
  } else {
    _wire->begin();
  }
  if (! isConnected()) return false;
  return true;
}
#endif


bool PCA9552::begin()
{
  _wire->begin();
  if (! isConnected()) return false;
  return true;
}


bool PCA9552::isConnected()
{
  _wire->beginTransmission(_address);
  _error = _wire->endTransmission();
  return (_error == 0);
}


uint8_t PCA9552::getAddress()
{
  return _address;
}


uint8_t PCA9552::channelCount()
{
  return _channelCount;
}


/////////////////////////////////////////////////////
//
//  GPIO
//
uint8_t PCA9552::getInput()
{
  return readReg(PCA9552_INPUT);
}


void PCA9552::digitalWrite(uint8_t led, uint8_t val)
{
  if (val == LOW) setLEDSource(led, 0);
  else            setLEDSource(led, 1);
}


uint8_t PCA9552::digitalRead(uint8_t led)
{
  uint8_t val = readReg(PCA9552_INPUT);
  if ((val >> led) & 0x01) return HIGH;
  return LOW;
}


/////////////////////////////////////////////////////
//
//  PRESCALERS
//
void PCA9552::setPrescaler(uint8_t gen, uint8_t psc)
{
  if (gen == 0) writeReg(PCA9552_PSC0, psc);
  else          writeReg(PCA9552_PSC1, psc);
}


uint8_t PCA9552::getPrescaler(uint8_t gen)
{
  if (gen == 0) return readReg(PCA9552_PSC0);
  else          return readReg(PCA9552_PSC1);
}


/////////////////////////////////////////////////////
//
//  PWM
//
void PCA9552::setPWM(uint8_t gen, uint8_t pwm)
{
  if (gen == 0) writeReg(PCA9552_PWM0, pwm);
  else          writeReg(PCA9552_PWM1, pwm);
}


uint8_t PCA9552::getPWM(uint8_t gen)
{
  if (gen == 0) return readReg(PCA9552_PWM0);
  else          return readReg(PCA9552_PWM1);
}


/////////////////////////////////////////////////////
//
//  LED SOURCE SELECTOR
//
bool PCA9552::setLEDSource(uint8_t led, uint8_t source)
{
  if (led >= _channelCount) return false;
  if (source > 3) return false;

  uint8_t ledSelect = readReg(PCA9552_LS0);
  ledSelect &= ~(0x03 << (led * 2));
  ledSelect |= (source << (led * 2));

  writeReg(PCA9552_LS0, ledSelect);
  return true;
}


uint8_t PCA9552::getLEDSource(uint8_t led)
{
  if (led >= _channelCount) return PCA9552_ERROR;

  uint8_t ledSelect = readReg(PCA9552_LS0);
  uint8_t source = (ledSelect >> (led * 2)) & 0x03;
  return source;
}


/////////////////////////////////////////////////////
//
//  PRIVATE
//
uint8_t PCA9552::writeReg(uint8_t reg, uint8_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(value);
  _error = _wire->endTransmission();

  if (_error == 0) _error = PCA9552_OK;
  else _error = PCA9552_ERROR;
  return _error;
}


uint8_t PCA9552::readReg(uint8_t reg)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _error = _wire->endTransmission();

  if (_wire->requestFrom(_address, (uint8_t)1) != 1)
  {
    _error = PCA9552_ERROR;
    return 0;
  }
  _error = PCA9552_OK;
  return _wire->read();
}


//  -- END OF FILE --

