#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <math/Vector2D.hpp>
#include "game/knight-game/rectangle/Hitbox.hpp"

class Entity 
{
    private:
        std::shared_ptr<Vector2D> position;
        Hitbox hitbox;
        float lastOffsetX = 0;
        bool offset = true;

    public:
        virtual void update(float offsetX, float deltaTime);
        Hitbox& getHitbox();
        std::shared_ptr<Vector2D> getPosition();

    protected:
        Entity(std::shared_ptr<Vector2D> position, Hitbox hitbox);
        void disableOffset();
        float getOffsetX();

        virtual void clearAfterImageOffset(float offsetX);
        virtual float getDrawWidth();
        virtual float getDrawHeight();
};

#endif // ENTITY_HPP