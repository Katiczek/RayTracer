#pragma once
class RRay
{
public:
	RRay(vector pos, vector dir);
	~RRay(void);

	vector pos;
	vector dir;
};

