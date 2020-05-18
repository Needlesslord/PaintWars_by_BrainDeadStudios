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

Animation warriorDeath;


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

	//DEATH
	warriorDeath.PushBack({ 0, 1064, 89, 152 });
	warriorDeath.PushBack({ 89, 1064, 89, 152 });
	warriorDeath.PushBack({ 178, 1064, 89, 152 });
	warriorDeath.PushBack({ 267, 1064, 89, 152 });
	warriorDeath.PushBack({ 356, 1064, 89, 152 });
	warriorDeath.speed = 500.0f;
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

Animation painterRecollection;

Animation painterDeath;

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

	//RECOLLECTION
	painterRecollection.PushBack({ 1275, 0, 103, 156 });
	painterRecollection.PushBack({ 1378, 0, 103, 156 });
	painterRecollection.PushBack({ 1481, 0, 103, 156 });
	painterRecollection.speed = 500.0f;

	//DEATH
	painterDeath.PushBack({ 0, 780, 76, 156 });
	painterDeath.PushBack({ 76, 780, 76, 156 });
	painterDeath.PushBack({ 152, 780, 76, 156 });
	painterDeath.PushBack({ 228, 780, 76, 156 });
	painterDeath.PushBack({ 304, 780, 76, 156 });
	painterDeath.speed = 500.0f;
}

//KNIGHT

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

Animation knightDeath;


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

	//DEATH
	knightDeath.PushBack({ 0, 1555, 88, 151 });
	knightDeath.PushBack({ 88, 1555, 88, 151 });
	knightDeath.PushBack({ 176, 1555, 88, 151 });
	knightDeath.PushBack({ 264, 1555, 88, 151 });
	knightDeath.PushBack({ 352, 1555, 88, 151 });
	knightDeath.speed = 500.0f;
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

Animation explorerDeath;

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

	explorerDeath.PushBack({ 0, 780, 75, 156 });
	explorerDeath.PushBack({ 75, 780, 75, 156 });
	explorerDeath.PushBack({ 150, 780, 75, 156 });
	explorerDeath.PushBack({ 225, 780, 75, 156 });
	explorerDeath.PushBack({ 300, 780, 75, 156 });
	explorerDeath.speed = 500.0f;
}

//RANGED
Animation rangerIdle;

Animation rangerMovingWest;
Animation rangerMovingNorthWest;
Animation rangerMovingNorth;
Animation rangerMovingNorthEast;
Animation rangerMovingEast;
Animation rangerMovingSouthEast;
Animation rangerMovingSouth;
Animation rangerMovingSouthWest;

Animation rangerAttackWest;
Animation rangerAttackNorthWest;
Animation rangerAttackNorth;
Animation rangerAttackNorthEast;
Animation rangerAttackEast;
Animation rangerAttackSouthEast;
Animation rangerAttackSouth;
Animation rangerAttackSouthWest;

Animation rangerDeath;

