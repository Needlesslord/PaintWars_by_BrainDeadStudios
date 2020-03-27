#ifndef _UI_Item__H
#define _UI_Item__H

#include "j1Module.h"
#include "p2Point.h"

enum UI_State //Types of states
{
	UI_NOTHING,
	IDLE,
	HOVER,
	CLICK,
	MAX_STATE
};


class UI_Item
{
public:
	UI_Item() {};
	virtual ~UI_Item() {};

	virtual bool Start() { return true; };
	bool PreUpdate(float dt);
	virtual bool Update(float dt);
	virtual bool PostUpdate() { return true; };



   virtual bool OnHover() { return true; }; // HOVEING OR NOT HOVERING  MUST BE VIRTUAL OR WON'T WORK (NO IDEA WHY)
	bool OnClick(); //IF THE BUTTON IS CLICKED OR NOT
	bool SliderClick();//IF WE USE CLICK 1 WITH KEY_DOWN IT DOESNT WORK CORRECTLY

public:
	UI_State	state = IDLE; //Initial state
	iPoint		pos;
	iPoint		position;
	iPoint		mouse_position;
	UI_Item*		parent = nullptr; //Global item
	p2Point<int> pivot = { 0,0 };

	bool		drag = false; //For draggable objects
	bool		static_object = false; //Static button
	bool		visible = true; //Show UI items
};

#endif  // !_UI_Item__H
