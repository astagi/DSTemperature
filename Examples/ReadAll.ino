/*
  Author: Andrea Stagi <stagi.andrea@gmail.com>
  Example: ReadAll
  Description: fetch all devices and relative temperatures
  on the wire bus on pin 5 and send them via serial port.
*/

#include <OneWire.h>
#include <DSTemperature.h>

DSTemperature ds(5);  // on pin 5

void setup(void) {
  Serial.begin(9600);
  ds.begin();
}

void sendAddress(DSAddress ds) {
  for(int i = 0 ; i < 8 ; i++) {
    Serial.print(ds.value[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
}

void loop(void) {
  for(int i = 0 ; i < ds.getDeviceCount() ; i++) {
    Serial.println("-------------------------------------------");
    Serial.print("DEVICE ADDRESS:    ");
    sendAddress(ds.getAddressFromIndex(i));
    Serial.print("TEMPERATURE VALUE: ");
    Serial.print(ds.getCelsius(i));
    Serial.println(" C");
  }

  /*
    TODO: try to get index from 28 DA E5 D1 3 0 0 77 and 28 DA 19 0 0 0 20 32
  */
} 
