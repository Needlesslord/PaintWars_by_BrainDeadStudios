#include "Cut.h"
#include "TransitionManager.h"

Cut::Cut(SCENES next_scene) : Transition(next_scene, 0.0f)
{

}

Cut::~Cut()
{

}

void Cut::StepTransition()
{
	App->scenes->SwitchScene(next_scene);

	App->transition_manager->DeleteActiveTransition();
}