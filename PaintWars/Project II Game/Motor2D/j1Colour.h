#ifndef _j1COLOUR_H_
#define _j1COLOUR_H_

struct j1Colour
{
	float r, g, b, a;

	j1Colour() : r(0.0f), g(0.0f), b(0.0f), a(1.0f)
	{}

	j1Colour(float r, float g, float b, float a = 1.0f) : r(r), g(g), b(b), a(a)
	{}

	void Set(float r, float g, float b, float a = 1.0f)
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
};

extern j1Colour Black;
extern j1Colour Grey;
extern j1Colour White;
extern j1Colour Red;
extern j1Colour Green;
extern j1Colour Blue;

#endif