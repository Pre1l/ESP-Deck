#include "math/Vector2D.hpp"
#include <cmath>

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
	return round(x);
}

int Vector2D::getIntY() 
{
  	return round(y);
}

Vector2D& Vector2D::setX(float x) 
{
	this->x = x;

	return *this;
}

Vector2D& Vector2D::setY(float y) 
{
	this->y = y;

	return *this;
}

Vector2D& Vector2D::addX(float value) 
{
	x += value;

	return *this;
}

Vector2D& Vector2D::addY(float value) 
{
	y += value;

	return *this;
}

Vector2D& Vector2D::add(Vector2D& other) 
{
	y += other.getY();
	x += other.getX();

	return *this;
}

Vector2D& Vector2D::subtract(Vector2D& other) 
{
	y -= other.getY();
	x -= other.getX();

	return *this;
}

Vector2D Vector2D::copy() 
{
	return *this;
}

Vector2D& Vector2D::subtractX(float value) 
{
	x -= value;
	
	return *this;
}

Vector2D& Vector2D::subtractY(float value) 
{
	y -= value;
	
	return *this;
}

Vector2D& Vector2D::multiply(float value) 
{
	x *= value;
	y *= value;
	
	return *this;
}