/*
Author: Andrea Stagi <stagi.andrea@gmail.com>
Example: ReadAll
Description: fetch all devices and relative temperatures
on the wire bus on pin 5 and send them via serial port.
*/

#include "DSTemperature.h"

DSTemperature ds(5);  // on pin 5

void setup(void) {
  Serial.begin(9600);
  ds.begin();
}

void loop(void) {
  for(int i = 0 ; i < ds.getDeviceCount() ; i++) {
    Serial.println("-------------------------------------------");
    Serial.print("DEVICE ADDRESS:    ");
    Serial.println(ds.getAddressFromIndex(i).repr());
    Serial.print("TEMPERATURE VALUE: ");
    Serial.print(ds.getCelsius(i));
    Serial.println(" C");
  }
}
