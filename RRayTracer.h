#pragma once
#include "RScene.h";
#include "RImage.h";
#include "RRay.h";

class RRayTracer
{
public:
	RScene * scene; 
	RImage * image;
	int reflectCount;

	RRayTracer( RScene * scene, RImage * image );
	~RRayTracer(void);
	int trace( void );
	vector intersect(RRay * ray);
	bool AnyObstacleBetween(vector pointA, vector pointB);
	vector intersectPoint(RRay * ray, float tmin);
	vector RRayTracer::traceReflect(vector InterPoint, vector dir, vector normalInterPoint);
	double PhongFactor(vector v, vector r, double shin);
	vector pixelColor(RObject * obj, vector interPoint, vector camPos);
	vector traceTransparent(vector InterPoint, vector dir, RObject * obj);
};

