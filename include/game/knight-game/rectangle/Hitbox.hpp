#ifndef HITBOX_HPP
#define HITBOX_HPP

#include "Rectangle.hpp"
#include <memory>

class Hitbox : public Rectangle
{
    public:
        Hitbox(std::shared_ptr<Vector2D> position, float width, float height);
};

#endif // HITBOX_HPP