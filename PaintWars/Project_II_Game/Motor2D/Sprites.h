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

//PALADIN

Animation knightIdle;

Animation knightMovingWest;
Animation knightMovingNorthWest;
Animation knightMovingNorth;
Animation knightMovingNorthEast;
Animation knightMovingEast;
Animation knightMovingSouthEast;
Animation knightMovingSouth;
Animation knightMovingSouthWest;

Animation knightAttackWest;
Animation knightAttackNorthWest;
Animation knightAttackNorth;
Animation knightAttackNorthEast;
Animation knightAttackEast;
Animation knightAttackSouthEast;
Animation knightAttackSouth;
Animation knightAttackSouthWest;


void KnightSprites()
{

	//Idle 
	knightIdle.PushBack({ 1052, 0, 88, 151 });
	knightIdle.PushBack({ 1140, 0, 88, 151 });
	knightIdle.speed = 50.0f;

	//MOVING

	//Moving Right
	knightMovingEast.PushBack({ 0, 151, 88, 151 });
	knightMovingEast.PushBack({ 88, 151, 88, 151 });
	knightMovingEast.PushBack({ 176, 151, 88, 151 });
	knightMovingEast.PushBack({ 264, 151, 88, 151 });
	knightMovingEast.PushBack({ 352, 151, 88, 151 });
	knightMovingEast.PushBack({ 440, 151, 88, 151 });
	knightMovingEast.speed = 500.0f;

	//Moving Left
	knightMovingWest.PushBack({ 528, 151, 88, 151 });
	knightMovingWest.PushBack({ 616, 151, 88, 151 });
	knightMovingWest.PushBack({ 704, 151, 88, 151 });
	knightMovingWest.PushBack({ 792, 151, 88, 151 });
	knightMovingWest.PushBack({ 880, 151, 88, 151 });
	knightMovingWest.PushBack({ 968, 151, 88, 151 });
	knightMovingWest.speed = 500.0f;

	//Moving RightBack
	knightMovingNorthEast.PushBack({ 0, 302, 88, 151 });
	knightMovingNorthEast.PushBack({ 88, 302, 88, 151 });
	knightMovingNorthEast.PushBack({ 176, 302, 88, 151 });
	knightMovingNorthEast.PushBack({ 264, 302, 88, 151 });
	knightMovingNorthEast.PushBack({ 352, 302, 88, 151 });
	knightMovingNorthEast.PushBack({ 440, 302, 88, 151 });
	knightMovingNorthEast.speed = 500.0f;

	//Moving LeftBack
	knightMovingNorthWest.PushBack({ 528, 302, 88, 151 });
	knightMovingNorthWest.PushBack({ 616, 302, 88, 151 });
	knightMovingNorthWest.PushBack({ 704, 302, 88, 151 });
	knightMovingNorthWest.PushBack({ 792, 302, 88, 151 });
	knightMovingNorthWest.PushBack({ 880, 302, 88, 151 });
	knightMovingNorthWest.PushBack({ 968, 302, 88, 151 });
	knightMovingNorthWest.speed = 500.0f;


	//Moving RightFront
	knightMovingSouthEast.PushBack({ 0, 453, 88, 151 });
	knightMovingSouthEast.PushBack({ 88, 453, 88, 151 });
	knightMovingSouthEast.PushBack({ 176, 453, 88, 151 });
	knightMovingSouthEast.PushBack({ 264, 453, 88, 151 });
	knightMovingSouthEast.PushBack({ 352, 453, 88, 151 });
	knightMovingSouthEast.PushBack({ 440, 453, 88, 151 });
	knightMovingSouthEast.speed = 500.0f;

	//Moving LeftFront
	knightMovingSouthWest.PushBack({ 528, 453, 88, 151 });
	knightMovingSouthWest.PushBack({ 616, 453, 88, 151 });
	knightMovingSouthWest.PushBack({ 704, 453, 88, 151 });
	knightMovingSouthWest.PushBack({ 792, 453, 88, 151 });
	knightMovingSouthWest.PushBack({ 880, 453, 88, 151 });
	knightMovingSouthWest.PushBack({ 968, 453, 88, 151 });
	knightMovingSouthWest.speed = 500.0f;

	//Moving Back
	knightMovingNorth.PushBack({ 0, 604, 88, 151 });
	knightMovingNorth.PushBack({ 88, 604, 88, 151 });
	knightMovingNorth.PushBack({ 176, 604, 88, 151 });
	knightMovingNorth.PushBack({ 264, 604, 88, 151 });
	knightMovingNorth.PushBack({ 352, 604, 88, 151 });
	knightMovingNorth.PushBack({ 440, 604, 88, 151 });
	knightMovingNorth.speed = 500.0f;

	//Moving Front
	knightMovingSouth.PushBack({ 528, 604, 88, 151 });
	knightMovingSouth.PushBack({ 616, 604, 88, 151 });
	knightMovingSouth.PushBack({ 704, 604, 88, 151 });
	knightMovingSouth.PushBack({ 792, 604, 88, 151 });
	knightMovingSouth.PushBack({ 880, 604, 88, 151 });
	knightMovingSouth.PushBack({ 968, 604, 88, 151 });
	knightMovingSouth.speed = 500.0f;

	//ATTACK

	//Attack East
	knightAttackEast.PushBack({ 0, 755, 88, 151 });
	knightAttackEast.PushBack({ 88, 755, 88, 151 });
	knightAttackEast.speed = 250.0f;

	//Attack SouthEast
	knightAttackSouthEast.PushBack({ 176, 755, 88, 151 });
	knightAttackSouthEast.PushBack({ 264, 755, 88, 151 });
	knightAttackSouthEast.speed = 250.0f;

	//Attack South
	knightAttackSouth.PushBack({ 528, 906, 88, 151 });
	knightAttackSouth.PushBack({ 616, 906, 88, 151 });
	knightAttackSouth.speed = 250.0f;

	//Attack SouthWest
	knightAttackSouthWest.PushBack({ 352, 755, 88, 151 });
	knightAttackSouthWest.PushBack({ 440, 755, 88, 151 });
	knightAttackSouthWest.speed = 250.0f;

	//Attack West
	knightAttackWest.PushBack({ 528, 755, 88, 151 });
	knightAttackWest.PushBack({ 616, 755, 88, 151 });
	knightAttackWest.speed = 250.0f;

	//Attack NorthWest
	knightAttackNorthWest.PushBack({ 352, 906, 88, 151 });
	knightAttackNorthWest.PushBack({ 440, 906, 88, 151 });
	knightAttackNorthWest.speed = 250.0f;

	//Attack North
	knightAttackNorth.PushBack({ 176, 906, 88, 151 });
	knightAttackNorth.PushBack({ 264, 906, 88, 151 });
	knightAttackNorth.speed = 250.0f;

	//Attack NorthEast
	knightAttackNorthEast.PushBack({ 0, 906, 88, 151 });
	knightAttackNorthEast.PushBack({ 88, 906, 88, 151 });
	knightAttackNorthEast.speed = 250.0f;
}