void RangerSprites()
{
	//Idle 
	rangerIdle.PushBack({ 948, 0, 75, 156 });
	rangerIdle.PushBack({ 1027, 0, 75, 156 });
	rangerIdle.speed = 50.0f;

	//MOVING

	//Moving Right
	rangerMovingEast.PushBack({ 0, 156, 75, 156 });
	rangerMovingEast.PushBack({ 79, 156, 75, 156 });
	rangerMovingEast.PushBack({ 158, 156, 75, 156 });
	rangerMovingEast.PushBack({ 233, 156, 75, 156 });
	rangerMovingEast.PushBack({ 312, 156, 75, 156 });
	rangerMovingEast.PushBack({ 391, 156, 75, 156 });
	rangerMovingEast.speed = 500.0f;

	//Moving Left
	rangerMovingWest.PushBack({ 470, 156, 75, 156 });
	rangerMovingWest.PushBack({ 549, 156, 75, 156 });
	rangerMovingWest.PushBack({ 628, 156, 75, 156 });
	rangerMovingWest.PushBack({ 707, 156, 75, 156 });
	rangerMovingWest.PushBack({ 786, 156, 75, 156 });
	rangerMovingWest.PushBack({ 865, 156, 75, 156 });
	rangerMovingWest.speed = 500.0f;

	//Moving RightBack
	rangerMovingNorthEast.PushBack({ 0, 312, 75, 156 });
	rangerMovingNorthEast.PushBack({ 79, 312, 75, 156 });
	rangerMovingNorthEast.PushBack({ 158, 312, 75, 156 });
	rangerMovingNorthEast.PushBack({ 233, 312, 75, 156 });
	rangerMovingNorthEast.PushBack({ 312, 312, 75, 156 });
	rangerMovingNorthEast.PushBack({ 391, 312, 75, 156 });
	rangerMovingNorthEast.speed = 500.0f;

	//Moving LeftBack
	rangerMovingNorthWest.PushBack({ 470, 312, 75, 156 });
	rangerMovingNorthWest.PushBack({ 549, 312, 75, 156 });
	rangerMovingNorthWest.PushBack({ 628, 312, 75, 156 });
	rangerMovingNorthWest.PushBack({ 707, 312, 75, 156 });
	rangerMovingNorthWest.PushBack({ 786, 312, 75, 156 });
	rangerMovingNorthWest.PushBack({ 865, 312, 75, 156 });
	rangerMovingNorthWest.speed = 500.0f;


	//Moving RightFront
	rangerMovingSouthEast.PushBack({ 0, 468, 75, 156 });
	rangerMovingSouthEast.PushBack({ 79, 468, 75, 156 });
	rangerMovingSouthEast.PushBack({ 158, 468, 75, 156 });
	rangerMovingSouthEast.PushBack({ 233, 468, 75, 156 });
	rangerMovingSouthEast.PushBack({ 312, 468, 75, 156 });
	rangerMovingSouthEast.PushBack({ 391, 468, 75, 156 });
	rangerMovingSouthEast.speed = 500.0f;

	//Moving LeftFront
	rangerMovingSouthWest.PushBack({ 470, 468, 75, 156 });
	rangerMovingSouthWest.PushBack({ 549, 468, 75, 156 });
	rangerMovingSouthWest.PushBack({ 628, 468, 75, 156 });
	rangerMovingSouthWest.PushBack({ 707, 468, 75, 156 });
	rangerMovingSouthWest.PushBack({ 786, 468, 75, 156 });
	rangerMovingSouthWest.PushBack({ 865, 468, 75, 156 });
	rangerMovingSouthWest.speed = 500.0f;

	//Moving Back
	rangerMovingNorth.PushBack({ 0, 624, 75, 156 });
	rangerMovingNorth.PushBack({ 79, 624, 75, 156 });
	rangerMovingNorth.PushBack({ 158, 624, 75, 156 });
	rangerMovingNorth.PushBack({ 233, 624, 75, 156 });
	rangerMovingNorth.PushBack({ 312, 624, 75, 156 });
	rangerMovingNorth.PushBack({ 391, 624, 75, 156 });
	rangerMovingNorth.speed = 500.0f;

	//Moving Front
	rangerMovingSouth.PushBack({ 470, 624, 75, 156 });
	rangerMovingSouth.PushBack({ 549, 624, 75, 156 });
	rangerMovingSouth.PushBack({ 628, 624, 75, 156 });
	rangerMovingSouth.PushBack({ 707, 624, 75, 156 });
	rangerMovingSouth.PushBack({ 786, 624, 75, 156 });
	rangerMovingSouth.PushBack({ 865, 624, 75, 156 });
	rangerMovingSouth.speed = 500.0f;


	//ATTACK

	//Attack East
	rangerAttackEast.PushBack({ 0, 780, 93, 156 });
	rangerAttackEast.PushBack({ 93, 780, 93, 156 });
	rangerAttackEast.PushBack({ 186, 780, 93, 156 });
	rangerAttackEast.speed = 250.0f;

	//Attack SouthEast
	rangerAttackSouthEast.PushBack({ 0, 1092, 93, 156 });
	rangerAttackSouthEast.PushBack({ 93, 1092, 93, 156 });
	rangerAttackSouthEast.PushBack({ 186, 1092, 93, 156 });
	rangerAttackSouthEast.speed = 250.0f;

	//Attack South
	rangerAttackSouth.PushBack({ 372, 1248, 93, 156 });
	rangerAttackSouth.PushBack({ 465, 1248, 93, 156 });
	rangerAttackSouth.PushBack({ 558, 1248, 93, 156 });
	rangerAttackSouth.speed = 250.0f;

	//Attack SouthWest
	rangerAttackSouthWest.PushBack({ 372, 1092, 93, 156 });
	rangerAttackSouthWest.PushBack({ 465, 1092, 93, 156 });
	rangerAttackSouthWest.PushBack({ 558, 1092, 93, 156 });
	rangerAttackSouthWest.speed = 250.0f;

	//Attack West
	rangerAttackWest.PushBack({ 372, 780, 93, 156 });
	rangerAttackWest.PushBack({ 465, 780, 93, 156 });
	rangerAttackWest.PushBack({ 558, 780, 93, 156 });
	rangerAttackWest.speed = 250.0f;

	//Attack NorthWest
	rangerAttackNorthWest.PushBack({ 372, 936, 93, 156 });
	rangerAttackNorthWest.PushBack({ 465, 936, 93, 156 });
	rangerAttackNorthWest.PushBack({ 558, 936, 93, 156 });
	rangerAttackNorthWest.speed = 250.0f;

	//Attack North
	rangerAttackNorth.PushBack({ 0, 1248, 93, 156 });
	rangerAttackNorth.PushBack({ 93, 1248, 93, 156 });
	rangerAttackNorth.PushBack({ 186, 1248, 93, 156 });
	rangerAttackNorth.speed = 250.0f;

	//Attack NorthEast
	rangerAttackNorthEast.PushBack({ 0, 936, 93, 156 });
	rangerAttackNorthEast.PushBack({ 93, 936, 93, 156 });
	rangerAttackNorthEast.PushBack({ 186, 936, 93, 156 });
	rangerAttackNorthEast.speed = 250.0f;


	//DEATH
	rangerDeath.PushBack({ 0, 1404, 93, 156 });
	rangerDeath.PushBack({ 93, 1404, 93, 156 });
	rangerDeath.PushBack({ 186, 1404, 93, 156 });
	rangerDeath.PushBack({ 279, 1404, 93, 156 });
	rangerDeath.PushBack({ 372, 1404, 93, 156 });
	rangerDeath.speed = 500.0f;
}



