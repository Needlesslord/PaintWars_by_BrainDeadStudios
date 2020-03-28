#pragma once

struct Color
{
	float r, g, b, a;

	Color() : r(0), g(0), b(0), a(255)
	{}

	Color(float r, float g, float b, float a = 255) : r(r), g(g), b(b), a(a)
	{}

	void Set(float r, float g, float b, float a = 255)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	float* operator & ()
	{
		return (float*)this;
	}

	bool operator ==(const Color& v) const
	{
		return (r == v.r && g == v.g && b == v.b);
	}
};

extern Color Red;
extern Color Green;
extern Color Blue;
extern Color Black;
extern Color White;
extern Color Yellow;
extern Color Pink;
extern Color Purple;
extern Color Orange;
extern Color Magenta;
extern Color Cyan;
extern Color Grey;