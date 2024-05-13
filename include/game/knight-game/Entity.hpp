#include <math/Vector2D.hpp>
#include "Hitbox.hpp"
#ifndef ENTITY_HPP
#define ENTITY_HPP

class Entity 
{
    private:
        Vector2D* position;
        Vector2D* velocity;
        Hitbox* hitbox;

    public:
        virtual void update(float deltaTime);
        Vector2D* getPosition();
        Vector2D* getVelocity();
        Hitbox* getHitbox();

    protected:
        Entity(Vector2D& position, Vector2D velocity, Hitbox hitbox);
};

#endif // ENTITY_HPP