//ENEMY

//RIDER

Animation riderIdle;
		 
Animation riderMovingWest;
Animation riderMovingNorthWest;
Animation riderMovingNorth;
Animation riderMovingNorthEast;
Animation riderMovingEast;
Animation riderMovingSouthEast;
Animation riderMovingSouth;
Animation riderMovingSouthWest;
	
Animation riderAttackWest;
Animation riderAttackNorthWest;
Animation riderAttackNorth;
Animation riderAttackNorthEast;
Animation riderAttackEast;
Animation riderAttackSouthEast;
Animation riderAttackSouth;
Animation riderAttackSouthWest;

Animation riderDeath;


void RiderSprites()
{
	//Idle 
	riderIdle.PushBack({ 1068, 0, 89, 152 });
	riderIdle.PushBack({ 1157, 0, 89, 152 });
	riderIdle.speed = 50.0f;

	//MOVING

	//Moving Right
	riderMovingEast.PushBack({ 0, 152, 89, 152 });
	riderMovingEast.PushBack({ 89, 152, 89, 152 });
	riderMovingEast.PushBack({ 178, 152, 89, 152 });
	riderMovingEast.PushBack({ 267, 152, 89, 152 });
	riderMovingEast.PushBack({ 356, 152, 89, 152 });
	riderMovingEast.PushBack({ 445, 152, 89, 152 });
	riderMovingEast.speed = 500.0f;

	//Moving Left
	riderMovingWest.PushBack({ 534, 152, 89, 152 });
	riderMovingWest.PushBack({ 623, 152, 89, 152 });
	riderMovingWest.PushBack({ 712, 152, 89, 152 });
	riderMovingWest.PushBack({ 801, 152, 89, 152 });
	riderMovingWest.PushBack({ 890, 152, 89, 152 });
	riderMovingWest.PushBack({ 979, 152, 89, 152 });
	riderMovingWest.speed = 500.0f;

	//Moving RightBack
	riderMovingNorthEast.PushBack({ 0, 304, 89, 152 });
	riderMovingNorthEast.PushBack({ 89, 304, 89, 152 });
	riderMovingNorthEast.PushBack({ 178, 304, 89, 152 });
	riderMovingNorthEast.PushBack({ 267, 304, 89, 152 });
	riderMovingNorthEast.PushBack({ 356, 304, 89, 152 });
	riderMovingNorthEast.PushBack({ 445, 304, 89, 152 });
	riderMovingNorthEast.speed = 500.0f;

	//Moving LeftBack
	riderMovingNorthWest.PushBack({ 534, 304, 89, 152 });
	riderMovingNorthWest.PushBack({ 623, 304, 89, 152 });
	riderMovingNorthWest.PushBack({ 712, 304, 89, 152 });
	riderMovingNorthWest.PushBack({ 801, 304, 89, 152 });
	riderMovingNorthWest.PushBack({ 890, 304, 89, 152 });
	riderMovingNorthWest.PushBack({ 979, 304, 89, 152 });
	riderMovingNorthWest.speed = 500.0f;


	//Moving RightFront
	riderMovingSouthEast.PushBack({ 0, 456, 89, 152 });
	riderMovingSouthEast.PushBack({ 89, 456, 89, 152 });
	riderMovingSouthEast.PushBack({ 178, 456, 89, 152 });
	riderMovingSouthEast.PushBack({ 267, 456, 89, 152 });
	riderMovingSouthEast.PushBack({ 356, 456, 89, 152 });
	riderMovingSouthEast.PushBack({ 445, 456, 89, 152 });
	riderMovingSouthEast.speed = 500.0f;

	//Moving LeftFront
	riderMovingSouthWest.PushBack({ 534, 456, 89, 152 });
	riderMovingSouthWest.PushBack({ 623, 456, 89, 152 });
	riderMovingSouthWest.PushBack({ 712, 456, 89, 152 });
	riderMovingSouthWest.PushBack({ 801, 456, 89, 152 });
	riderMovingSouthWest.PushBack({ 890, 456, 89, 152 });
	riderMovingSouthWest.PushBack({ 979, 456, 89, 152 });
	riderMovingSouthWest.speed = 500.0f;

	//Moving Back
	riderMovingNorth.PushBack({ 0, 608, 89, 152 });
	riderMovingNorth.PushBack({ 89, 608, 89, 152 });
	riderMovingNorth.PushBack({ 178, 608, 89, 152 });
	riderMovingNorth.PushBack({ 267, 608, 89, 152 });
	riderMovingNorth.PushBack({ 356, 608, 89, 152 });
	riderMovingNorth.PushBack({ 445, 608, 89, 152 });
	riderMovingNorth.speed = 500.0f;

	//Moving Front
	riderMovingSouth.PushBack({ 534, 608, 89, 152 });
	riderMovingSouth.PushBack({ 623, 608, 89, 152 });
	riderMovingSouth.PushBack({ 712, 608, 89, 152 });
	riderMovingSouth.PushBack({ 801, 608, 89, 152 });
	riderMovingSouth.PushBack({ 890, 608, 89, 152 });
	riderMovingSouth.PushBack({ 979, 608, 89, 152 });
	riderMovingSouth.speed = 500.0f;

	//ATTACK

	//Attack East
	riderAttackEast.PushBack({ 0, 760, 89, 152 });
	riderAttackEast.PushBack({ 89, 760, 89, 152 });
	riderAttackEast.speed = 250.0f;

	//Attack SouthEast
	riderAttackSouthEast.PushBack({ 178, 760, 89, 152 });
	riderAttackSouthEast.PushBack({ 267, 760, 89, 152 });
	riderAttackSouthEast.speed = 250.0f;

	//Attack South
	riderAttackSouth.PushBack({ 534, 912, 89, 152 });
	riderAttackSouth.PushBack({ 623, 912, 89, 152 });
	riderAttackSouth.speed = 250.0f;

	//Attack SouthWest
	riderAttackSouthWest.PushBack({ 356, 760, 89, 152 });
	riderAttackSouthWest.PushBack({ 445, 760, 89, 152 });
	riderAttackSouthWest.speed = 250.0f;

	//Attack West
	riderAttackWest.PushBack({ 534, 760, 89, 152 });
	riderAttackWest.PushBack({ 623, 760, 89, 152 });
	riderAttackWest.speed = 250.0f;

	//Attack NorthWest
	riderAttackNorthWest.PushBack({ 356, 912, 89, 152 });
	riderAttackNorthWest.PushBack({ 445, 912, 89, 152 });
	riderAttackNorthWest.speed = 250.0f;

	//Attack North
	riderAttackNorth.PushBack({ 178, 912, 89, 152 });
	riderAttackNorth.PushBack({ 267, 912, 89, 152 });
	riderAttackNorth.speed = 250.0f;

	//Attack NorthEast
	riderAttackNorthEast.PushBack({ 0, 912, 89, 152 });
	riderAttackNorthEast.PushBack({ 89, 912, 89, 152 });
	riderAttackNorthEast.speed = 250.0f;

	//DEATH
	riderDeath.PushBack({ 0, 1064, 89, 152 });
	riderDeath.PushBack({ 89, 1064, 89, 152 });
	riderDeath.PushBack({ 178, 1064, 89, 152 });
	riderDeath.PushBack({ 267, 1064, 89, 152 });
	riderDeath.PushBack({ 356, 1064, 89, 152 });
	riderDeath.speed = 500.0f;
}


