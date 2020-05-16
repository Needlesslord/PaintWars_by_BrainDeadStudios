#ifndef __j1WINDOW_H__
#define __j1WINDOW_H__

#include "j1Module.h"

struct SDL_Window;
struct SDL_Surface;
struct SDL_Rect;

class j1Window : public j1Module
{
public:

	j1Window();

	// Destructor
	virtual ~j1Window();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before quitting
	bool CleanUp();

	// Changae title
	void SetTitle(const char* new_title);

	// Retrive window size
	void GetWindowSize(int& width, int& height) const;
	void GetWindowRect(SDL_Rect& rect) const;

	// Retrieve window scale
	float GetScale() const;

	void Fullscreen_Swap();

public:
	//The window we'll be rendering to
	SDL_Window* window;

	//The surface contained by the window
	SDL_Surface* screen_surface;
	float		scale;
	int		width;
	int		height;
	bool fullscreen;
private:
	std::string	title;
	
	
};

#endif // __j1WINDOW_H__