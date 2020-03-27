#ifndef __j1RENDER_H__
#define __j1RENDER_H__

#include "SDL/include/SDL.h"
#include "p2Point.h"
#include "j1Module.h"
#include <map>

struct BlitEvent
{
	SDL_Texture* texture;
	int x, y;
	const SDL_Rect section;
	bool fliped;
	bool ui;
	float speed;
	uint r, g, b, a;
};

class j1Render : public j1Module
{
public:

	j1Render();
	virtual ~j1Render();

	bool Awake(pugi::xml_node&);

	bool Start();

	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	bool CleanUp();

	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

	void SetViewPort(const SDL_Rect& rect);
	void ResetViewPort();
	iPoint ScreenToWorld(int x, int y) const;

	void AddBlitEvent(int layer, SDL_Texture* texture, int x, int y, const SDL_Rect section, bool fliped = false, bool ui = false, float speed = 1.0f, Uint8 r = 0u, Uint8 g = 0u, Uint8 b = 0u, Uint8 a = 255);
	bool DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool ui = false, bool filled = true, bool use_camera = true, bool guiHitBox = false) const;
	bool DrawLine(int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool use_camera = true) const;
	bool DrawCircle(int x1, int y1, int redius, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool use_camera = true) const;

	void SetBackgroundColor(SDL_Color color);

public:

	SDL_Renderer*	renderer;
	SDL_Rect		camera;
	SDL_Rect		viewport;
	SDL_Color		background;

private:

	std::multimap<int, BlitEvent> blit_queue;

	void BlitAll();
	bool Blit(SDL_Texture* texture, int x, int y, const SDL_Rect* section = NULL, bool fliped = false, bool ui = false, float speed = 1.0f, double angle = 0, int pivot_x = INT_MAX, int pivot_y = INT_MAX)	 const;

};

#endif // __j1RENDER_H__