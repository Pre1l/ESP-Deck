#ifndef DISPLAY_MANAGER_HPP
#define DISPLAY_MANAGER_HPP

#include "TFT_eSPI.h"

namespace DisplayManager 
{
    extern TFT_eSPI tft;

    void initialize();
    TFT_eSPI& getDisplay();
    void resetFont();
    void renderPartialBitmap(int xPartialBitmap, int yPartialBitmap, int xOnBitmap, int yOnBitmap, int widthPartialBitmap, int heightPartialBitmap, int widthBitmap, const unsigned short* bitmap);
}

#endif // DISPLAY_MANAGER_HPP