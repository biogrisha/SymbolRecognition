#pragma once
struct RGB
{
	RGB(unsigned char R, unsigned char G, unsigned char B) :R(R), G(G), B(B)
	{

	}
	RGB(const RGB& rgb) :R(rgb.R), G(rgb.G), B(rgb.R)
	{

	}
	RGB& operator=(const RGB& rgb)
	{
		R = rgb.R;
		G = rgb.G;
		B = rgb.B;
		return *this;
	}

	bool operator==(const RGB& rgb)
	{
		if (R == rgb.R && G == rgb.G && B == rgb.B)
		{
			return true;
		}
		return false;
	}

	unsigned char R;
	unsigned char G;
	unsigned char B;
};

struct Pixel
{
	Pixel(int x, int y, RGB& rgb) :X(x), Y(y), rgb(rgb) {}

	int X;
	int Y;
	RGB rgb;
};

struct Vector
{
	Vector(int x, int y) : X(x), Y(y) {}
	int X;
	int Y;
};