#pragma once
class vector
{
public:
	vector(void);
	vector(vector & v);
	vector(float x, float y, float z);
	vector(vector pointA, vector pointB);
	~vector(void);

	vector sumVector(vector v);
	vector subVector(vector v);	
	vector mulVector(vector v);
	vector mulConst(float a);
	vector divisionConst(float a);
	vector normalize();
	float dot(vector u);		//scalar multiplay
	float length();
	vector roundColor(void);
	vector dotMulVector(vector v);

	float x,y,z;
};