//EXPLORER
Animation explorerIdle;


Animation explorerMovingWest;
Animation explorerMovingNorthWest;
Animation explorerMovingNorth;
Animation explorerMovingNorthEast;
Animation explorerMovingEast;
Animation explorerMovingSouthEast;
Animation explorerMovingSouth;
Animation explorerMovingSouthWest;

void ExplorerSprites()
{



	//Idle 
	explorerIdle.PushBack({ 900, 0, 75, 156 });
	explorerIdle.PushBack({ 975, 0, 75, 156 });
	explorerIdle.speed = 50.0f;

	//MOVING

	//Moving Right
	explorerMovingEast.PushBack({ 0, 156, 75, 156 });
	explorerMovingEast.PushBack({ 75, 156, 75, 156 });
	explorerMovingEast.PushBack({ 150, 156, 75, 156 });
	explorerMovingEast.PushBack({ 225, 156, 75, 156 });
	explorerMovingEast.PushBack({ 300, 156, 75, 156 });
	explorerMovingEast.PushBack({ 375, 156, 75, 156 });
	explorerMovingEast.speed = 500.0f;

	//Moving Left
	explorerMovingWest.PushBack({ 450, 156, 75, 156 });
	explorerMovingWest.PushBack({ 525, 156, 75, 156 });
	explorerMovingWest.PushBack({ 600, 156, 75, 156 });
	explorerMovingWest.PushBack({ 675, 156, 75, 156 });
	explorerMovingWest.PushBack({ 750, 156, 75, 156 });
	explorerMovingWest.PushBack({ 825, 156, 75, 156 });
	explorerMovingWest.speed = 500.0f;

	//Moving RightBack
	explorerMovingNorthEast.PushBack({ 0, 312, 75, 156 });
	explorerMovingNorthEast.PushBack({ 75, 312, 75, 156 });
	explorerMovingNorthEast.PushBack({ 150, 312, 75, 156 });
	explorerMovingNorthEast.PushBack({ 225, 312, 75, 156 });
	explorerMovingNorthEast.PushBack({ 300, 312, 75, 156 });
	explorerMovingNorthEast.PushBack({ 375, 312, 75, 156 });
	explorerMovingNorthEast.speed = 500.0f;

	//Moving LeftBack
	explorerMovingNorthWest.PushBack({ 450, 312, 75, 156 });
	explorerMovingNorthWest.PushBack({ 525, 312, 75, 156 });
	explorerMovingNorthWest.PushBack({ 600, 312, 75, 156 });
	explorerMovingNorthWest.PushBack({ 675, 312, 75, 156 });
	explorerMovingNorthWest.PushBack({ 750, 312, 75, 156 });
	explorerMovingNorthWest.PushBack({ 825, 312, 75, 156 });
	explorerMovingNorthWest.speed = 500.0f;


	//Moving RightFront
	explorerMovingSouthEast.PushBack({ 0, 468, 75, 156 });
	explorerMovingSouthEast.PushBack({ 75, 468, 75, 156 });
	explorerMovingSouthEast.PushBack({ 150, 468, 75, 156 });
	explorerMovingSouthEast.PushBack({ 225, 468, 75, 156 });
	explorerMovingSouthEast.PushBack({ 300, 468, 75, 156 });
	explorerMovingSouthEast.PushBack({ 375, 468, 75, 156 });
	explorerMovingSouthEast.speed = 500.0f;

	//Moving LeftFront
	explorerMovingSouthWest.PushBack({ 450, 468, 75, 156 });
	explorerMovingSouthWest.PushBack({ 525, 468, 75, 156 });
	explorerMovingSouthWest.PushBack({ 600, 468, 75, 156 });
	explorerMovingSouthWest.PushBack({ 675, 468, 75, 156 });
	explorerMovingSouthWest.PushBack({ 750, 468, 75, 156 });
	explorerMovingSouthWest.PushBack({ 825, 468, 75, 156 });
	explorerMovingSouthWest.speed = 500.0f;

	//Moving Back
	explorerMovingNorth.PushBack({ 0, 624, 75, 156 });
	explorerMovingNorth.PushBack({ 75, 624, 75, 156 });
	explorerMovingNorth.PushBack({ 150, 624, 75, 156 });
	explorerMovingNorth.PushBack({ 225, 624, 75, 156 });
	explorerMovingNorth.PushBack({ 300, 624, 75, 156 });
	explorerMovingNorth.PushBack({ 375, 624, 75, 156 });
	explorerMovingNorth.speed = 500.0f;

	//Moving Front
	explorerMovingSouth.PushBack({ 450, 624, 75, 156 });
	explorerMovingSouth.PushBack({ 525, 624, 75, 156 });
	explorerMovingSouth.PushBack({ 600, 624, 75, 156 });
	explorerMovingSouth.PushBack({ 675, 624, 75, 156 });
	explorerMovingSouth.PushBack({ 750, 624, 75, 156 });
	explorerMovingSouth.PushBack({ 825, 624, 75, 156 });
	explorerMovingSouth.speed = 500.0f;
}

