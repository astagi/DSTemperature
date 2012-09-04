#include "DSTemperature.h"

DSTemperature::DSTemperature(byte pin) {
  _wire = new OneWire(pin);
  _addresses = (DSAddress*)malloc(sizeof(DSAddress)); 
}

void DSTemperature::begin(void) {

  DSAddress addr;

  _wire->reset_search();

  while (_wire->search(addr.value)) {
    if (OneWire::crc8(addr.value, 7) == addr.value[7]) {
      if (_nDevices != 0)
        resizeAddresses();
      _addresses[_nDevices++] = addr;
    }
  }

  _wire->reset_search();
  delay(250);
  return;

}

void DSTemperature::resizeAddresses() {

  DSAddress* new_addresses = (DSAddress*)malloc(sizeof(DSAddress) * _nDevices);
  for (byte i = 0 ; i < _nDevices ; i++)
    new_addresses[i] = _addresses[i];
  free(_addresses);
  _addresses = new_addresses;

}

float DSTemperature::getCelsius(byte ds) {
  return CELSIUS(getRawTemperature(ds));
}

float DSTemperature::getFahrenheit(byte ds) {
  return FAHRENHEIT(getRawTemperature(ds));
}

byte DSTemperature::getDeviceCount(void) {
  return _nDevices;
}

DSAddress DSTemperature::getAddressFromIndex(byte ds) {
  return _addresses[ds];
}

float DSTemperature::getRawTemperature(byte ds) {

  byte data[12];

  _wire->reset();
  _wire->select(_addresses[ds].value);
  _wire->write(0x44, 1);
  
  delay(1000);
  
  byte present = _wire->reset();
  _wire->select(_addresses[ds].value);    
  _wire->write(0xBE);

  for (byte i = 0; i < 9; i++) {
    data[i] = _wire->read();
  }

  unsigned int raw = (data[1] << 8) | data[0];
  if (_addresses[ds].value[0] == DS18S20) {
    raw = raw << 3;
    if (data[7] == 0x10) {
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    if (cfg == 0x00) raw = raw << 3;
    else if (cfg == 0x20) raw = raw << 2;
    else if (cfg == 0x40) raw = raw << 1;
  }

  return (float)raw;

}
