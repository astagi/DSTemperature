#include <OneWire.h>

#ifndef DSTEMPERATURE_H
#define DSTEMPERATURE_H

#define FAHRENHEIT(x) ((x / 16.0) * 1.8 + 32.0)
#define CELSIUS(x) (x / 16.0)

#define DS18S20 0x10
#define DS18B20 0x28
#define DS1822  0x22

#define ADDR_SIZE 8

typedef struct{
  byte value[ADDR_SIZE];
}DSAddress;

class DSTemperature {

  private:
    OneWire*   _wire;
    DSAddress* _addresses;
    byte       _nDevices;

    void resizeAddresses(void);
    float getRawTemperature(byte ds);

  public:
    DSTemperature(byte pin);
    void begin(void);
    float getCelsius(byte ds);
    float getFahrenheit(byte ds);
    byte getDeviceCount(void);
    DSAddress getAddressFromIndex(byte ds);
    byte getIndexFromAddress(DSAddress dsaddr){}
};

#endif
