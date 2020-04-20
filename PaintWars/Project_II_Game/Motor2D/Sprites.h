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

Animation warriorAttackWest;
Animation warriorAttackNorthWest;
Animation warriorAttackNorth;
Animation warriorAttackNorthEast;
Animation warriorAttackEast;
Animation warriorAttackSouthEast;
Animation warriorAttackSouth;
Animation warriorAttackSouthWest;


void WarriorSprites()
{

	//Idle 
	warriorIdle.PushBack({ 1068, 0, 89, 152 });
	warriorIdle.PushBack({ 1157, 0, 89, 152 });
	warriorIdle.speed = 50.0f;

	//MOVING

	//Moving Right
	warriorMovingEast.PushBack({ 0, 152, 89, 152 });
	warriorMovingEast.PushBack({ 89, 152, 89, 152 });
	warriorMovingEast.PushBack({ 178, 152, 89, 152 });
	warriorMovingEast.PushBack({ 267, 152, 89, 152 });
	warriorMovingEast.PushBack({ 356, 152, 89, 152 });
	warriorMovingEast.PushBack({ 445, 152, 89, 152 });
	warriorMovingEast.speed = 500.0f;

	//Moving Left
	warriorMovingWest.PushBack({ 534, 152, 89, 152 });
	warriorMovingWest.PushBack({ 623, 152, 89, 152 });
	warriorMovingWest.PushBack({ 712, 152, 89, 152 });
	warriorMovingWest.PushBack({ 801, 152, 89, 152 });
	warriorMovingWest.PushBack({ 890, 152, 89, 152 });
	warriorMovingWest.PushBack({ 979, 152, 89, 152 });
	warriorMovingWest.speed = 500.0f;

	//Moving RightBack
	warriorMovingNorthEast.PushBack({ 0, 304, 89, 152 });
	warriorMovingNorthEast.PushBack({ 89, 304, 89, 152 });
	warriorMovingNorthEast.PushBack({ 178, 304, 89, 152 });
	warriorMovingNorthEast.PushBack({ 267, 304, 89, 152 });
	warriorMovingNorthEast.PushBack({ 356, 304, 89, 152 });
	warriorMovingNorthEast.PushBack({ 445, 304, 89, 152 });
	warriorMovingNorthEast.speed = 500.0f;

	//Moving LeftBack
	warriorMovingNorthWest.PushBack({ 534, 304, 89, 152 });
	warriorMovingNorthWest.PushBack({ 623, 304, 89, 152 });
	warriorMovingNorthWest.PushBack({ 712, 304, 89, 152 });
	warriorMovingNorthWest.PushBack({ 801, 304, 89, 152 });
	warriorMovingNorthWest.PushBack({ 890, 304, 89, 152 });
	warriorMovingNorthWest.PushBack({ 979, 304, 89, 152 });
	warriorMovingNorthWest.speed = 500.0f;


	//Moving RightFront
	warriorMovingSouthEast.PushBack({ 0, 456, 89, 152 });
	warriorMovingSouthEast.PushBack({ 89, 456, 89, 152 });
	warriorMovingSouthEast.PushBack({ 178, 456, 89, 152 });
	warriorMovingSouthEast.PushBack({ 267, 456, 89, 152 });
	warriorMovingSouthEast.PushBack({ 356, 456, 89, 152 });
	warriorMovingSouthEast.PushBack({ 445, 456, 89, 152 });
	warriorMovingSouthEast.speed = 500.0f;

	//Moving LeftFront
	warriorMovingSouthWest.PushBack({ 534, 456, 89, 152 });
	warriorMovingSouthWest.PushBack({ 623, 456, 89, 152 });
	warriorMovingSouthWest.PushBack({ 712, 456, 89, 152 });
	warriorMovingSouthWest.PushBack({ 801, 456, 89, 152 });
	warriorMovingSouthWest.PushBack({ 890, 456, 89, 152 });
	warriorMovingSouthWest.PushBack({ 979, 456, 89, 152 });
	warriorMovingSouthWest.speed = 500.0f;

	//Moving Back
	warriorMovingNorth.PushBack({ 0, 608, 89, 152 });
	warriorMovingNorth.PushBack({ 89, 608, 89, 152 });
	warriorMovingNorth.PushBack({ 178, 608, 89, 152 });
	warriorMovingNorth.PushBack({ 267, 608, 89, 152 });
	warriorMovingNorth.PushBack({ 356, 608, 89, 152 });
	warriorMovingNorth.PushBack({ 445, 608, 89, 152 });
	warriorMovingNorth.speed = 500.0f;

	//Moving Front
	warriorMovingSouth.PushBack({ 534, 608, 89, 152 });
	warriorMovingSouth.PushBack({ 623, 608, 89, 152 });
	warriorMovingSouth.PushBack({ 712, 608, 89, 152 });
	warriorMovingSouth.PushBack({ 801, 608, 89, 152 });
	warriorMovingSouth.PushBack({ 890, 608, 89, 152 });
	warriorMovingSouth.PushBack({ 979, 608, 89, 152 });
	warriorMovingSouth.speed = 500.0f;

	//ATTACK

	//Attack East
	warriorAttackEast.PushBack({ 0, 760, 89, 152 });
	warriorAttackEast.PushBack({ 89, 760, 89, 152 });
	warriorAttackEast.speed = 250.0f;

	//Attack SouthEast
	warriorAttackSouthEast.PushBack({ 178, 760, 89, 152 });
	warriorAttackSouthEast.PushBack({ 267, 760, 89, 152 });
	warriorAttackSouthEast.speed = 250.0f;

	//Attack South
	warriorAttackSouth.PushBack({ 534, 912, 89, 152 });
	warriorAttackSouth.PushBack({ 623, 912, 89, 152 });
	warriorAttackSouth.speed = 250.0f;

	//Attack SouthWest
	warriorAttackSouthWest.PushBack({ 356, 760, 89, 152 });
	warriorAttackSouthWest.PushBack({ 445, 760, 89, 152 });
	warriorAttackSouthWest.speed = 250.0f;

	//Attack West
	warriorAttackWest.PushBack({ 534, 760, 89, 152 });
	warriorAttackWest.PushBack({ 623, 760, 89, 152 });
	warriorAttackWest.speed = 250.0f;

	//Attack NorthWest
	warriorAttackNorthWest.PushBack({ 356, 912, 89, 152 });
	warriorAttackNorthWest.PushBack({ 445, 912, 89, 152 });
	warriorAttackNorthWest.speed = 250.0f;

	//Attack North
	warriorAttackNorth.PushBack({ 178, 912, 89, 152 });
	warriorAttackNorth.PushBack({ 267, 912, 89, 152 });
	warriorAttackNorth.speed = 250.0f;

	//Attack NorthEast
	warriorAttackNorthEast.PushBack({ 0, 912, 89, 152 });
	warriorAttackNorthEast.PushBack({ 89, 912, 89, 152 });
	warriorAttackNorthEast.speed = 250.0f;
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
	painterIdle.PushBack({ 912, 0, 76, 156 });
	painterIdle.PushBack({ 988, 0, 76, 156 });
	painterIdle.speed = 50.0f;

	//MOVING

	//Moving Right
	painterMovingEast.PushBack({ 0, 156, 76, 156 });
	painterMovingEast.PushBack({ 76, 156, 76, 156 });
	painterMovingEast.PushBack({ 152, 156, 76, 156 });
	painterMovingEast.PushBack({ 228, 156, 76, 156 });
	painterMovingEast.PushBack({ 304, 156, 76, 156 });
	painterMovingEast.PushBack({ 380, 156, 76, 156 });
	painterMovingEast.speed = 500.0f;

	//Moving Left
	painterMovingWest.PushBack({ 456, 156, 76, 156 });
	painterMovingWest.PushBack({ 532, 156, 76, 156 });
	painterMovingWest.PushBack({ 608, 156, 76, 156 });
	painterMovingWest.PushBack({ 684, 156, 76, 156 });
	painterMovingWest.PushBack({ 760, 156, 76, 156 });
	painterMovingWest.PushBack({ 836, 156, 76, 156 });
	painterMovingWest.speed = 500.0f;

	//Moving RightBack
	painterMovingNorthEast.PushBack({ 0, 312, 76, 156 });
	painterMovingNorthEast.PushBack({ 76, 312, 76, 156 });
	painterMovingNorthEast.PushBack({ 152, 312, 76, 156 });
	painterMovingNorthEast.PushBack({ 228, 312, 76, 156 });
	painterMovingNorthEast.PushBack({ 304, 312, 76, 156 });
	painterMovingNorthEast.PushBack({ 380, 312, 76, 156 });
	painterMovingNorthEast.speed = 500.0f;

	//Moving LeftBack
	painterMovingNorthWest.PushBack({ 456, 312, 76, 156 });
	painterMovingNorthWest.PushBack({ 532, 312, 76, 156 });
	painterMovingNorthWest.PushBack({ 608, 312, 76, 156 });
	painterMovingNorthWest.PushBack({ 684, 312, 76, 156 });
	painterMovingNorthWest.PushBack({ 760, 312, 76, 156 });
	painterMovingNorthWest.PushBack({ 836, 312, 76, 156 });
	painterMovingNorthWest.speed = 500.0f;


	//Moving RightFront
	painterMovingSouthEast.PushBack({ 0, 468, 76, 156 });
	painterMovingSouthEast.PushBack({ 76, 468, 76, 156 });
	painterMovingSouthEast.PushBack({ 152, 468, 76, 156 });
	painterMovingSouthEast.PushBack({ 228, 468, 76, 156 });
	painterMovingSouthEast.PushBack({ 304, 468, 76, 156 });
	painterMovingSouthEast.PushBack({ 380, 468, 76, 156 });
	painterMovingSouthEast.speed = 500.0f;

	//Moving LeftFront
	painterMovingSouthWest.PushBack({ 456, 468, 76, 156 });
	painterMovingSouthWest.PushBack({ 532, 468, 76, 156 });
	painterMovingSouthWest.PushBack({ 608, 468, 76, 156 });
	painterMovingSouthWest.PushBack({ 684, 468, 76, 156 });
	painterMovingSouthWest.PushBack({ 760, 468, 76, 156 });
	painterMovingSouthWest.PushBack({ 836, 468, 76, 156 });
	painterMovingSouthWest.speed = 500.0f;

	//Moving Back
	painterMovingNorth.PushBack({ 0, 624, 76, 156 });
	painterMovingNorth.PushBack({ 76, 624, 76, 156 });
	painterMovingNorth.PushBack({ 152, 624, 76, 156 });
	painterMovingNorth.PushBack({ 228, 624, 76, 156 });
	painterMovingNorth.PushBack({ 304, 624, 76, 156 });
	painterMovingNorth.PushBack({ 380, 624, 76, 156 });
	painterMovingNorth.speed = 500.0f;

	//Moving Front
	painterMovingSouth.PushBack({ 456, 624, 76, 156 });
	painterMovingSouth.PushBack({ 532, 624, 76, 156 });
	painterMovingSouth.PushBack({ 608, 624, 76, 156 });
	painterMovingSouth.PushBack({ 684, 624, 76, 156 });
	painterMovingSouth.PushBack({ 760, 624, 76, 156 });
	painterMovingSouth.PushBack({ 836, 624, 76, 156 });
	painterMovingSouth.speed = 500.0f;




}
