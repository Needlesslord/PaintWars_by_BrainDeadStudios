#include "j1TransitionsManager.h"
#include "j1Transitions.h"
#include "j1EntityManager.h"
#include "j1Player.h"
#include "j1Render.h"
#include "FadeToColour.h"
#include "j1App.h"
#include "j1Window.h"
#include "p2Log.h"

// Similar code to FadeToBlack, but now we can control the color easily

FadeToColour::FadeToColour(j1Colour colour, float time) : j1Transitions(time) {

	this->colour = colour;

	uint w, h;
	App->win->GetWindowSize(w, h);
	screen = { 0, 0, (int)w, (int)h };
	SDL_SetRenderDrawBlendMode(App->render->renderer, SDL_BLENDMODE_BLEND);

}

FadeToColour::~FadeToColour()
{}

void FadeToColour::Start() {

	j1Transitions::Start();

	// Filling the screen with a color
	FillScreen(Interpolation(0, 255, percentage));
}

void FadeToColour::Change() {

	// FillScreen(255.0f);


	j1Transitions::Change();
}

void FadeToColour::Exit() {

	// Color disappears
	FillScreen(Interpolation(255, 0, percentage));

	j1Transitions::Exit();
}

void FadeToColour::FillScreen(float percentage) {

	if (percentage < 0)
		percentage = 0;

	if (percentage > 255)
		percentage = 255;

	SDL_SetRenderDrawColor(App->render->renderer, colour.r, colour.g, colour.b, percentage);
	SDL_RenderFillRect(App->render->renderer, &screen);
}