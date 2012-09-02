#include <OneWire.h>

#ifndef DSTEMPERATURE_H
#define DSTEMPERATURE_H

#define FAHRENHEIT(x) (((float)x / 16.0) * 1.8 + 32.0)
#define CELSIUS(x) ((float)x / 16.0)

#define DS18S20 0x10
#define DS18B20 0x28
#define DS1822  0x22

class DSTemperature {

  private:
    OneWire* wire;

  public:
    DSTemperature(int pin);
    void begin(void);

};

#endif
