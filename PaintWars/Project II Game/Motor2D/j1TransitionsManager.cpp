#include "j1App.h"
#include "j1TransitionsManager.h"
#include "j1Transitions.h"
#include "j1Render.h"
#include "j1Window.h"
#include "FadeToColour.h"
//#include "MoveToMouse.h"
//#include "Zoom.h"
//#include "Wipe.h"
#include "Lines.h"
#include "Squares.h"
#include "j1Input.h"

j1TransitionsManager::j1TransitionsManager()
{}

j1TransitionsManager::~j1TransitionsManager()
{}

bool j1TransitionsManager::PostUpdate()
{
		// Calls PostUpdate (switch of states) of every transition in the list
		for (std::list<j1Transitions*>::iterator item = transitions_list.begin(); item != transitions_list.end(); ++item) {
			(*item)->PostUpdate();
		}
	return true;
}

bool j1TransitionsManager::CleanUp() {

	// Clears the list
	transitions_list.clear();

	return true;
}

void j1TransitionsManager::CleanTransitions(j1Transitions* transition) {

	// Removes the list and deletes the transition
	transitions_list.remove(transition);
	delete transition;
}

void j1TransitionsManager::FadingToColour(j1Colour colour, float time) {
	transitions_list.push_back(new FadeToColour(colour, time));
}

void j1TransitionsManager::LinesAppearing(j1Colour colour, float time) {
	transitions_list.push_back(new Lines(colour, time));
}

void j1TransitionsManager::SquaresAppearing(int transition, j1Colour colour, float time) {
	transitions_list.push_back(new Squares(transition, colour, time));
}
