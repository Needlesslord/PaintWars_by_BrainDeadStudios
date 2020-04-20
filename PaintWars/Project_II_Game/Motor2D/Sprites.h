#pragma once

#include "animation.h"

//WARRIOR

Animation warriorIdle;

Animation warriorMovingWest;
Animation warriorMovingNorthWest;
Animation warriorMovingNorth;
Animation warriorMovingNorthEast;
Animation warriorMovingEast;
Animation warriorMovingSouthEast;
Animation warriorMovingSouth;
Animation warriorMovingSouthWest;

void WarriorSprites()
{
	//Idle 
	warriorIdle.PushBack({ 1500, 5, 123, 239 });
	warriorIdle.PushBack({ 1623, 5, 125, 239 });
	warriorIdle.speed = 50.0f;

	//MOVING

	//Moving Right
	warriorMovingEast.PushBack({ 0, 244, 125, 244 });
	warriorMovingEast.PushBack({ 125, 244, 125, 244 });
	warriorMovingEast.PushBack({ 250, 244, 125, 244 });
	warriorMovingEast.PushBack({ 375, 244, 125, 244 });
	warriorMovingEast.PushBack({ 500, 244, 125, 244 });
	warriorMovingEast.PushBack({ 625, 244, 125, 244 });
	warriorMovingEast.speed = 500.0f;

	//Moving Left
	warriorMovingWest.PushBack({ 750, 244, 125, 244 });
	warriorMovingWest.PushBack({ 875, 244, 125, 244 });
	warriorMovingWest.PushBack({ 1000, 244, 125, 244 });
	warriorMovingWest.PushBack({ 1125, 244, 125, 244 });
	warriorMovingWest.PushBack({ 1250, 244, 125, 244 });
	warriorMovingWest.PushBack({ 1375, 244, 125, 244 });
	warriorMovingWest.speed = 500.0f;

	//Moving RightBack
	warriorMovingNorthEast.PushBack({ 0, 488, 125, 244 });
	warriorMovingNorthEast.PushBack({ 125, 488, 125, 244 });
	warriorMovingNorthEast.PushBack({ 250, 488, 125, 244 });
	warriorMovingNorthEast.PushBack({ 375, 488, 125, 244 });
	warriorMovingNorthEast.PushBack({ 500, 488, 125, 244 });
	warriorMovingNorthEast.PushBack({ 625, 488, 125, 244 });
	warriorMovingNorthEast.speed = 500.0f;

	//Moving LeftBack
	warriorMovingNorthWest.PushBack({ 750, 488, 125, 244 });
	warriorMovingNorthWest.PushBack({ 875, 488, 125, 244 });
	warriorMovingNorthWest.PushBack({ 1000, 488, 125, 244 });
	warriorMovingNorthWest.PushBack({ 1125, 488, 125, 244 });
	warriorMovingNorthWest.PushBack({ 1250, 488, 125, 244 });
	warriorMovingNorthWest.PushBack({ 1375, 488, 125, 244 });
	warriorMovingNorthWest.speed = 500.0f;


	//Moving RightFront
	warriorMovingSouthEast.PushBack({ 0, 732, 125, 244 });
	warriorMovingSouthEast.PushBack({ 125, 732, 125, 244 });
	warriorMovingSouthEast.PushBack({ 250, 732, 125, 244 });
	warriorMovingSouthEast.PushBack({ 375, 732, 125, 244 });
	warriorMovingSouthEast.PushBack({ 500, 732, 125, 244 });
	warriorMovingSouthEast.PushBack({ 625, 732, 125, 244 });
	warriorMovingSouthEast.speed = 500.0f;

	//Moving LeftFront
	warriorMovingSouthWest.PushBack({ 750, 732, 125, 244 });
	warriorMovingSouthWest.PushBack({ 875, 732, 125, 244 });
	warriorMovingSouthWest.PushBack({ 1000, 732, 125, 244 });
	warriorMovingSouthWest.PushBack({ 1125, 732, 125, 244 });
	warriorMovingSouthWest.PushBack({ 1250, 732, 125, 244 });
	warriorMovingSouthWest.PushBack({ 1375, 732, 125, 244 });
	warriorMovingSouthWest.speed = 500.0f;

	//Moving Back
	warriorMovingNorth.PushBack({ 0, 976, 125, 244 });
	warriorMovingNorth.PushBack({ 125, 976, 125, 244 });
	warriorMovingNorth.PushBack({ 250, 976, 125, 244 });
	warriorMovingNorth.PushBack({ 375, 976, 125, 244 });
	warriorMovingNorth.PushBack({ 500, 976, 125, 244 });
	warriorMovingNorth.PushBack({ 625, 976, 125, 244 });
	warriorMovingNorth.speed = 500.0f;

	//Moving Front
	warriorMovingSouth.PushBack({ 750, 976, 125, 244 });
	warriorMovingSouth.PushBack({ 875, 976, 125, 244 });
	warriorMovingSouth.PushBack({ 1000, 976, 125, 244 });
	warriorMovingSouth.PushBack({ 1125, 976, 125, 244 });
	warriorMovingSouth.PushBack({ 1250, 976, 125, 244 });
	warriorMovingSouth.PushBack({ 1375, 976, 125, 244 });
	warriorMovingSouth.speed = 500.0f;
}
	


