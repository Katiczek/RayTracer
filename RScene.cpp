#include "StdAfx.h"
#include "RScene.h"


RScene::RScene(void)
{
	this->obj_count = 0;
	this->light_count = 0;
}


RScene::~RScene(void)
{
}

void RScene::addObj(RObject * new_obj)
{
	this->obj_list[this->obj_count] = new_obj;
	this->obj_count++;
}

void RScene::addLight(RLight * new_light)
{
	this->light_list[this->light_count] = new_light;
	this->light_count++;
}