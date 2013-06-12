#pragma once
#include "RCamera.h"
#include "RObject.h"
#include "RLight.h"

class RScene
{
public:
	RScene(void);
	~RScene(void);

	void addObj(RObject * new_obj);
	void addLight(RLight * new_light);

	RCamera cam;
	RObject *obj_list[100];
	RLight * light_list[10];
	int obj_count, light_count;
};

