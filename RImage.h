#pragma once
class RImage
{
	int width;
	int height;
	int *** image;
public:
	RImage(RScene * );
	~RImage(void);
	int save(char *);
	void setPixel(int x , int y , vector color , int a);
};

