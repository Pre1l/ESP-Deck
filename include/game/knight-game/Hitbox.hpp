#ifndef HITBOX_HPP
#define HITBOX_HPP

#include "Rectangle.hpp"

class Hitbox : public Rectangle
{
    public:
        Hitbox(Vector2D* position, float width, float height);
};

#endif // HITBOX_HPP