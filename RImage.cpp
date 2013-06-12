#include "stdafx.h"
#include "RImage.h"


RImage::RImage( RScene * scene )
{
	this->width = scene->cam.width;
	this->height = scene->cam.height;

	this->image = new int**[this->width];		//image width x height - all cells with 4 param - red green blue alpha
	for(int i=0;i<this->width;i++)
		this->image[i] = new int*[this->height];
	for(int i=0;i<this->width;i++)
		for(int j=0;j<this->height;j++)
			this->image[i][j] = new int[4];
}


RImage::~RImage(void)
{
}

int RImage::save(char * fname )
{
	BMP Image;
	Image.SetSize(this->width,this->height);
	Image.SetBitDepth(32);							// Set its color depth to 32-bits
	for ( int x=0 ; x < this->width ; x++ )
		for ( int y=0 ; y < this->height ; y++ )
		{
			Image(x,y)->Red = this->image[x][y][0];
			Image(x,y)->Green = this->image[x][y][1];
			Image(x,y)->Blue = this->image[x][y][2];
			Image(x,y)->Alpha = this->image[x][y][3];
		}
	Image.WriteToFile(fname);
	return 1;
}

void RImage::setPixel(int x , int y , vector color , int a)
{
	color = color.mulConst(255);
	color = color.roundColor();
	this->image[x][y][0] = color.x;
	this->image[x][y][1] = color.y;
	this->image[x][y][2] = color.z;
	this->image[x][y][3] = a;
}