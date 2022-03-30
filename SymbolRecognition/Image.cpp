#include<iostream>
#include "Image.h"
using namespace std;

Image::Image(string path)
{
	Initialize(path.data());
}

Image::Image(const Image& img)
{
	width = img.GetWidth();
	height = img.GetHeight();
	dataLenth = width * height * sizeOfPix;
	data = new unsigned char[dataLenth];
	for (int i = 0; i < dataLenth - 1;i++)
	{
		const unsigned char* tmp = img.GetData();
		data[i] = tmp[i];

	}
}

Image::~Image()
{
	delete[] data;
	delete rgb;
}

RGB Image::GetPixel(int x, int y)const
{
	//counting from 0 on every dimention
	int index = y * width * sizeOfPix + x * sizeOfPix;
	if (index >= 0 && index <= dataLenth - sizeOfPix - 1)
	{
		rgb->R = data[index];
		rgb->G = data[index + 1];
		rgb->B = data[index + 2];
		return *rgb;
	}

}

void Image::SetPixel(int x, int y, unsigned char R, unsigned char G, unsigned char B)
{
	int index = y * width * sizeOfPix + x * sizeOfPix;
	if (index >= 0 && index <= dataLenth - sizeOfPix - 1)
	{
		data[index] = R;
		data[index + 1] = G;
		data[index + 2] = B;
	}
}

void Image::SetPixel(int x, int y, RGB rgb)
{
	int index = y * width * sizeOfPix + x * sizeOfPix;
	if (index >= 0 && index <= dataLenth - sizeOfPix - 1)
	{
		data[index] = rgb.R;
		data[index + 1] = rgb.G;
		data[index + 2] = rgb.B;
	}
}

void Image::DrawLine(const Vector& start, const Vector& end, const RGB& rgb)
{

	double x = 0;
	double y = 0;
	double loopCount = 0;
	double xLenth = start.X - end.X;
	double yLenth = start.Y - end.Y;
	double abs_xLenth = abs(xLenth);
	double abs_yLenth = abs(yLenth);
	double sign = 1;
	double statement = 0;
	if (abs_xLenth > abs_yLenth)
	{
		loopCount = abs_xLenth;
		statement = abs_yLenth / abs_xLenth;
		if (xLenth > 0)
		{
			sign = -1;
		}
		else
		{
			sign = 1;
		}
		if (yLenth > 0)
		{
			statement *= -1;
		}
		else if (yLenth < 0)
		{
			statement *= 1;
		}
		for (double i = 0; i < loopCount; i += 1)
		{
			x += 1 * sign;
			y = i * statement;
			SetPixel(x + start.X, y + start.Y, rgb);
		}
	}
	else if (abs_yLenth > abs_xLenth)
	{
		loopCount = abs_yLenth;
		statement = abs_xLenth / abs_yLenth;
		if (yLenth > 0)
		{
			sign = -1;
		}
		else
		{
			sign = 1;
		}
		if (xLenth > 0)
		{
			statement *= -1;
		}
		else if (xLenth < 0)
		{
			statement *= 1;
		}
		for (double i = 0; i < loopCount; i += 1)
		{
			y += 1 * sign;
			x = i * statement;
			SetPixel(x + start.X, y + start.Y, rgb);
		}
	}
	else if (abs_yLenth == abs_xLenth)
	{
		loopCount = abs_yLenth;
		statement = abs_xLenth / abs_yLenth;
		if (yLenth > 0)
		{
			sign = -1;
		}
		else
		{
			sign = 1;
		}
		if (xLenth > 0)
		{
			statement *= -1;
		}
		else if (xLenth < 0)
		{
			statement *= 1;
		}
		for (double i = 0; i < loopCount; i += 1)
		{
			y += 1 * sign;
			x = i * statement;
			SetPixel(x + start.X, y + start.Y, rgb);
		}
	}




}


int Image::GetWidth()const
{
	return width;
}

int Image::GetHeight()const
{
	return height;
}

const unsigned char* Image::GetData()const
{
	return data;
}

void Image::Initialize(const char path[])
{
	data = stbi_load(path, &width, &height, &nrChannels, 0);
	dataLenth = width * height * sizeOfPix;
}
