#include "stdafx.h"
#include "RRayTracer.h"
#define PI 3.14159265
#define DEPTH_OF_REFLECT 7
#define background vector(0,0,0)
int flaga;
RRayTracer::RRayTracer( RScene * scene, RImage * image )
{
	this->scene = scene;
	this->image = image;
}


RRayTracer::~RRayTracer(void)
{
}

int RRayTracer::trace()
{
	vector look(scene->cam.lookp.subVector(scene->cam.eyep));

	vector tmp(scene->cam.up.mulVector(look));
	vector u( tmp.divisionConst(tmp.length()) );

	tmp = vector(u.mulVector(look));
	vector v( tmp.divisionConst(tmp.length()) );

	tmp = vector(look.divisionConst(look.length()));
	float constTmp = scene->cam.width / (2*tan((scene->cam.fov/2.0)*PI/180));
	vector o(tmp.mulConst(constTmp));
	tmp = vector(u.mulConst(scene->cam.width/2));
	o = o.subVector(tmp);
	tmp = vector(v.mulConst(scene->cam.height/2));
	o = o.subVector(tmp);

	vector camPos = scene->cam.eyep;	

	vector dir;
	RObject * hit_obj = NULL;
	vector color;
	float tmin = 1e30;
	for(int i=0; i<scene->cam.width; i++)
		for(int j=0; j<scene->cam.height; j++)
		{
			dir.x = u.x*i + v.x*j + o.x;
			dir.y = u.y*i + v.y*j + o.y;
			dir.z = u.z*i + v.z*j + o.z;
			dir = dir.normalize();

			this->reflectCount = 0;
			vector color = intersect(new RRay(camPos, dir));
			image->setPixel(i,j,color,1);
		}

	image->save("C:/Users/Magda/Desktop/Output.bmp");
	
	return 1;
}

vector RRayTracer::intersectPoint(RRay * ray, float tmin)
{
	return (ray->pos.sumVector(ray->dir.mulConst(tmin)));
}

bool RRayTracer::AnyObstacleBetween(vector pointA, vector pointB)
{
	RObject *obj;
	vector vec(pointA,pointB);
	float t,len = vec.length();
	for( int x=0; x<scene->obj_count; x++ )
	{
		obj = scene->obj_list[x];
		t = obj->intersect(new RRay(pointA,vec));
		if(t>0.001 && t<len)
			return true;
	}
	return false;
}
/**
* @brief intersect - function calculate distance from the position (pos) to the nearest object (if such occurs) moving by vector dir
* @param scene - object of RScene, we use in this function object list
* @param pos - position of viewer
* @param dir - vector from pos to direction where veiwer looks
* @param hit_obj - it's reference! At the end of function in program we will have object which we hitted
* @return tmin - length of space between pos and place where we hitted hit_obj
*/
vector RRayTracer::intersect(RRay * ray)
{
	float tmin = 1e30;
	float t;
	RObject *obj, * hit_obj=NULL;
	for( int x=0; x<scene->obj_count; x++ )
	{
		obj = scene->obj_list[x];
		t = obj->intersect(ray);
		if( t>0.001 && t<tmin )
		{
			tmin=t;
			hit_obj = obj;
		}
	}
	if( hit_obj == NULL )
		return background;
	vector interPoint = intersectPoint(ray,tmin);
	vector color = pixelColor(hit_obj,interPoint,ray->pos);
	
	if( hit_obj->reflect != 0 )
	{
		color = color.mulConst(1-hit_obj->reflect);
		if( this->reflectCount < DEPTH_OF_REFLECT )
		{
			this->reflectCount += 1;
			color = color.sumVector(traceReflect(interPoint, ray->dir, hit_obj->normal(interPoint)));
		}
	}
	if( hit_obj->transparency != 0)
	{
		color = color.mulConst(1-hit_obj->transparency);
		color = color.sumVector(traceTransparent(interPoint, ray->dir, hit_obj));
	}
	
	return color;
}

