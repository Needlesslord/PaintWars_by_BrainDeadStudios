#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "SDL/include/SDL_rect.h"
#include "SDL_image/include/SDL_image.h"

#define MAX_FRAMES 200
typedef unsigned int uint;
enum  ORIENTATION; //?????????????
enum  ENTITY_TYPE;//?????????????

class Animation
{
public:
	bool loop = true;
	float defspeed = 1.0f;
	SDL_Rect frames[MAX_FRAMES];
	float speed;
	uint n_frames = 0;
	ENTITY_TYPE type;
	ORIENTATION orientation;
	SDL_Texture* texture;

private:
	float current_frame;
	int current_speed;
	int last_frame = 0;
	int loops = 0;

public:

	SDL_Rect& GetCurrentFrame();

	void PushBack(const SDL_Rect& rect);
	bool Finished() const;
	void Reset();
	void SetFrame(int frame);
	int GetFrameNum();
	Animation GetAnimation();
};

#endif 