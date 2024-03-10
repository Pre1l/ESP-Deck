#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP

class Vector2D 
{
    private:
        float x;
        float y;

    public:
        Vector2D(float x, float y);

        float getX();
        float getY();
        int getIntX();
        int getIntY();
        void setX(float x);
        void setY(float y);
        void addX(float value);
        void addY(float value);
};

#endif // VECTOR2D_HPP