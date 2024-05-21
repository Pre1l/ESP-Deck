#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <math/Vector2D.hpp>
#include <cstdint>
#include <memory>

class Rectangle 
{
    public:
        static const int COLLISION_X = 0;
        static const int COLLISION_Y = 1;

    private:
        static uint8_t nextId;

        std::shared_ptr<Vector2D> position;
        float width;
        float height;
        uint8_t id;

    public:
        std::shared_ptr<Vector2D> getPosition();
        float getWidth();
        float getHeight();
        uint8_t getId();
        float calculateCollision(Rectangle& other, int direction, bool returnOverlap);

    protected:
        Rectangle(std::shared_ptr<Vector2D> position, float width, float height);
};

#endif // RECTANGLE_HPP