//SLIME
Animation slimeIdle;
		  
Animation slimeMovingWest;
Animation slimeMovingNorthWest;
Animation slimeMovingNorth;
Animation slimeMovingNorthEast;
Animation slimeMovingEast;
Animation slimeMovingSouthEast;
Animation slimeMovingSouth;
Animation slimeMovingSouthWest;

Animation slimeDeath;

void SlimeSprites()
{
	//Idle 
	slimeIdle.PushBack({ 136, 742, 68, 52 });
	slimeIdle.PushBack({ 204, 742, 68, 52 });
	slimeIdle.speed = 8.0f;

	//MOVING

	//Moving Right
	slimeMovingEast.PushBack({ 0, 0, 68, 52 });
	slimeMovingEast.PushBack({ 68, 0, 68, 52 });
	slimeMovingEast.PushBack({ 136, 0, 68, 52 });
	slimeMovingEast.PushBack({ 204, 0, 68, 52 });
	slimeMovingEast.speed = 500.0f;

	//Moving Left
	slimeMovingWest.PushBack({ 272, 0, 68, 52 });
	slimeMovingWest.PushBack({ 340, 0, 68, 52 });
	slimeMovingWest.PushBack({ 408, 0, 68, 52 });
	slimeMovingWest.PushBack({ 476, 0, 68, 52 });
	slimeMovingWest.speed = 500.0f;

	//Moving RightBack
	slimeMovingNorthEast.PushBack({ 0, 102, 68, 52 });
	slimeMovingNorthEast.PushBack({ 68, 102, 68, 52 });
	slimeMovingNorthEast.PushBack({ 136, 102, 68, 52 });
	slimeMovingNorthEast.PushBack({ 204, 102, 68, 52 });
	slimeMovingNorthEast.speed = 500.0f; 
										 
	//Moving LeftBack					 
	slimeMovingNorthWest.PushBack({ 272, 102, 68, 52 });
	slimeMovingNorthWest.PushBack({ 340, 102, 68, 52 });
	slimeMovingNorthWest.PushBack({ 408, 102, 68, 52 });
	slimeMovingNorthWest.PushBack({ 476, 102, 68, 52 });
	slimeMovingNorthWest.speed = 500.0f;


	//Moving RightFront
	slimeMovingSouthEast.PushBack({ 0, 208, 68, 52 });
	slimeMovingSouthEast.PushBack({ 68, 208, 68, 52 });
	slimeMovingSouthEast.PushBack({ 136, 208, 68, 52 });
	slimeMovingSouthEast.PushBack({ 204, 208, 68, 52 });
	slimeMovingSouthEast.speed = 500.0f; 
										 
	//Moving LeftFront					 
	slimeMovingSouthWest.PushBack({ 272, 208, 68, 52 });
	slimeMovingSouthWest.PushBack({ 340, 208, 68, 52 });
	slimeMovingSouthWest.PushBack({ 408, 208, 68, 52 });
	slimeMovingSouthWest.PushBack({ 476, 208, 68, 52 });
	slimeMovingSouthWest.speed = 500.0f;

	//Moving Back
	slimeMovingNorth.PushBack({ 0, 318, 68, 52 });
	slimeMovingNorth.PushBack({ 68, 318, 68, 52 });
	slimeMovingNorth.PushBack({ 136, 318, 68, 52 });
	slimeMovingNorth.PushBack({ 204, 318, 68, 52 });
	slimeMovingNorth.speed = 500.0f; 
									 
	//Moving Front					 
	slimeMovingSouth.PushBack({ 272, 318, 68, 52 });
	slimeMovingSouth.PushBack({ 340, 318, 68, 52 });
	slimeMovingSouth.PushBack({ 408, 318, 68, 52 });
	slimeMovingSouth.PushBack({ 476, 318, 68, 52 });
	slimeMovingSouth.speed = 500.0f;

	//DEATH
	slimeDeath.PushBack({ 0, 873, 68, 52 });
	slimeDeath.PushBack({ 68, 873, 68, 52 });
	slimeDeath.PushBack({ 136, 873, 68, 52 });
	slimeDeath.PushBack({ 204, 873, 68, 52 });
	slimeDeath.PushBack({ 272, 873, 68, 52 });
	slimeDeath.speed = 500.0f;
}


