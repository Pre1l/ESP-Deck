#include <math/Vector2D.hpp>
#include "Hitbox.hpp"
#ifndef ENTITY_HPP
#define ENTITY_HPP

class Entity 
{
    private:
        Vector2D position;
        Vector2D velocity;

    public:
        virtual void update(float deltaTime);
        Vector2D& getPosition();
        Vector2D& getVelocity();

    protected:
        Entity(Vector2D& position, Vector2D velocity);
};

#endif // ENTITY_HPP