//RANGED
Animation rangedIdle;


Animation rangedMovingWest;
Animation rangedMovingNorthWest;
Animation rangedMovingNorth;
Animation rangedMovingNorthEast;
Animation rangedMovingEast;
Animation rangedMovingSouthEast;
Animation rangedMovingSouth;
Animation rangedMovingSouthWest;

void RangedSprites()
{



	//Idle 
	rangedIdle.PushBack({ 948, 0, 75, 156 });
	rangedIdle.PushBack({ 1027, 0, 75, 156 });
	rangedIdle.speed = 50.0f;

	//MOVING

	//Moving Right
	rangedMovingEast.PushBack({ 0, 156, 75, 156 });
	rangedMovingEast.PushBack({ 79, 156, 75, 156 });
	rangedMovingEast.PushBack({ 158, 156, 75, 156 });
	rangedMovingEast.PushBack({ 233, 156, 75, 156 });
	rangedMovingEast.PushBack({ 312, 156, 75, 156 });
	rangedMovingEast.PushBack({ 391, 156, 75, 156 });
	rangedMovingEast.speed = 500.0f;

	//Moving Left
	rangedMovingWest.PushBack({ 470, 156, 75, 156 });
	rangedMovingWest.PushBack({ 549, 156, 75, 156 });
	rangedMovingWest.PushBack({ 628, 156, 75, 156 });
	rangedMovingWest.PushBack({ 707, 156, 75, 156 });
	rangedMovingWest.PushBack({ 786, 156, 75, 156 });
	rangedMovingWest.PushBack({ 865, 156, 75, 156 });
	rangedMovingWest.speed = 500.0f;

	//Moving RightBack
	rangedMovingNorthEast.PushBack({ 0, 312, 75, 156 });
	rangedMovingNorthEast.PushBack({ 79, 312, 75, 156 });
	rangedMovingNorthEast.PushBack({ 158, 312, 75, 156 });
	rangedMovingNorthEast.PushBack({ 233, 312, 75, 156 });
	rangedMovingNorthEast.PushBack({ 312, 312, 75, 156 });
	rangedMovingNorthEast.PushBack({ 391, 312, 75, 156 });
	rangedMovingNorthEast.speed = 500.0f;

	//Moving LeftBack
	rangedMovingNorthWest.PushBack({ 470, 312, 75, 156 });
	rangedMovingNorthWest.PushBack({ 549, 312, 75, 156 });
	rangedMovingNorthWest.PushBack({ 628, 312, 75, 156 });
	rangedMovingNorthWest.PushBack({ 707, 312, 75, 156 });
	rangedMovingNorthWest.PushBack({ 786, 312, 75, 156 });
	rangedMovingNorthWest.PushBack({ 865, 312, 75, 156 });
	rangedMovingNorthWest.speed = 500.0f;


	//Moving RightFront
	rangedMovingSouthEast.PushBack({ 0, 468, 75, 156 });
	rangedMovingSouthEast.PushBack({ 79, 468, 75, 156 });
	rangedMovingSouthEast.PushBack({ 158, 468, 75, 156 });
	rangedMovingSouthEast.PushBack({ 233, 468, 75, 156 });
	rangedMovingSouthEast.PushBack({ 312, 468, 75, 156 });
	rangedMovingSouthEast.PushBack({ 391, 468, 75, 156 });
	rangedMovingSouthEast.speed = 500.0f;

	//Moving LeftFront
	rangedMovingSouthWest.PushBack({ 470, 468, 75, 156 });
	rangedMovingSouthWest.PushBack({ 549, 468, 75, 156 });
	rangedMovingSouthWest.PushBack({ 628, 468, 75, 156 });
	rangedMovingSouthWest.PushBack({ 707, 468, 75, 156 });
	rangedMovingSouthWest.PushBack({ 786, 468, 75, 156 });
	rangedMovingSouthWest.PushBack({ 865, 468, 75, 156 });
	rangedMovingSouthWest.speed = 500.0f;

	//Moving Back
	rangedMovingNorth.PushBack({ 0, 624, 75, 156 });
	rangedMovingNorth.PushBack({ 79, 624, 75, 156 });
	rangedMovingNorth.PushBack({ 158, 624, 75, 156 });
	rangedMovingNorth.PushBack({ 233, 624, 75, 156 });
	rangedMovingNorth.PushBack({ 312, 624, 75, 156 });
	rangedMovingNorth.PushBack({ 391, 624, 75, 156 });
	rangedMovingNorth.speed = 500.0f;

	//Moving Front
	rangedMovingSouth.PushBack({ 470, 624, 75, 156 });
	rangedMovingSouth.PushBack({ 549, 624, 75, 156 });
	rangedMovingSouth.PushBack({ 628, 624, 75, 156 });
	rangedMovingSouth.PushBack({ 707, 624, 75, 156 });
	rangedMovingSouth.PushBack({ 786, 624, 75, 156 });
	rangedMovingSouth.PushBack({ 865, 624, 75, 156 });
	rangedMovingSouth.speed = 500.0f;
}
