#pragma once
class RSphere : public RObject
{
public:
	RSphere(void);
	RSphere(float radius, vector position, vector ambient, vector diffuse, vector specular, float shiness, float reflect, float transparency);
	~RSphere(void);
	float intersect(RRay * ray);
	vector normal(vector point);
	
	float radius;
	vector pos;
};

