#ifndef EEPROM_MANAGER_HPP
#define EEPROM_MANAGER_HPP

#include <cstdint>

namespace EepromManager 
{
    const int EEPROM_SNAKE_CLASSIC_HIGHSCORE_ADDR_INT8 = 0;
    const int EEPROM_SNAKE_SPEED_HIGHSCORE_ADDR_INT8 = 1;
    const int EEPROM_SNAKE_RISING_HIGHSCORE_ADDR_INT8 = 2;
    const int EEPROM_MERGE_HIGHSCORE_ADDR_INT16 = 3;
    const int EEPROM_FLAPPYBIRD_EASY_HIGHSCORE_ADDR_INT16 = 5;
    const int EEPROM_FLAPPYBIRD_NORMAL_HIGHSCORE_ADDR_INT16 = 7;
    const int EEPROM_FLAPPYBIRD_HARD_HIGHSCORE_ADDR_INT16 = 9;

    int32_t readInt32(int address);
    int16_t readInt16(int address);
    int8_t readInt8(int address);

    void writeInt32(int address, int32_t value);
    void writeInt16(int address, int16_t value);
    void writeInt8(int address, int8_t value);
}

#endif // EEPROM_MANAGER_HPP