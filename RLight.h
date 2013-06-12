#pragma once
#include "vector.h"

class RLight
{
public:
	RLight(void);
	RLight( vector position, vector ambient, vector diffuse, vector specular);
	~RLight(void);

	vector p;			//po³o¿enie œwiat³a
	vector col_diff, 
		   col_amb, 
		   col_spec;
};