//EXPLOSIVE BLOB
Animation explosiveBlobIdle;
		  
Animation explosiveBlobMovingWest;
Animation explosiveBlobMovingNorthWest;
Animation explosiveBlobMovingNorth;
Animation explosiveBlobMovingNorthEast;
Animation explosiveBlobMovingEast;
Animation explosiveBlobMovingSouthEast;
Animation explosiveBlobMovingSouth;
Animation explosiveBlobMovingSouthWest;

Animation explosiveBlobDeath;

void ExplosiveBlobSprites()
{
	//Idle 
	explosiveBlobIdle.PushBack({ 96, 303, 96, 101 });
	explosiveBlobIdle.PushBack({ 192, 303, 96, 101 });
	explosiveBlobIdle.speed = 50.0f;

	//MOVING

	//Moving Right
	explosiveBlobMovingEast.PushBack({ 0, 202, 96, 101 });
	explosiveBlobMovingEast.PushBack({ 96, 202, 96, 101 });
	explosiveBlobMovingEast.PushBack({ 192, 202, 96, 101 });
	explosiveBlobMovingEast.PushBack({ 288, 202, 96, 101 });
	explosiveBlobMovingEast.speed = 500.0f;		 	 
										 	 
	//Moving Left						 	 
	explosiveBlobMovingWest.PushBack({ 384, 202, 96, 101 });
	explosiveBlobMovingWest.PushBack({ 480, 202, 96, 101 });
	explosiveBlobMovingWest.PushBack({ 576, 202, 96, 101 });
	explosiveBlobMovingWest.PushBack({ 672, 202, 96, 101 });
	explosiveBlobMovingWest.speed = 500.0f;

	//Moving RightBack
	explosiveBlobMovingNorthEast.PushBack({ 0, 101, 96, 101 });
	explosiveBlobMovingNorthEast.PushBack({ 96, 101, 96, 101 });
	explosiveBlobMovingNorthEast.PushBack({ 192, 101, 96, 101 });
	explosiveBlobMovingNorthEast.PushBack({ 288, 101, 96, 101 });
	explosiveBlobMovingNorthEast.speed = 500.0f;	  
										  
	//Moving LeftBack					  	  
	explosiveBlobMovingNorthWest.PushBack({ 384, 101, 96, 101 });
	explosiveBlobMovingNorthWest.PushBack({ 480, 101, 96, 101 });
	explosiveBlobMovingNorthWest.PushBack({ 576, 101, 96, 101 });
	explosiveBlobMovingNorthWest.PushBack({ 672, 101, 96, 101 });
	explosiveBlobMovingNorthWest.speed = 500.0f;


	//Moving RightFront
	explosiveBlobMovingSouthEast.PushBack({ 0, 0, 96, 101 });
	explosiveBlobMovingSouthEast.PushBack({ 96, 0, 96, 101 });
	explosiveBlobMovingSouthEast.PushBack({ 192, 0, 96, 101 });
	explosiveBlobMovingSouthEast.PushBack({ 288, 0, 96, 101 });
	explosiveBlobMovingSouthEast.speed = 500.0f;  	  
										  	  
	//Moving LeftFront					  	  
	explosiveBlobMovingSouthWest.PushBack({ 384, 0, 96, 101 });
	explosiveBlobMovingSouthWest.PushBack({ 480, 0, 96, 101 });
	explosiveBlobMovingSouthWest.PushBack({ 576, 0, 96, 101 });
	explosiveBlobMovingSouthWest.PushBack({ 672, 0, 96, 101 });
	explosiveBlobMovingSouthWest.speed = 500.0f;

	//Moving Back
	explosiveBlobMovingNorth.PushBack({ 0, 303, 96, 101 });
	explosiveBlobMovingNorth.PushBack({ 96, 303, 96, 101 });
	explosiveBlobMovingNorth.PushBack({ 192, 303, 96, 101 });
	explosiveBlobMovingNorth.PushBack({ 288, 303, 96, 101 });
	explosiveBlobMovingNorth.speed = 500.0f;  	  
									  	  
	//Moving Front					  	  
	explosiveBlobMovingSouth.PushBack({ 384, 303, 96, 101 });
	explosiveBlobMovingSouth.PushBack({ 480, 303, 96, 101 });
	explosiveBlobMovingSouth.PushBack({ 576, 303, 96, 101 });
	explosiveBlobMovingSouth.PushBack({ 672, 303, 96, 101 });
	explosiveBlobMovingSouth.speed = 500.0f;

	//DEATH
	explosiveBlobDeath.PushBack({ 0, 404, 96, 101 });
	explosiveBlobDeath.PushBack({ 96, 404, 96, 101 });
	explosiveBlobDeath.PushBack({ 192, 404, 96, 101 });
	explosiveBlobDeath.PushBack({ 288, 404, 96, 101 });
	explosiveBlobDeath.PushBack({ 384, 404, 96, 101 });
	explosiveBlobDeath.speed = 500.0f;
}



