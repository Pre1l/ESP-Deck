#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include "Rectangle.hpp"

class Terrain : public Rectangle
{
    private:
        int16_t color;
        float lastOffsetX;

    public:
        Terrain(Vector2D* position, float width, float height, float offsetX, int16_t color);
        void render(float offsetX);
};

#endif // TERRAIN_HPP