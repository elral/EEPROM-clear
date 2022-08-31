
#include <Arduino.h>
#include "MFEEPROM.h"

#define CLEARBYTE 0xFF;

MFEEPROM MFeeprom;

void setup() {

  MFeeprom.init();

  uint16_t bufferlength = MFeeprom.get_length();
  char buffer[bufferlength];
  char incomingByte = 0;

  // initialize the LED pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  while (!Serial) delay(10);
  delay(1000);
  Serial.println("Please press 'd' for only dumping the EEPROM");
  Serial.println("or press 'e' for erasing and dumping the EEPROM");

  do
  {
    if (Serial.available() > 0) {
      incomingByte = Serial.read();
      if (incomingByte=='d' || incomingByte =='e') {
        break;
      } else {
        Serial.println("Please press 'd' or 'e' ");
      }
    }
  } while (incomingByte != 'd' || incomingByte != 'e');

  Serial.print("Number of Bytes in EEPROM: "); Serial.println(bufferlength);

  for (uint16_t i = 0 ; i < bufferlength ; i++) {
    buffer[i] = CLEARBYTE;
  }

  if (incomingByte == 'e') {
    if (MFeeprom.write_block(0,buffer, bufferlength)) {
      // turn the LED on when we're done
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("Memory erased");
    } else {
      Serial.println("Failure! Memory not erased (completly)");
    }
  }

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
}


void loop() {
/** Empty loop. **/
}