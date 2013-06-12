#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	RScene * scene = new RScene();
	//Scena podstawowa
/*	scene->addObj(new RSphere(2, vector(0,0,0), vector(0,0,0), vector(0.8,0.1,0.1), vector(0.8,0.8,0.8), 20, 0.5, 0));
	scene->addObj(new RSphere(1, vector(2,2,0), vector(0,0,0), vector(0,0.8,0), vector(0,0,0), 0, 0, 0));
	scene->addObj(new RTriangle(vector(-5,-4,-5), vector(-5,-4,5), vector(5,-4,5), vector(0.01,0.01,0.01), 
		vector(0.01,0.01,0.6), vector(0.01,0.01,0.01), 20, 0.5, 0));
	scene->addObj(new RTriangle(vector(5,-4,5), vector(5,-4,-5), vector(-5,-4,-5), vector(0.01,0.01,0.01), 
		vector(0.01,0.01,0.6), vector(0.01,0.01,0.01), 20, 0.5, 0));

	scene->addLight(new RLight(vector(-4,4,-2), vector(1,1,1), vector(1,1,1), vector(1,1,1)));
	scene->addLight(new RLight(vector(1,1,-10), vector(1,1,1), vector(1,1,1), vector(1,1,1)));*/

//	scene->addObj(new RSphere(1.5, vector(-3,0,1), vector(0,0,0), vector(0.1,0.1,0.8), vector(0.8,0.8,0.8), 10, 0, 0));
//	scene->addObj(new RSphere(0.5, vector(0,0,3), vector(0,0,0), vector(0.5,0.5,0.1), vector(0.0,0.0,0.0), 0, 0, 0));



//	scene->addObj(new RTriangle(-5,-4,-5, -5,-4,5, 5,-4,5, 0.01,0.01,0.01, 0.01,0.01,0.6, 0.01,0.01,0.01, 20, 0, 0));
//	scene->addObj(new RTriangle(5,-4,5, 5,-4,-5, -5,-4,-5, 0.01,0.01,0.01, 0.01,0.01,0.6, 0.01,0.01,0.01, 20, 0, 0));

	/*scene->addObj(new RTriangle(-5,4,6, -5,-4,4, 5,-4,4, 0.01,0.01,0.01, 0.01,0.01,0.6, 0.01,0.01,0.01, 20, 0.7, 0));
	scene->addObj(new RTriangle(5,-4,4, 5,4,6, -5,4,6, 0.01,0.01,0.01, 0.01,0.01,0.6, 0.01,0.01,0.01, 20, 0.7, 0));

	scene->addObj(new RSphere(1.5, 0,0,0, 0,0,0, 0,0.8,0.8, 0.8,0.8,0.8, 0, 0, 0));
	scene->addObj(new RSphere(1.7,  -2,0,3 ,0,0,0, 0.8,0.1,0.1 ,0,0,0 ,20, 0, 0));
	scene->addObj(new RSphere(1.7,  2,0,2 ,0,0,0, 0.8,0.8,0 ,0,0,0 ,0, 0, 0));

	scene->addLight(new RLight(-4,4,-2,1,1,1,1,1,1,1,1,1));
	scene->addLight(new RLight(1,1,-10,1,1,1,1,1,1,1,1,1));*/

	//scene->addObj(new RTriangle(-8,-1.5,-8, -8,-1.5,10, 8,-1.5,10, 0.01,0.01,0.01, 0.2,0.2,0.3, 0.01,0.01,0.01, 20, 0.7, 0));
	//scene->addObj(new RTriangle(-8,-1.5,-8, 8,-1.5,10, 8,-1.5,-8, 0.01,0.01,0.01, 0.2,0.2,0.3, 0.01,0.01,0.01, 20, 0.7, 0));

	//MOJA SCENA
	scene->addObj(new RTriangle(vector(-15,-1.5,-10), vector(0,-1.5,20), vector(15,-1.5,-10), 
		vector(0.01,0.01,0.01), vector(0.2,0.2,0.3), vector(0.01,0.01,0.01), 20, 0.2, 0));
	scene->addObj(new RSphere(1.5, vector(0,0,0), vector(0,0,0), vector(0,0.7,0.7), vector(0,0,0), 0, 0, 1));
	scene->addObj(new RSphere(1.5, vector(1.7,0,3), vector(0,0,0), vector(0.7,0.7,0), vector(0,0,0), 0, 0.7, 0));
	scene->addObj(new RSphere(1.5, vector(-1.7,0,3), vector(0,0,0), vector(0.6,0.05,0.05), vector(0.7,0.7,0.7), 10, 0, 0));
	scene->addLight(new RLight(vector(-3,1,-1), vector(1,1,1), vector(1,1,1), vector(1,1,1)));
	scene->addLight(new RLight(vector(3,6,-5), vector(1,1,1), vector(1,1,1), vector(1,1,1)));

	//szyba
//	scene->addObj(new RTriangle(vector(0,-1,-5), vector(0,1,-5), vector(-1,0,-5), 
//		vector(0.01,0.01,0.01), vector(0,0.7,0.7), vector(0,0,0), 0, 0, 0));

	scene->addLight(new RLight(vector(0,2,-15), vector(1,1,1), vector(1,1,1), vector(1,1,1)));

	RImage * image = new RImage(scene);
	RRayTracer * rayTracer = new RRayTracer(scene,image);

	rayTracer->trace();
	
	return 0;
}

