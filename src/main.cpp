
#include <Arduino.h>
#include "MFEEPROM.h"

#define CLEARBYTE 0xFF;
#ifdef ARDUINO_AVR_PROMICRO16
#define TXLED0 PORTD &= ~(1 << 5)
#define TXLED1 PORTD |= (1 << 5)
#define RXLED0 PORTB &= ~(1 << 0)
#define RXLED1 PORTB |= (1 << 0)
#define TX_RX_LED_INIT DDRD |= (1 << 5), DDRB |= (1 << 0), TXLED0, RXLED0
#endif

MFEEPROM MFeeprom;

void setup() {

  MFeeprom.init();

  uint16_t bufferlength = MFeeprom.get_length();
  char buffer[bufferlength];

  // initialize the LED pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
#if defined(PRINTOUT) || defined(ONLY_DUMP)
  while (!Serial) delay(10);
  Serial.print("Number of Bytes: "); Serial.println(bufferlength);
#endif

#if !defined(ONLY_DUMP)
  for (uint16_t i = 0 ; i < bufferlength ; i++) {
    buffer[i] = CLEARBYTE;
  }

  if (MFeeprom.write_block(0,buffer, bufferlength)) 
#endif
  {
#if defined(PRINTOUT) && !defined(ONLY_DUMP)
    Serial.println("Memory erased");
  } else {
    Serial.println("Failure! Memory not erased (completly)");
#endif
  }

#if defined(PRINTOUT) || defined(ONLY_DUMP)
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
#ifdef ARDUINO_AVR_PROMICRO16
  TXLED0;
  RXLED0;
  delay(1000);
  TXLED1;
  RXLED1;
  delay(1000);
#else
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
#endif
}