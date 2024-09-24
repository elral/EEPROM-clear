
#include <Arduino.h>
#include "MFEEPROM.h"

#define CLEARBYTE 0xFF;

MFEEPROM MFeeprom;

void setup() {

  MFeeprom.init();

  uint16_t bufferlength = MFeeprom.get_length();
  char buffer[bufferlength];

  // initialize the LED pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
#ifdef PRINTOUT
  while (!Serial) delay(10);
  Serial.print("Number of Bytes: "); Serial.println(bufferlength);
  delay(500);
#endif

#ifndef ONLY_DUMP
  for (uint16_t i = 0 ; i < bufferlength ; i++) {
    buffer[i] = CLEARBYTE;
  }

  if (MFeeprom.write_block(0,buffer, bufferlength)) {
    
#ifdef PRINTOUT
    Serial.println("Memory erased");
  } else {
    Serial.println("Failure! Memory not erased (completly)");
#endif
  }
#endif

#ifdef PRINTOUT
  Serial.print("Number of Bytes: "); Serial.println(bufferlength);
  for (uint16_t i = 0 ; i < bufferlength ; i+=32) {
    Serial.print(i); Serial.print(" to "); Serial.print(i+32); Serial.print(": ");Serial.print("\t");
    for (uint16_t j = i; j < i+32; j++) {
      Serial.print(MFeeprom.read_char(j));
    }
    Serial.println("");
  }

  for (uint16_t i = 0 ; i < bufferlength ; i+=32) {
    Serial.print(i); Serial.print(" to "); Serial.print(i+32); Serial.print(": ");Serial.print("\t");
    for (uint16_t j = i; j<i+32; j++) {
      uint8_t n = MFeeprom.read_char(j);
      Serial.print("0x");
      Serial.print(n < 16 ? "0" : "");
      Serial.print(n, HEX);
      Serial.print(" ");
    }
    Serial.println("");
  }
#endif
}


void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}