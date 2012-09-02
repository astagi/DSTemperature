#include "DSTemperature.h"

DSTemperature::DSTemperature(int pin) {
  this->wire = new OneWire(pin);
}

void DSTemperature::begin(void) {

  byte addr[8];
  int i = 0;

  while ((this->wire)->search(addr)) {
    if (OneWire::crc8(addr, 7) == addr[7]) {
      //Store 'addr'esses in a vector
    }
  }

  (this->wire)->reset_search();
  delay(250);
  return;

}
