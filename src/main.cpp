
#include <Arduino.h>
#include "MFEEPROM.h"

void setup() {
  
  eeprom_init();
  uint16_t bufferlength = eeprom_length();
  char buffer[bufferlength];

  // initialize the LED pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  while (!Serial) delay(10);

  
  Serial.print("Anzahl Zellen: "); Serial.println(eeprom_length());
  for (int i = 0 ; i < bufferlength ; i++) {
    buffer[i] = 0xFF;
  }

  eeprom_write_block(0,buffer, bufferlength);

// turn the LED on when we're done
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("Speicher gelöscht");

  Serial.print("Anzahl Zellen: "); Serial.println(bufferlength);
  for (int i = 0 ; i < bufferlength ; i+=32) {
    Serial.print(i); Serial.print(" to "); Serial.print(i+32); Serial.print(": ");Serial.print("\t");
    for (uint16_t j = i; j < i+32; j++) {
      Serial.print(eeprom_read_char(j));
    }
    Serial.println("");
  }

  for (int i = 0 ; i < bufferlength ; i+=32) {
    Serial.print(i); Serial.print(" to "); Serial.print(i+32); Serial.print(": ");Serial.print("\t");
    for (uint16_t j = i; j<i+32; j++) {
      uint8_t n = eeprom_read_char(j);
      Serial.print("0x");
      Serial.print(n < 16 ? "0" : "");
      Serial.print(n, HEX);
      Serial.print(" ");
    }
    Serial.println("");
  }
}


void loop() {
/** Empty loop. **/
}