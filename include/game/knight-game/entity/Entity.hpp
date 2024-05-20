#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <math/Vector2D.hpp>
#include "game/knight-game/rectangle/Hitbox.hpp"

class Entity 
{
    private:
        Vector2D position;
        Vector2D velocity;

    public:
        virtual void update(float deltaTime) = 0;
        Vector2D& getPosition();
        Vector2D& getVelocity();

    protected:
        Entity(Vector2D& position, Vector2D velocity);
};

#endif // ENTITY_HPP