#include "StdAfx.h"
#include "RTriangle.h"


RTriangle::RTriangle(void)
{
	this->pos1 = vector(-1,0,0);
	this->pos2 = vector(1,0,0);
	this->pos3 = vector(0,0,1);
	this->shiness = 0;
	this->type = 2;//trójk¹t
	this->reflect = 0;
	this->transparency = 0;
}


RTriangle::~RTriangle(void)
{
}

RTriangle::RTriangle(vector pos1, vector pos2, vector pos3, vector ambient, vector diffuse, vector specular, 
		float shiness, float reflect, float transparency)
{
	this->pos1 = pos1;
	this->pos2 = pos2;
	this->pos3 = pos3;
	this->col_amb = ambient;
	this->col_diff = diffuse;
	this->col_spec = specular;
	this->shiness = shiness;
	this->type = 2;//trójk¹t
	this->reflect = reflect;
	this->transparency = transparency;
}

float RTriangle::intersect(RRay * ray)
{
	float A,B,C,D,t;
	A = ((this->pos2.y-this->pos1.y)*(this->pos3.z-this->pos1.z))-((this->pos3.y-this->pos1.y)*(this->pos2.z-this->pos1.z));
	B = (-1)*(((this->pos2.x-this->pos1.x)*(this->pos3.z-this->pos1.z))-((this->pos3.x-this->pos1.x)*(this->pos2.z-this->pos1.z)));
	C = ((this->pos2.x-this->pos1.x)*(this->pos3.y-this->pos1.y))-((this->pos3.x-this->pos1.x)*(this->pos2.y-this->pos1.y));
	D = (A * (-1*this->pos1.x)) + (B * (-1*this->pos1.y)) + (C * (-1*this->pos1.z));

	t = -(A*ray->pos.x + B*ray->pos.y + C*ray->pos.z + D) / (A*ray->dir.x + B*ray->dir.y + C*ray->dir.z);
	
	if( t < 0 )
		return -1;

	// Compute vectors        
	vector v0(this->pos3.subVector(this->pos1)),
		v1(this->pos2.subVector(this->pos1)),
		v2(ray->pos.sumVector(ray->dir.mulConst(t)).subVector(this->pos1));

	// Compute dot products
	float dot00 = v0.dot(v0),
		  dot01 = v0.dot(v1),
		  dot02 = v0.dot(v2),
		  dot11 = v1.dot(v1),
		  dot12 = v1.dot(v2);

	// Compute barycentric coordinates
	float invDenom = 1 / (dot00 * dot11 - dot01 * dot01),
		  u = (dot11 * dot02 - dot01 * dot12) * invDenom,
		  v = (dot00 * dot12 - dot01 * dot02) * invDenom;

	// Check if point is in triangle
	if( (u >= 0.001) && (v >= 0.001) && (u + v < 1) )
		return t;
	else
		return -1;
}

vector RTriangle::normal(vector point)
{
	vector v0(this->pos3.subVector(this->pos1)), 
		   v1(this->pos2.subVector(this->pos1)), 
		   norm( (v0.y*v1.z) - (v0.z * v1.y) , -((v0.z * v1.x) - (v0.x * v1.z)) , (v0.x * v1.y) - (v0.y * v1.x));
	return norm.normalize();
}
