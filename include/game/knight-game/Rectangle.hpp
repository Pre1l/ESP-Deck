#include <math/Vector2D.hpp>
#include <cstdint>
#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

class Rectangle 
{
    private:
        static uint8_t nextId;

        Vector2D& position;
        float width;
        float height;
        uint8_t id;

    public:
        Vector2D& getPosition();
        float getWidth();
        float getHeight();
        uint8_t getId();

    protected:
        Rectangle(Vector2D& position, float width, float height);
};

#endif // RECTANGLE_HPP