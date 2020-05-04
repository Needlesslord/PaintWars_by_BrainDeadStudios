#ifndef __j1SCENE_MANAGER_H__
#define __j1SCENE_MANAGER_H__

#include "j1Module.h"
#include "Scene.h"
#include <vector>

class j1SceneManager : public j1Module
{
public:
	j1SceneManager();
	~j1SceneManager();

	bool Awake(pugi::xml_node& config);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	// Save
	bool Save(pugi::xml_node&) const;

	// Load
	bool Load(pugi::xml_node&);

public:
	void	ScenePushbacks();										// The pushbacks must be made in the order in which the scenes will appear.
	void	LoadInitialScene();										// Will load the first scene in the scenes vector.

	void	SwitchScene(SCENES scene_name);							// Unloads the current scene and then loads the next one.
	void	LoadScene(SCENES scene_name);							// Loads a new scene. Can be called even while there is another one already running.
	void	UnloadScene(Scene* scene_to_unload);					// Unloads a scene. Only use when there is another scene loaded already. Ex. current_scene & next_scene are active.

	Scene*	CreateScene(SCENES scene_name);

	void GUI_Event_Manager(GUI_Event type, j1UIElement* element);

public:
	Scene*					current_scene;							// The scene that is being currently loaded.
	Scene*					next_scene;								// Buffer for the scene that will be loaded next.


	bool Map_Forest_Active;
	bool Map_Snow_Active;
	bool Map_Volcano_Active;

	bool Load_Map_Forest;
	bool Load_Map_Snow;
	bool Load_Map_Volcano;



	bool exit;

private:
	std::vector<Scene*>		scenes;									// All the scenes of the game.
};

#endif // !__SCENE_MANAGER_H__