#include "eeprom/EepromManager.hpp"
#include <EEPROM.h>

int32_t EepromManager::readInt32(int address) 
{
    byte byte1 = EEPROM.read(address);
    byte byte2 = EEPROM.read(address + 1);
    byte byte3 = EEPROM.read(address + 2);
    byte byte4 = EEPROM.read(address + 3);

    return (byte4 << 24) | (byte3 << 16) | (byte2 << 8) | byte1;
}

int16_t EepromManager::readInt16(int address)
{
    byte byte1 = EEPROM.read(address);
    byte byte2 = EEPROM.read(address + 1);

    return (byte2 << 8) | byte1;
}

int8_t EepromManager::readInt8(int address)
{
    return EEPROM.read(address);
}

void EepromManager::writeInt32(int address, int32_t value)
{
    EEPROM.put(address, value);
    EEPROM.commit();
}

void EepromManager::writeInt16(int address, int16_t value)
{
    EEPROM.put(address, value);
    EEPROM.commit();
}

void EepromManager::writeInt8(int address, int8_t value)
{
    EEPROM.put(address, value);
    EEPROM.commit();
}