vector RRayTracer::pixelColor(RObject * obj, vector interPoint, vector camPos)//interPoint - punkt uderzenia
{
	vector n = obj->normal(interPoint);
	vector pixCol(0,0,0);
	vector l(0,0,0);							//do Ÿród³a œwiate³ka
	vector r(0,0,0);							//odbity (reflect)
	vector v = camPos.subVector(interPoint);	//do oka
	v = v.normalize();
	for(int k=0;k<scene->light_count;k++)
	{
		//if( AnyObstacleBetween(interPoint,scene->light_list[k]->p) )
		//	continue;
		l = scene->light_list[k]->p.subVector(interPoint);
		l = l.normalize();

		r = n.mulConst(n.dot(l) * 2).subVector(l);
		r = r.normalize();

		pixCol = pixCol.sumVector(scene->light_list[k]->col_amb.dotMulVector(obj->col_amb));

		double diffFactor = l.dot(n);
		if(diffFactor >= 0.0001)
		{
			pixCol = pixCol.sumVector(scene->light_list[k]->col_diff.dotMulVector(obj->col_diff).mulConst(diffFactor));

			double phong = PhongFactor(v,r,obj->shiness);
			if(phong != 0)
				pixCol = pixCol.sumVector(scene->light_list[k]->col_spec.dotMulVector(obj->col_spec).mulConst(phong));
		}
	}
	return pixCol;
}

double RRayTracer::PhongFactor(vector v, vector r, double shin)
{
	double cosAngle = r.dot(v);
	if(cosAngle <= 0)
		return 0;
	return pow(cosAngle,shin);
}

vector RRayTracer::traceReflect(vector InterPoint, vector dir, vector normalInterPoint)
{
	vector reverseDir = dir.mulConst(-1);	//do oka
	float tmp = reverseDir.dot(normalInterPoint) * 2;
	vector reflectDir = reverseDir.subVector(normalInterPoint.mulConst(tmp)).mulConst(-1);

	return intersect(new RRay(InterPoint,reflectDir));
}

//------------------------------------------------------------TRANSPARENT-------------------------------------------
vector ComputeTransmissionDirection(vector toCameraDir, vector interNormal, double eta, double cosTransmittedAngle, double cosIncidentAngle)
{
	if( cosIncidentAngle < 0 )
	{
		interNormal = interNormal.mulConst(-1);
		cosIncidentAngle = -cosIncidentAngle;
	}
	toCameraDir = toCameraDir.mulConst(-1);
	float tmp = (cosTransmittedAngle - cosIncidentAngle / eta);
	
	return toCameraDir.divisionConst(eta).subVector(interNormal.mulConst(tmp));
}

vector ComputeTransmissionColor(float transmission, double eta)
{
	float tmp = (transmission/(eta*eta));

	return vector(tmp,tmp,tmp);
}

double FindRefractionCoeff(double eta, double cosIncidentAngle)
{
	return 1 - (1 - cosIncidentAngle * cosIncidentAngle) / (eta * eta);
}


vector RRayTracer::traceTransparent(vector InterPoint, vector dir, RObject * obj)
{
	float reflection = 0.3, refraction = 1.05, transmission = 0.9;
	//vector transparentColor = pixelColor(obj,InterPoint,camPos);
	vector toCamDir = dir.mulConst(-1);	//do oka
	double cosIncidentAngle = toCamDir.dot(obj->normal(InterPoint));
	double eta = cosIncidentAngle > 0 ? refraction : 1/refraction;
	double refractionCoeff = FindRefractionCoeff(eta, cosIncidentAngle);

	//tutaj nie kolor diff, tylko cos-tam. Wymyœl potem

	if( refractionCoeff < 0 )	//krawêdŸ kuli, promieñ siê odbija. Przekazuje parametry kulki do funkcji reflect
		return traceReflect(InterPoint,dir,obj->normal(InterPoint));

	vector reflectionColor = obj->col_diff.mulConst(reflection);
	vector transmittedDir = ComputeTransmissionDirection(toCamDir, obj->normal(InterPoint),eta,sqrt(refractionCoeff), cosIncidentAngle);
	vector transmissionColor = ComputeTransmissionColor(transmission,eta);

	vector transparentColor(0,0,0);// = transmissionColor.mulVector(traceReflect(InterPoint,dir,obj->normal(InterPoint))).mulVector(reflectionColor);//obj->col_diff.mulConst(reflection);
	transparentColor = transparentColor.sumVector((intersect(new RRay(InterPoint,transmittedDir))).mulVector(transmissionColor));

	return transparentColor;
}