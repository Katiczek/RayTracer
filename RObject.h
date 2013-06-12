#pragma once
#include "RRay.h"
#include "vector.h"
//class RScene;

class RObject
{
public:
	RObject(void);
	~RObject(void);
	virtual float intersect(RRay * ray);
	virtual vector normal(vector point);

	int type; //typ obiektu (np kula)
	vector col_diff;
	vector col_amb;
	vector col_spec;
	float shiness;
	float reflect;
	float transparency;
};

