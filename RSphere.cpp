#include "StdAfx.h"
#include "RSphere.h"

RSphere::RSphere(void)
{
	this->pos = vector(0,0,0);
	this->col_amb = vector(1,1,1);
	this->col_diff = vector(1,1,1);
	this->col_spec = vector(1,1,1);
	this->shiness = 0;
	this->radius = 1;
	this->type = 1;	//sfera
	this->reflect = 0;
	this->transparency = 0;
}

RSphere::RSphere(float radius, vector position, vector ambient, vector diffuse, vector specular, float shiness, float reflect, float transparency)
{
	this->pos = position;
	this->col_amb = ambient;
	this->col_diff = diffuse;
	this->col_spec = specular;
	this->shiness = shiness;
	this->radius = radius;
	this->type = 1;//sfera
	this->reflect = reflect;
	this->transparency = transparency;
}

RSphere::~RSphere(void)
{
}

float RSphere::intersect(RRay * ray)
{
	float t1,t2;
	vector v = ray->pos.subVector(this->pos);
	
	float a = ray->dir.dot(ray->dir);
	float b = ray->dir.dot(v.mulConst(2));
	
	float c = v.dot(v) - (this->radius * this->radius);

	float delta = b * b - 4 * a * c; 

	if(delta < 0)
		return 0;

	delta = sqrt(delta);

	t1 = (-b + delta) / (2.0 * a);
	t2 = (-b - delta) / (2.0 * a);

	if( t1 > 0.001 && t2 > 0.001)
		return (t1 < t2 ? t1 : t2);
	else if( t1 < 0.001 )
		return t2;
	else
		return t1;
}

vector RSphere::normal(vector point)
{
	vector norm = point.subVector(this->pos);
	return norm.normalize();
}

