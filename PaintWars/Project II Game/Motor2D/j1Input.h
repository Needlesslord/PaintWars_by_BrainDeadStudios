#ifndef __j1INPUT_H__
#define __j1INPUT_H__

#include "j1Module.h"
#include "p2Point.h"
#include "SDL/include/SDL.h"

//#define NUM_KEYS 352
#define NUM_MOUSE_BUTTONS 5
//#define LAST_KEYS_PRESSED_BUFFER 50

struct SDL_Rect;

enum j1EventWindow
{
	WE_QUIT = 0,
	WE_HIDE = 1,
	WE_SHOW = 2,
	WE_COUNT
};

enum j1KeyState
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

class j1Input : public j1Module
{

public:

	j1Input();
	virtual ~j1Input();


	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();

	bool CleanUp();

	// Gather relevant win events
	bool GetWindowEvent(j1EventWindow ev);

	// Check key states (includes mouse and joy buttons)
	j1KeyState GetKey(int id) const
	{
		return keyboard[id];
	}

	j1KeyState GetMouseButtonDown(int id) const
	{
		return mouse_buttons[id - 1];
	}

	// Check if a certain window event happened
	bool GetWindowEvent(int code);

	// Get mouse / axis position
	void GetMousePosition(int &x, int &y);
	iPoint GetMouseWorldPosition();
	void GetMouseMotion(int& x, int& y);


	void EnableTextInput();
	void DisableTextInput();
	int GetCursorPosition();

	p2SString GetText();
	p2SString GetModifiedString();

	p2SString	final_text;
	p2SString	text;


	float			ball_roll;
private:
	bool		windowEvents[WE_COUNT];
	j1KeyState*	keyboard;
	j1KeyState	mouse_buttons[NUM_MOUSE_BUTTONS];
	float			mouse_motion_x;
	float			mouse_motion_y;
	float			mouse_x;
	float			mouse_y;

	int			cursor_position = 0;
	bool		text_input = false;
};

#endif // __j1INPUT_H__