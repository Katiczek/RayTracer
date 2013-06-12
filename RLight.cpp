#include "StdAfx.h"
#include "RLight.h"


RLight::RLight(void)
{
	this->p = vector(0,0,0);
	this->col_amb = vector(1,1,1);
	this->col_diff = vector(1,1,1);
	this->col_spec = vector(1,1,1);
}

RLight::RLight( vector position, vector ambient, vector diffuse, vector specular )
{
	this->p = position;
	this->col_amb = ambient;
	this->col_diff = diffuse;
	this->col_spec = specular;
}

RLight::~RLight(void)
{
}
