#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include "Rectangle.hpp"

class Terrain : public Rectangle
{
    private:
        int16_t color;

    public:
        Terrain(Vector2D* position, float width, float height, int16_t color);

    private:
        void render();
};

#endif // TERRAIN_HPP