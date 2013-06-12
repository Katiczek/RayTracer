#pragma once
#include "vector.h"

class RCamera
{
public:
	RCamera(void);
	~RCamera(void);

	int width;
	int height;
	float fov;
	vector eyep;
	vector lookp;
	vector up;
};