//CHROMA KING
Animation chromaKingIdle;
		  
Animation chromaKingMovingWest;
Animation chromaKingMovingNorthWest;
Animation chromaKingMovingNorth;
Animation chromaKingMovingNorthEast;
Animation chromaKingMovingEast;
Animation chromaKingMovingSouthEast;
Animation chromaKingMovingSouth;
Animation chromaKingMovingSouthWest;

Animation chromaKingDeath;

void ChromaKingSprites()
{
	//Idle 
	chromaKingIdle.PushBack({ 544, 3027, 272, 221 });
	chromaKingIdle.PushBack({ 816, 3027, 272, 221 });
	chromaKingIdle.speed = 50.0f;

	//MOVING

	//Moving Right
	chromaKingMovingEast.PushBack({ 0, 0, 272, 221 });
	chromaKingMovingEast.PushBack({ 272, 0, 272, 221 });
	chromaKingMovingEast.PushBack({ 544, 0, 272, 221 });
	chromaKingMovingEast.PushBack({ 816, 0, 272, 221 });
	chromaKingMovingEast.speed = 500.0f;		 
												 
	//Moving Left						 	 	 
	chromaKingMovingWest.PushBack({ 1088, 0, 272, 221 });
	chromaKingMovingWest.PushBack({ 1360, 0, 272, 221 });
	chromaKingMovingWest.PushBack({ 1632, 0, 272, 221 });
	chromaKingMovingWest.PushBack({ 1904, 0, 272, 221 });
	chromaKingMovingWest.speed = 500.0f;

	//Moving RightBack
	chromaKingMovingNorthEast.PushBack({ 0, 467, 272, 221 });
	chromaKingMovingNorthEast.PushBack({ 272, 467, 272, 221 });
	chromaKingMovingNorthEast.PushBack({ 544, 467, 272, 221 });
	chromaKingMovingNorthEast.PushBack({ 816, 467, 272, 221 });
	chromaKingMovingNorthEast.speed = 500.0f;	   
												   
	//Moving LeftBack					  	  	   
	chromaKingMovingNorthWest.PushBack({ 1088, 467, 272, 221 });
	chromaKingMovingNorthWest.PushBack({ 1360, 467, 272, 221 });
	chromaKingMovingNorthWest.PushBack({ 1632, 467, 272, 221 });
	chromaKingMovingNorthWest.PushBack({ 1904, 467, 272, 221 });
	chromaKingMovingNorthWest.speed = 500.0f;


	//Moving RightFront
	chromaKingMovingSouthWest.PushBack({ 0, 891, 272, 221 });
	chromaKingMovingSouthWest.PushBack({ 272, 891, 272, 221 });
	chromaKingMovingSouthWest.PushBack({ 544, 891, 272, 221 });
	chromaKingMovingSouthWest.PushBack({ 816, 891, 272, 221 });
	chromaKingMovingSouthWest.speed = 500.0f;

	//Moving LeftFront					  	  
	chromaKingMovingSouthWest.PushBack({ 1088, 891, 272, 221 });
	chromaKingMovingSouthWest.PushBack({ 1360, 891, 272, 221 });
	chromaKingMovingSouthWest.PushBack({ 1632, 891, 272, 221 });
	chromaKingMovingSouthWest.PushBack({ 1904, 891, 272, 221 });
	chromaKingMovingSouthWest.speed = 500.0f;

	//Moving Back
	chromaKingMovingNorth.PushBack({ 0, 1332, 272, 221 });
	chromaKingMovingNorth.PushBack({ 272, 1332, 272, 221 });
	chromaKingMovingNorth.PushBack({ 544, 1332, 272, 221 });
	chromaKingMovingNorth.PushBack({ 816, 1332, 272, 221 });
	chromaKingMovingNorth.speed = 500.0f;

	//Moving Front					  	  
	chromaKingMovingSouth.PushBack({ 1088, 1332, 272, 221 });
	chromaKingMovingSouth.PushBack({ 1360, 1332, 272, 221 });
	chromaKingMovingSouth.PushBack({ 1632, 1332, 272, 221 });
	chromaKingMovingSouth.PushBack({ 1904, 1332, 272, 221 });
	chromaKingMovingSouth.speed = 500.0f;

	//DEATH
	chromaKingDeath.PushBack({ 0, 3349, 272, 221 });
	chromaKingDeath.PushBack({ 272, 3349, 272, 221 });
	chromaKingDeath.PushBack({ 544, 3349, 272, 221 });
	chromaKingDeath.PushBack({ 816, 3349, 272, 221 });
	chromaKingDeath.PushBack({ 1088, 3349, 272, 221 });
	chromaKingDeath.speed = 500.0f;
}

