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

float Gear::GearVector::operator*(GearVector const &vec)
{	
	return (_x*vec._x + _y*vec._y);
}

float Gear::GearVector::dot(GearVector const &vec)
{
	return (_x*vec._x + _y*vec._y);
}

GearVector Gear::GearVector::operator+(GearVector const &vec)
{
	return GearVector(_x+vec._x, _y+vec._y);
}

void Gear::GearVector::add(GearVector const &vec)
{
	_x += vec._x; vec._y;
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
