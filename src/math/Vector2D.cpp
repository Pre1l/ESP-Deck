#include "math/Vector2D.hpp"

Vector2D::Vector2D(float x, float y) : x(x), y(y) {}

float Vector2D::getX() 
{
	return x;
}

float Vector2D::getY() 
{
	return y;
}

int Vector2D::getIntX() 
{
	return static_cast<int>(x);
}

int Vector2D::getIntY() 
{
  	return static_cast<int>(y);
}

Vector2D Vector2D::setX(float x) 
{
	this->x = x;

	return *this;
}

Vector2D Vector2D::setY(float y) 
{
	this->y = y;

	return *this;
}

Vector2D Vector2D::addX(float value) 
{
	x += value;

	return *this;
}

Vector2D Vector2D::addY(float value) 
{
	y += value;

	return *this;
}

Vector2D Vector2D::add(Vector2D vector) 
{
	y += vector.getY();
	x += vector.getX();

	return *this;
}

Vector2D Vector2D::subtract(Vector2D vector) 
{
	y -= vector.getY();
	x -= vector.getX();

	return *this;
}

Vector2D Vector2D::copy() 
{
	return Vector2D(x, y);
}

Vector2D Vector2D::subtractX(float value) 
{
	x -= value;
	
	return *this;
}