//PAINTER
Animation painterIdle;


Animation painterMovingWest;
Animation painterMovingNorthWest;
Animation painterMovingNorth;
Animation painterMovingNorthEast;
Animation painterMovingEast;
Animation painterMovingSouthEast;
Animation painterMovingSouth;
Animation painterMovingSouthWest;

void PainterSprites()
{
	//Idle
	painterIdle.PushBack({ 1272, 0, 106, 222 });
	painterIdle.PushBack({ 1378, 0, 106, 222 });
	painterIdle.speed = 50.0f;


	//MOVING

	//Moving Right
	painterMovingEast.PushBack({ 0, 222, 106, 222 });
	painterMovingEast.PushBack({ 106, 222, 106, 222 });
	painterMovingEast.PushBack({ 212, 222, 106, 222 });
	painterMovingEast.PushBack({ 318, 222, 106, 222 });
	painterMovingEast.PushBack({ 424, 222, 106, 222 });
	painterMovingEast.PushBack({ 530, 222, 106, 222 });
	painterMovingEast.speed = 500.0f;

	//Moving Left
	painterMovingWest.PushBack({ 636, 222, 106, 222 });
	painterMovingWest.PushBack({ 742, 222, 106, 222 });
	painterMovingWest.PushBack({ 848, 222, 106, 222 });
	painterMovingWest.PushBack({ 954, 222, 106, 222 });
	painterMovingWest.PushBack({ 1060, 222, 106, 222 });
	painterMovingWest.PushBack({ 1166, 222, 106, 222 });
	painterMovingWest.speed = 500.0f;

	//Moving RightBack
	painterMovingNorthEast.PushBack({ 0, 444, 106, 222 });
	painterMovingNorthEast.PushBack({ 106, 444, 106, 222 });
	painterMovingNorthEast.PushBack({ 212, 444, 106, 222 });
	painterMovingNorthEast.PushBack({ 318, 444, 106, 222 });
	painterMovingNorthEast.PushBack({ 424, 444, 106, 222 });
	painterMovingNorthEast.PushBack({ 530, 444, 106, 222 });
	painterMovingNorthEast.speed = 500.0f;

	//Moving LeftBack
	painterMovingNorthWest.PushBack({ 636, 444, 106, 222 });
	painterMovingNorthWest.PushBack({ 742, 444, 106, 222 });
	painterMovingNorthWest.PushBack({ 848, 444, 106, 222 });
	painterMovingNorthWest.PushBack({ 954, 444, 106, 222 });
	painterMovingNorthWest.PushBack({ 1060, 444, 106, 222 });
	painterMovingNorthWest.PushBack({ 1166, 444, 106, 222 });
	painterMovingNorthWest.speed = 500.0f;


	//Moving RightFront
	painterMovingSouthEast.PushBack({ 0, 666, 106, 222 });
	painterMovingSouthEast.PushBack({ 106, 666, 106, 222 });
	painterMovingSouthEast.PushBack({ 212, 666, 106, 222 });
	painterMovingSouthEast.PushBack({ 318, 666, 106, 222 });
	painterMovingSouthEast.PushBack({ 424, 666, 106, 222 });
	painterMovingSouthEast.PushBack({ 530, 666, 106, 222 });
	painterMovingSouthEast.speed = 500.0f;

	//Moving LeftFront
	painterMovingSouthWest.PushBack({ 636, 666, 106, 222 });
	painterMovingSouthWest.PushBack({ 742, 666, 106, 222 });
	painterMovingSouthWest.PushBack({ 848, 666, 106, 222 });
	painterMovingSouthWest.PushBack({ 954, 666, 106, 222 });
	painterMovingSouthWest.PushBack({ 1060, 666, 106, 222 });
	painterMovingSouthWest.PushBack({ 1166, 666, 106, 222 });
	painterMovingSouthWest.speed = 500.0f;

	//Moving Back
	painterMovingNorth.PushBack({ 0, 888, 106, 222 });
	painterMovingNorth.PushBack({ 106, 888, 106, 222 });
	painterMovingNorth.PushBack({ 212, 888, 106, 222 });
	painterMovingNorth.PushBack({ 318, 888, 106, 222 });
	painterMovingNorth.PushBack({ 424, 888, 106, 222 });
	painterMovingNorth.PushBack({ 530, 888, 106, 222 });
	painterMovingNorth.speed = 500.0f;

	//Moving Front
	painterMovingSouth.PushBack({ 636, 888, 106, 222 });
	painterMovingSouth.PushBack({ 742, 888, 106, 222 });
	painterMovingSouth.PushBack({ 848, 888, 106, 222 });
	painterMovingSouth.PushBack({ 954, 888, 106, 222 });
	painterMovingSouth.PushBack({ 1060, 888, 106, 222 });
	painterMovingSouth.PushBack({ 1166, 888, 106, 222 });
	painterMovingSouth.speed = 500.0f;
}
