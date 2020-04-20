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
	warriorIdle.PushBack({ 945, 0, 76, 148 });
	warriorIdle.PushBack({ 1021, 0, 76, 148 });
	warriorIdle.speed = 50.0f;

	//MOVING

	//Moving Right
	warriorMovingEast.PushBack({ 0, 148, 65, 153 });
	warriorMovingEast.PushBack({ 75, 148, 65, 153 });
	warriorMovingEast.PushBack({ 154, 148, 65, 153 });
	warriorMovingEast.PushBack({ 233, 148, 65, 153 });
	warriorMovingEast.PushBack({ 312, 148, 65, 153 });
	warriorMovingEast.PushBack({ 390, 148, 65, 153 });
	warriorMovingEast.speed = 500.0f;

	//Moving Left
	warriorMovingWest.PushBack({ 470, 148, 64, 149 });
	warriorMovingWest.PushBack({ 537, 244, 69, 149 });
	warriorMovingWest.PushBack({ 606, 244, 69, 149 });
	warriorMovingWest.PushBack({ 675, 244, 69, 149 });
	warriorMovingWest.PushBack({ 744, 244, 69, 149 });
	warriorMovingWest.PushBack({ 813, 244, 69, 149 });
	warriorMovingWest.speed = 500.0f;

	//Moving RightBack
	warriorMovingNorthEast.PushBack({ 0, 296, 69, 149 });
	warriorMovingNorthEast.PushBack({ 69, 296, 69, 149 });
	warriorMovingNorthEast.PushBack({ 207, 296, 69, 149 });
	warriorMovingNorthEast.PushBack({ 276, 296, 69, 149 });
	warriorMovingNorthEast.PushBack({ 354, 296, 69, 149 });
	warriorMovingNorthEast.PushBack({ 423, 296, 69, 149 });
	warriorMovingNorthEast.speed = 500.0f;

	//Moving LeftBack
	warriorMovingNorthWest.PushBack({ 468, 296, 69, 149 });
	warriorMovingNorthWest.PushBack({ 537, 296, 69, 149 });
	warriorMovingNorthWest.PushBack({ 606, 296, 69, 149 });
	warriorMovingNorthWest.PushBack({ 675, 296, 69, 149 });
	warriorMovingNorthWest.PushBack({ 744, 296, 69, 149 });
	warriorMovingNorthWest.PushBack({ 813, 296, 69, 149 });
	warriorMovingNorthWest.speed = 500.0f;


	//Moving RightFront
	warriorMovingSouthEast.PushBack({ 0, 444, 69, 149 });
	warriorMovingSouthEast.PushBack({ 69, 444, 69, 149 });
	warriorMovingSouthEast.PushBack({ 207, 444, 69, 149 });
	warriorMovingSouthEast.PushBack({ 276, 444, 69, 149 });
	warriorMovingSouthEast.PushBack({ 354, 444, 69, 149 });
	warriorMovingSouthEast.PushBack({ 423, 444, 69, 149 });
	warriorMovingSouthEast.speed = 500.0f;

	//Moving LeftFront
	warriorMovingSouthWest.PushBack({ 468, 444, 69, 149 });
	warriorMovingSouthWest.PushBack({ 537, 444, 69, 149 });
	warriorMovingSouthWest.PushBack({ 606, 444, 69, 149 });
	warriorMovingSouthWest.PushBack({ 675, 444, 69, 149 });
	warriorMovingSouthWest.PushBack({ 744, 444, 69, 149 });
	warriorMovingSouthWest.PushBack({ 813, 444, 69, 149 });
	warriorMovingSouthWest.speed = 500.0f;

	//Moving Back
	warriorMovingNorth.PushBack({ 0, 592, 69, 149 });
	warriorMovingNorth.PushBack({ 69, 592, 69, 149 });
	warriorMovingNorth.PushBack({ 207, 592, 69, 149 });
	warriorMovingNorth.PushBack({ 276, 592, 69, 149 });
	warriorMovingNorth.PushBack({ 354, 592, 69, 149 });
	warriorMovingNorth.PushBack({ 423, 592, 69, 149 });
	warriorMovingNorth.speed = 500.0f;

	//Moving Front
	warriorMovingSouth.PushBack({ 468, 592, 69, 149 });
	warriorMovingSouth.PushBack({ 537, 592, 69, 149 });
	warriorMovingSouth.PushBack({ 606, 592, 69, 149 });
	warriorMovingSouth.PushBack({ 675, 592, 69, 149 });
	warriorMovingSouth.PushBack({ 744, 592, 69, 149 });
	warriorMovingSouth.PushBack({ 813, 592, 69, 149 });
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
	painterIdle.PushBack({ 945, 0, 76, 148 });
	painterIdle.PushBack({ 1021, 0, 76, 148 });
	painterIdle.speed = 50.0f;

	//MOVING

	//Moving Right
	painterMovingEast.PushBack({ 0, 148, 69, 149 });
	painterMovingEast.PushBack({ 69, 148, 69, 149 });
	painterMovingEast.PushBack({ 207, 148, 69, 149 });
	painterMovingEast.PushBack({ 276, 148, 69, 149 });
	painterMovingEast.PushBack({ 354, 148, 69, 149 });
	painterMovingEast.PushBack({ 423, 148, 69, 149 });
	painterMovingEast.speed = 500.0f;

	//Moving Left
	painterMovingWest.PushBack({ 468, 148, 69, 149 });
	painterMovingWest.PushBack({ 537, 244, 69, 149 });
	painterMovingWest.PushBack({ 606, 244, 69, 149 });
	painterMovingWest.PushBack({ 675, 244, 69, 149 });
	painterMovingWest.PushBack({ 744, 244, 69, 149 });
	painterMovingWest.PushBack({ 813, 244, 69, 149 });
	painterMovingWest.speed = 500.0f;

	//Moving RightBack
	painterMovingNorthEast.PushBack({ 0, 296, 69, 149 });
	painterMovingNorthEast.PushBack({ 69, 296, 69, 149 });
	warriorMovingNorthEast.PushBack({ 207, 296, 69, 149 });
	painterMovingNorthEast.PushBack({ 276, 296, 69, 149 });
	painterMovingNorthEast.PushBack({ 354, 296, 69, 149 });
	painterMovingNorthEast.PushBack({ 423, 296, 69, 149 });
	painterMovingNorthEast.speed = 500.0f;

	//Moving LeftBack
	painterMovingNorthWest.PushBack({ 468, 296, 69, 149 });
	painterMovingNorthWest.PushBack({ 537, 296, 69, 149 });
	painterMovingNorthWest.PushBack({ 606, 296, 69, 149 });
	painterMovingNorthWest.PushBack({ 675, 296, 69, 149 });
	painterMovingNorthWest.PushBack({ 744, 296, 69, 149 });
	painterMovingNorthWest.PushBack({ 813, 296, 69, 149 });
	painterMovingNorthWest.speed = 500.0f;


	//Moving RightFront
	painterMovingSouthEast.PushBack({ 0, 444, 69, 149 });
	painterMovingSouthEast.PushBack({ 69, 444, 69, 149 });
	painterMovingSouthEast.PushBack({ 207, 444, 69, 149 });
	painterMovingSouthEast.PushBack({ 276, 444, 69, 149 });
	painterMovingSouthEast.PushBack({ 354, 444, 69, 149 });
	painterMovingSouthEast.PushBack({ 423, 444, 69, 149 });
	painterMovingSouthEast.speed = 500.0f;

	//Moving LeftFront
	painterMovingSouthWest.PushBack({ 468, 444, 69, 149 });
	painterMovingSouthWest.PushBack({ 537, 444, 69, 149 });
	painterMovingSouthWest.PushBack({ 606, 444, 69, 149 });
	painterMovingSouthWest.PushBack({ 675, 444, 69, 149 });
	painterMovingSouthWest.PushBack({ 744, 444, 69, 149 });
	painterMovingSouthWest.PushBack({ 813, 444, 69, 149 });
	painterMovingSouthWest.speed = 500.0f;

	//Moving Back
	painterMovingNorth.PushBack({ 0, 592, 69, 149 });
	painterMovingNorth.PushBack({ 69, 592, 69, 149 });
	painterMovingNorth.PushBack({ 207, 592, 69, 149 });
	painterMovingNorth.PushBack({ 276, 592, 69, 149 });
	painterMovingNorth.PushBack({ 354, 592, 69, 149 });
	painterMovingNorth.PushBack({ 423, 592, 69, 149 });
	painterMovingNorth.speed = 500.0f;

	//Moving Front
	painterMovingSouth.PushBack({ 468, 592, 69, 149 });
	painterMovingSouth.PushBack({ 537, 592, 69, 149 });
	painterMovingSouth.PushBack({ 606, 592, 69, 149 });
	painterMovingSouth.PushBack({ 675, 592, 69, 149 });
	painterMovingSouth.PushBack({ 744, 592, 69, 149 });
	painterMovingSouth.PushBack({ 813, 592, 69, 149 });
	painterMovingSouth.speed = 500.0f;




}
