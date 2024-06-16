#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP

class Vector2D 
{
    private:
        float x;
        float y;

    public:
        Vector2D() : x(0), y(0) {}
        Vector2D(float x, float y);

        float getX();
        float getY();
        int getIntX();
        int getIntY();
        Vector2D& setX(float x);
        Vector2D& setY(float y);
        Vector2D& addX(float value);
        Vector2D& addY(float value);
        Vector2D& add(Vector2D& other);
        Vector2D& subtract(Vector2D& other);
        Vector2D copy();
        Vector2D& subtractX(float value);
        Vector2D& subtractY(float value);
        Vector2D& multiply(float value);
        bool equals(const Vector2D& other) const;
};

#endif // VECTOR2D_HPP