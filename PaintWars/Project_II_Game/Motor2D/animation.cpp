#include "j1App.h"
#include "animation.h"

void Animation::PushBack(const SDL_Rect& rect)
{
	frames[last_frame++] = rect;
}

Animation Animation::GetAnimation()
{
	return *this;
}

SDL_Rect& Animation::GetCurrentFrame()
{
	current_frame += speed * (App->dt / 100);
	if (current_frame >= last_frame)
	{
		current_frame = (loop) ? 0.0f : last_frame - 1;
		loops++;
	}

	return frames[(int)current_frame];
}

bool Animation::Finished() const
{
	return loops > 0;
}

void Animation::Reset()
{
	current_frame = 0;
}

void Animation::SetFrame(int frame)
{
	current_frame = frame;
}

int Animation::GetFrameNum()
{
	return current_frame;
}