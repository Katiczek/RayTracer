#include "StdAfx.h"
#include "RCamera.h"


RCamera::RCamera(void)
{
	this->width = 1000;//1000x800
	this->height = 800;
	this->eyep = vector(0,2,-15);//3,15,-16);//
	this->lookp = vector(0,0,0);
	this->up = vector(0,1,0);
	this->fov = 50;
}


RCamera::~RCamera(void)
{
}
