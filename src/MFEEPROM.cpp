#include <Arduino.h>
#include "MFEEPROM.h"
#include <EEPROM.h>

uint16_t eepromLength = 0;

#if defined(ARDUINO_ARCH_AVR) || defined(CORE_TEENSY) || defined(ARDUINO_ARCH_RP2040) || defined(ARDUINO_ARCH_ESP8266)

void eeprom_init(void) {
#if defined(ARDUINO_ARCH_RP2040)
    EEPROM.begin(2048);
#endif
    eepromLength = EEPROM.length();
    return;
}

uint16_t eeprom_length() {
    return eepromLength;
}

void eeprom_read_block(uint16_t adr, char data[], uint16_t len) {
    if (adr + len > eepromLength) return;
    for (uint16_t i = 0; i<len; i++) {
        EEPROM.get(adr + i,data[i]);
    }
}

void eeprom_write_block (uint16_t adr, char data[], uint16_t len) {
    if (adr + len > eepromLength) return;
    for (uint16_t i = 0; i<len; i++) {
        EEPROM.put(adr + i,data[i]);
    }
#if defined(ARDUINO_ARCH_RP2040) || defined(ARDUINO_ARCH_ESP8266)
    EEPROM.commit();
#endif
}

char eeprom_read_char(uint16_t adr) {
    if (adr >= eepromLength) return 0;
    return EEPROM.read(adr);
}

void eeprom_write_byte (uint16_t adr, char data) {
    if (adr >= eepromLength) return;
    EEPROM.put(adr, data);
#if defined(ARDUINO_ARCH_RP2040) || defined(ARDUINO_ARCH_ESP8266)
    EEPROM.commit();
#endif
}

#elif defined(ARDUINO_ARCH_STM32)

#if defined(DATA_EEPROM_BASE)
# warning  "STM32 w/o buffered API"

void eeprom_init(void) {
        EEPROM.init();
        eepromLength = EEPROM.length();
}

uint16_t eeprom_length() {
    return eepromLength;
}

void eeprom_read_block(uint16_t addr, char data[], uint16_t len) {
    if (adr + len > eepromLength) return;
    for (uint16_t i = 0; i<len; i++) {
        data[i] = EEPROM.read(addr + i);
    }
}

void eeprom_write_block (uint16_t addr, char data[], uint16_t len) {
    if (adr + len > eepromLength) return;
    for (uint16_t i = 0; i<len; i++) {
        EEPROM.write(addr + i,data[i]);
    }
}

uint8_t eeprom_read_char(uint16_t adr, char data) {
    if (adr >= eepromLength) return 0;
    data = EEPROM.read(adr);
}

void eeprom_write_byte (uint16_t adr, char data) {
    if (adr >= eepromLength) return;
    EEPROM.write(adr, data);
}

#else

void eeprom_init(void) {
        eeprom_buffer_fill();
        eepromLength = EEPROM.length();
}

uint16_t eeprom_length() {
    return eepromLength;
}

void eeprom_read_block(uint16_t addr, char data[], uint16_t len) {
    if (adr + len > eepromLength) return;
    for (uint16_t i = 0; i<len; i++) {
        data[i] = eeprom_buffered_read_byte(addr + i);
    }
}

void eeprom_write_block (uint16_t addr, char data[], uint16_t len) {
    if (adr + len > eepromLength) return;
    for (uint16_t i = 0; i<len; i++) {
        eeprom_buffered_write_byte(addr + i,data[i]);
    }
    eeprom_buffer_flush();
}

char eeprom_read_char(uint16_t adr) {
    if (adr >= eepromLength) return 0;
    return eeprom_buffered_read_byte(adr);
}

void eeprom_write_byte (uint16_t adr, char data) {
    if (adr >= eepromLength) return;
    EEPROM.write(adr, data);
    eeprom_buffer_flush();
}
#endif

#endif
