#pragma once
class RTriangle : public RObject
{
public:
	RTriangle(void);
	RTriangle(vector pos1, vector pos2, vector pos3, vector ambient, vector diffuse, vector specular, 
		float shin, float reflect, float transparency);
	~RTriangle(void);

	float intersect(RRay * ray);
	vector normal(vector point);

	vector pos1, pos2, pos3;
};

