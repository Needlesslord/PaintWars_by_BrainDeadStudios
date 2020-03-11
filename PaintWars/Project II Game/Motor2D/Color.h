class Color
{
public:

	Color(unsigned int r = 0u, unsigned int g = 0u, unsigned int b = 0u, unsigned int a = 255u)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	void SetColor(unsigned int r, unsigned int g, unsigned int b, unsigned int a = 255u)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
	void SetAlpha(unsigned int a)
	{
		this->a = a;
	}

	void Red()
	{
		r = 255u;
		g = 0u;
		b = 0u;
	}
	void Green()
	{
		r = 0u;
		g = 255u;
		b = 0u;
	}
	void Blue()
	{
		r = 0u;
		g = 0u;
		b = 255u;
	}
	void White()
	{
		r = 255u;
		g = 255u;
		b = 255u;
	}
	void Black()
	{
		r = 0u;
		g = 0u;
		b = 0u;
	}

	unsigned int r;
	unsigned int g;
	unsigned int b;
	unsigned int a;

};
