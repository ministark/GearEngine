#include "GearVector.h"
using namespace Gear;

GearVector::GearVector()
{
	_x = 0;	_y = 0;
}

Gear::GearVector::GearVector(float x, float y)
{
	_x = x;	_y = y;
}

Gear::GearVector::GearVector(const GearVector &vec)
{
	_x = vec._x; _y = vec._y;
}


GearVector::~GearVector()
{
}

float Gear::GearVector::operator*(const GearVector  &vec) const
{	
	return (_x*vec._x + _y*vec._y);
}

float Gear::GearVector::dot(GearVector const &vec)
{
	return (_x*vec._x + _y*vec._y);
}

GearVector Gear::GearVector::operator*(const float &s) const
{
	return GearVector(_x*s, _y*s);
}

void Gear::GearVector::s_mul(const float &s)
{
	_x *= s; _y *= s;
}

GearVector Gear::GearVector::operator+(const GearVector  &vec) const
{
	return GearVector(_x+vec._x, _y+vec._y);
}

void Gear::GearVector::add(GearVector const &vec)
{
	_x += vec._x; _y += vec._y;
}

void Gear::GearVector::operator+=(const GearVector &vec) 
{
	_x += vec._x; _y += vec._y;
}

GearVector Gear::GearVector::operator-(const GearVector &vec) const
{
	return GearVector(_x - vec._x, _y - vec._y);
}

void Gear::GearVector::sub(const GearVector &vec)
{
	_x -= vec._x; _y -= vec._y;

}

float Gear::GearVector::norm()
{
	float r = std::sqrtf(powf(_x, 2) + powf(_y, 2));
	_x /= r; _y /= r;
	return r;
}

float Gear::GearVector::len(GearVector const &)
{
	return  std::sqrtf(powf(_x, 2) + powf(_y, 2));

}
