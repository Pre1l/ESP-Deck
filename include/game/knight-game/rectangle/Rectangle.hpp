#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <math/Vector2D.hpp>
#include <cstdint>
#include <memory>

class Rectangle 
{
    public:
        enum class CollisionAxis {
            X,
            Y
        };

    private:
        static uint8_t nextId;

        std::shared_ptr<Vector2D> position;
        float width;
        float height;
        uint8_t id;

    public:
        virtual std::shared_ptr<Vector2D> getPosition();
        float getWidth();
        float getHeight();
        uint8_t getId();

        float calculateCollision(Rectangle& other, CollisionAxis axis, bool returnOverlap);
        bool calculateCollision(Rectangle& other);

    protected:
        Rectangle(std::shared_ptr<Vector2D> position, float width, float height);
};

#endif // RECTANGLE_HPP