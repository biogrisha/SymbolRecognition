#pragma once

#include <iostream>
#include "stb_image.h"
#include "ImageRelatedDataStructs.h"

class Image
{
public:
	Image(std::string path);
	Image(const Image& img);
	~Image();
	RGB GetPixel(int x, int y)const;

	void SetPixel(int x, int y, unsigned char R, unsigned char G, unsigned char B);
	void SetPixel(int x, int y, RGB rgb);

	void DrawLine(const Vector& start, const Vector& end, const RGB& rgb);
	void DrawLine(const Vector& start, const Vector& end, unsigned char R, unsigned char G, unsigned char B);
	void DrawLine(const Pixel& start, const Pixel& end);

	int GetWidth()const;
	int GetHeight()const;


	const unsigned char* GetData()const;
private:
	const int sizeOfPix = 3;
	unsigned char* data;
	RGB* rgb = new RGB(0, 0, 0);
	int width;
	int height;
	int nrChannels;
	int dataLenth;

	void Initialize(const char path[]);





};