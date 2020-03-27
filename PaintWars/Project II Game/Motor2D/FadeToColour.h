#pragma once

#include "j1TransitionsManager.h"
#include "j1Transitions.h"

class FadeToColour : public j1Transitions {
public:

	FadeToColour(j1Colour colour = Black, float time = 2.0f);
	~FadeToColour();

	void Start();
	void Change();
	void Exit();

	void FillScreen(float percentage);

private:

	j1Colour colour;
	SDL_Rect screen;

	bool changing_scene = false;
};