#ifndef __SCENE_H__
#define __SCENE_H__

#include <string>
#include "SDL/include/SDL.h"
#include "PugiXml\src\pugixml.hpp"

#include "j1App.h"								// Watch out with unnecessary includes.
#include "p2Point.h"

enum class SCENES
{
	MENU_SCENE,
	GAME_SCENE,
	SETTINGS_SCENE,
	START_SCENE,
	WIN_SCENE,
	LOSE_SCENE,
	GAME_LOGO_SCENE,
	TEAM_LOGO_SCENE,
	SCORE_SCENE,
	NONE
};

class Scene
{
public:
	Scene(SCENES scene_name);
	virtual ~Scene();

	virtual bool Awake(pugi::xml_node& config);					// Called before render is available
	virtual bool Start();										// Called before the first frame
	virtual bool PreUpdate();									// Called before all Updates
	virtual bool Update(float dt);								// Called each loop iteration
	virtual bool PostUpdate();									// Called before all Updates
	virtual bool CleanUp();										// Called before quitting

public:
	virtual void InitScene();									// Method that will be used to initialize the variables all the scenes.
	virtual void DrawScene();									// Method that will draw the map and all other elements of the scene.
	virtual SDL_Texture* SceneToTexture();						// Creates a unified texture from the current scene.


	virtual void GUI_Event_Manager(GUI_Event type, j1UIElement* element);

	
	virtual void ExecuteTransition();							// Method that will trigger a new transition depending on the input received.
	virtual void CameraDebugMovement(float dt);					// Method that will move the camera around depending on the input.

public:
	SCENES			scene_name;									// SCENE will be both the name and the index of the scene.

	int map_width;												// Width of the map loaded on the scene.
	int map_height;												// Height of the map loaded on the scene.

public:															// RENDER SCENE TO TEXTURE VARIABLES -------------------------------------------------
	SDL_Surface*	scene_surface;								// The scene sub-surface that will be used to get a unified texture from the scene.
	SDL_Renderer*	scene_renderer;								// The scene sub-renderer that will be used to get a unified texture from the scene.
	SDL_Texture*	scene_texture;								// Unified texture from the scene.
	SDL_Texture*	tileset_texture;							// Texture that will be used to blit the map in the Scene Sub-Renderer.

	int x_offset;												// Offset in the x axis. Adds half a tile's width and will be used to make map size related calculations more accurate.
	int y_offset;												// Offset in the y axis. Adds half a tile's height and will be used to make map size related calculations more accurate.
};

#endif // !__SCENE_H__