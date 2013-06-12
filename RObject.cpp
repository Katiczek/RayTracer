#include "StdAfx.h"
#include "RObject.h"

RObject::RObject(void)
{
}


RObject::~RObject(void)
{
}

float RObject::intersect(RRay * ray)
{
	return -1;
}

vector RObject::normal(vector point)
{
	return point;
}
