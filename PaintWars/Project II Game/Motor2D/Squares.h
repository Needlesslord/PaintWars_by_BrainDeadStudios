#pragma once

#include "j1Transitions.h"
#include "j1TransitionsManager.h"

#include <vector>

class Squares : public j1Transitions {

public:

	Squares(int transition, j1Colour colour, float time);
	~Squares();

	void Start();
	void Change();
	void Exit();

	void Draw(int appear, int width = 0, int height = 0);

private:
	// Number of rows and columns
	int number = 11;

	// Depending on this number, the squares are drawn in different ways
	int transition;
	std::vector<iPoint> squares_vec;

	uint w, h;
	SDL_Rect screen;
	int square_w, square_h;
	j1Colour colour;


};