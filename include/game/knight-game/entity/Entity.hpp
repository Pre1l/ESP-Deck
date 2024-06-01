#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <math/Vector2D.hpp>
#include "game/knight-game/rectangle/Hitbox.hpp"

class Entity 
{
    private:
        std::shared_ptr<Vector2D> position;
        Hitbox hitbox;

    public:
        virtual void update(float offsetX, float deltaTime) = 0;
        Hitbox& getHitbox();
        std::shared_ptr<Vector2D> getPosition();

    protected:
        Entity(std::shared_ptr<Vector2D> position, Hitbox hitbox);
};

#endif // ENTITY_HPP