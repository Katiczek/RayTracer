#include "StdAfx.h"
#include "vector.h"

vector::vector(void)
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

vector::vector(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

vector::vector(vector pointA, vector pointB)
{
	this->x = pointB.x - pointA.x;
	this->y = pointB.y - pointA.y;
	this->z = pointB.z - pointA.z;
}

vector::vector(vector & v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
}

vector::~vector(void)
{
}

vector vector::sumVector(vector v)
{
	return vector(v.x+this->x,v.y+this->y,v.z+this->z);
}

vector vector::subVector(vector v)
{
	return vector(this->x-v.x,this->y-v.y,this->z-v.z);
}

vector vector::mulVector(vector v)
{
	return vector( this->y*v.z-this->z*v.y , this->z*v.x-this->x*v.z , this->x*v.y-this->y*v.x );
}

vector vector::dotMulVector(vector v)
{
	return vector(this->x*v.x , this->y*v.y , this->z*v.z);
}

vector vector::mulConst(float a)
{
	return vector( this->x*a , this->y*a , this->z*a );
}

vector vector::divisionConst(float a)
{
	return vector( this->x/a , this->y/a , this->z/a );
}

vector vector::normalize()
{
	return this->divisionConst(this->length());
}

float vector::dot(vector v)
{
	return ( this->x*v.x + this->y*v.y + this->z*v.z );
}

float vector::length()
{
	return ( sqrt( pow( this->x,2 ) + pow( this->y,2 ) + pow( this->z,2 ) ) );
}

vector vector::roundColor(void)
{
	if (this->x > 255)
		this->x=255;
	if (this->x < 0)
		this->x=0;
	if (this->y > 255)
		this->y=255;
	if (this->y < 0)
		this->y=0;
	if (this->z > 255)
		this->z=255;
	if (this->z < 0)
		this->z=0;
	return *this;
}