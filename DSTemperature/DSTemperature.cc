#include "DSTemperature.h"

DSTemperature::DSTemperature(byte pin) {
  _wire = new OneWire(pin);
  _addresses = (DSAddress*)malloc(sizeof(DSAddress)); 
}

void DSTemperature::begin(void) {

  DSAddress addr;

  while (_wire->search(addr.value)) {
    if (OneWire::crc8(addr.value, 7) == addr.value[7]) {
      if (_nSensors != 0)
        resizeAddresses();
      _addresses[_nSensors++] = addr;
    }
  }

  _wire->reset_search();
  delay(250);
  return;

}

void DSTemperature::resizeAddresses() {

  DSAddress* new_addresses = (DSAddress*)malloc(sizeof(DSAddress) * _nSensors);
  for (byte i = 0 ; i < _nSensors ; i++)
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
