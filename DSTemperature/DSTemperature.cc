#include "DSTemperature.h"

DSTemperature::DSTemperature(int pin) {
  _wire = new OneWire(pin);
  _addresses = (DSAddress*)malloc(sizeof(DSAddress)); 
}

void DSTemperature::begin(void) {

  DSAddress addr;
  int i = 0, addr_i = 0;

  while (_wire->search(addr.value)) {
    if (OneWire::crc8(addr.value, 7) == addr.value[7]) {
      resizeAddresses();
      _addresses[_nSensors++] = addr;
    }
  }

  _wire->reset_search();
  delay(250);
  return;

}

void DSTemperature::resizeAddresses() {

  if (_nSensors == 0)
    return;

  DSAddress* new_addresses = (DSAddress*)malloc(sizeof(DSAddress) * _nSensors);
  for (int i = 0 ; i < _nSensors ; i++)
    new_addresses[i] = _addresses[i];
  free(_addresses);
  _addresses = new_addresses;

}

float DSTemperature::getCelsius(int ds) {
  return CELSIUS(getRawTemperature(ds));
}

float DSTemperature::getFahrenheit(int ds) {
  return FAHRENHEIT(getRawTemperature(ds));
}



