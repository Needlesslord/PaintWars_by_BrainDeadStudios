#pragma once

#include "animation.h"

//WARRIOR
Animation warrior_idle_Left;
Animation warrior_idle_LeftBack;
Animation warrior_idle_Back;
Animation warrior_idle_RightBack;
Animation warrior_idle_Right;
Animation warrior_idle_RightFront;
Animation warrior_idle_Front;
Animation warrior_idle_LeftFront;

Animation warrior_moving_Left;
Animation warrior_moving_LeftBack;
Animation warrior_moving_Back;
Animation warrior_moving_RightBack;
Animation warrior_moving_Right;
Animation warrior_moving_RightFront;
Animation warrior_moving_Front;
Animation warrior_moving_LeftFront;

void WarriorSprites()
{
	//Idle Right
	warrior_idle_Right.PushBack({ 0, 0, 125, 244 });
	warrior_idle_Right.PushBack({ 125, 0, 125, 244 });
	warrior_idle_Right.speed = 0.08f;

	//Idle RightBack
	warrior_idle_RightBack.PushBack({ 250, 0, 125, 244 });
	warrior_idle_RightBack.PushBack({ 375, 0, 125, 244 });
	warrior_idle_RightBack.speed = 0.08f;

	//Idle Back
	warrior_idle_Back.PushBack({ 500, 0, 125, 244 });
	warrior_idle_Back.PushBack({ 625, 0, 125, 244 });
	warrior_idle_Back.speed = 0.08f;

	//Idle LeftBack
	warrior_idle_LeftBack.PushBack({ 750, 0, 125, 244 });
	warrior_idle_LeftBack.PushBack({ 875, 0, 125, 244 });
	warrior_idle_LeftBack.speed = 0.08f;

	//Idle Left
	warrior_idle_Left.PushBack({ 1000, 0, 125, 244 });
	warrior_idle_Left.PushBack({ 1125, 0, 125, 244 });
	warrior_idle_Left.speed = 0.08f;

	//Idle LeftFront
	warrior_idle_LeftFront.PushBack({ 1250, 0, 125, 244 });
	warrior_idle_LeftFront.PushBack({ 1375, 0, 125, 244 });
	warrior_idle_LeftFront.speed = 0.08f;

	//Idle Front
	warrior_idle_Front.PushBack({ 1500, 0, 125, 244 });
	warrior_idle_Front.PushBack({ 1625, 0, 125, 244 });
	warrior_idle_Front.speed = 0.08f;

	//Idle RightFront
	warrior_idle_RightFront.PushBack({ 1750, 0, 125, 244 });
	warrior_idle_RightFront.PushBack({ 1875, 0, 125, 244 });
	warrior_idle_RightFront.speed = 0.08f;

	//MOVING

	//Moving Right
	warrior_moving_Right.PushBack({ 0, 244, 125, 244 });
	warrior_moving_Right.PushBack({ 125, 244, 125, 244 });
	warrior_moving_Right.PushBack({ 250, 244, 125, 244 });
	warrior_moving_Right.PushBack({ 375, 244, 125, 244 });
	warrior_moving_Right.PushBack({ 500, 244, 125, 244 });
	warrior_moving_Right.PushBack({ 625, 244, 125, 244 });
	warrior_moving_Right.speed = 0.08f;

	//Moving Left
	warrior_moving_Left.PushBack({ 750, 244, 125, 244 });
	warrior_moving_Left.PushBack({ 875, 244, 125, 244 });
	warrior_moving_Left.PushBack({ 1000, 244, 125, 244 });
	warrior_moving_Left.PushBack({ 1125, 244, 125, 244 });
	warrior_moving_Left.PushBack({ 1250, 244, 125, 244 });
	warrior_moving_Left.PushBack({ 1375, 244, 125, 244 });
	warrior_moving_Left.speed = 0.08f;

	//Moving RightBack
	warrior_moving_RightBack.PushBack({ 0, 488, 125, 244 });
	warrior_moving_RightBack.PushBack({ 125, 488, 125, 244 });
	warrior_moving_RightBack.PushBack({ 250, 488, 125, 244 });
	warrior_moving_RightBack.PushBack({ 375, 488, 125, 244 });
	warrior_moving_RightBack.PushBack({ 500, 488, 125, 244 });
	warrior_moving_RightBack.PushBack({ 625, 488, 125, 244 });
	warrior_moving_RightBack.speed = 0.08f;

	//Moving LeftBack
	warrior_moving_LeftBack.PushBack({ 750, 488, 125, 244 });
	warrior_moving_LeftBack.PushBack({ 875, 488, 125, 244 });
	warrior_moving_LeftBack.PushBack({ 1000, 488, 125, 244 });
	warrior_moving_LeftBack.PushBack({ 1125, 488, 125, 244 });
	warrior_moving_LeftBack.PushBack({ 1250, 488, 125, 244 });
	warrior_moving_LeftBack.PushBack({ 1375, 488, 125, 244 });
	warrior_moving_LeftBack.speed = 0.08f;


	//Moving RightFront
	warrior_moving_RightFront.PushBack({ 0, 732, 125, 244 });
	warrior_moving_RightFront.PushBack({ 125, 732, 125, 244 });
	warrior_moving_RightFront.PushBack({ 250, 732, 125, 244 });
	warrior_moving_RightFront.PushBack({ 375, 732, 125, 244 });
	warrior_moving_RightFront.PushBack({ 500, 732, 125, 244 });
	warrior_moving_RightFront.PushBack({ 625, 732, 125, 244 });
	warrior_moving_RightFront.speed = 0.08f;

	//Moving LeftFront
	warrior_moving_LeftFront.PushBack({ 750, 732, 125, 244 });
	warrior_moving_LeftFront.PushBack({ 875, 732, 125, 244 });
	warrior_moving_LeftFront.PushBack({ 1000, 732, 125, 244 });
	warrior_moving_LeftFront.PushBack({ 1125, 732, 125, 244 });
	warrior_moving_LeftFront.PushBack({ 1250, 732, 125, 244 });
	warrior_moving_LeftFront.PushBack({ 1375, 732, 125, 244 });
	warrior_moving_LeftFront.speed = 0.08f;

	//Moving Back
	warrior_moving_Back.PushBack({ 0, 976, 125, 244 });
	warrior_moving_Back.PushBack({ 125, 976, 125, 244 });
	warrior_moving_Back.PushBack({ 250, 976, 125, 244 });
	warrior_moving_Back.PushBack({ 375, 976, 125, 244 });
	warrior_moving_Back.PushBack({ 500, 976, 125, 244 });
	warrior_moving_Back.PushBack({ 625, 976, 125, 244 });
	warrior_moving_Back.speed = 0.08f;

	//Moving Front
	warrior_moving_Front.PushBack({ 750, 976, 125, 244 });
	warrior_moving_Front.PushBack({ 875, 976, 125, 244 });
	warrior_moving_Front.PushBack({ 1000, 976, 125, 244 });
	warrior_moving_Front.PushBack({ 1125, 976, 125, 244 });
	warrior_moving_Front.PushBack({ 1250, 976, 125, 244 });
	warrior_moving_Front.PushBack({ 1375, 976, 125, 244 });
	warrior_moving_Front.speed = 0.08f;
}
	


//PAINTER
Animation painter_idle_Left;
Animation painter_idle_LeftBack;
Animation painter_idle_Back;
Animation painter_idle_RightBack;
Animation painter_idle_Right;
Animation painter_idle_RightFront;
Animation painter_idle_Front;
Animation painter_idle_LeftFront;

Animation painter_moving_Left;
Animation painter_moving_LeftBack;
Animation painter_moving_Back;
Animation painter_moving_RightBack;
Animation painter_moving_Right;
Animation painter_moving_RightFront;
Animation painter_moving_Front;
Animation painter_moving_LeftFront;

void PainterSprites()
{
	//Idle Right
	painter_idle_Right.PushBack({ 0, 0, 106, 222 });
	painter_idle_Right.PushBack({ 106, 0, 106, 222 });
	painter_idle_Right.speed = 0.08f;

	//Idle RightBack
	painter_idle_RightBack.PushBack({ 212, 0, 106, 222 });
	painter_idle_RightBack.PushBack({ 318, 0, 106, 222 });
	painter_idle_RightBack.speed = 0.08f;

	//Idle Back
	painter_idle_Back.PushBack({ 424, 0, 106, 222 });
	painter_idle_Back.PushBack({ 530, 0, 106, 222 });
	painter_idle_Back.speed = 0.08f;

	//Idle LeftBack
	painter_idle_LeftBack.PushBack({ 636, 0, 106, 222 });
	painter_idle_LeftBack.PushBack({ 742, 0, 106, 222 });
	painter_idle_LeftBack.speed = 0.08f;

	//Idle Left
	painter_idle_Left.PushBack({ 848, 0, 106, 222 });
	painter_idle_Left.PushBack({ 954, 0, 106, 222 });
	painter_idle_Left.speed = 0.08f;

	//Idle LeftFront
	painter_idle_LeftFront.PushBack({ 1060, 0, 106, 222 });
	painter_idle_LeftFront.PushBack({ 1166, 0, 106, 222 });
	painter_idle_LeftFront.speed = 0.08f;

	//Idle Front
	painter_idle_Front.PushBack({ 1272, 0, 106, 222 });
	painter_idle_Front.PushBack({ 1378, 0, 106, 222 });
	painter_idle_Front.speed = 0.08f;

	//Idle RightFront
	painter_idle_RightFront.PushBack({ 1484, 0, 106, 222 });
	painter_idle_RightFront.PushBack({ 1590, 0, 106, 222 });
	painter_idle_RightFront.speed = 0.08f;

	//MOVING

	//Moving Right
	painter_moving_Right.PushBack({ 0, 222, 106, 222 });
	painter_moving_Right.PushBack({ 106, 222, 106, 222 });
	painter_moving_Right.PushBack({ 212, 222, 106, 222 });
	painter_moving_Right.PushBack({ 318, 222, 106, 222 });
	painter_moving_Right.PushBack({ 424, 222, 106, 222 });
	painter_moving_Right.PushBack({ 530, 222, 106, 222 });
	painter_moving_Right.speed = 0.08f;

	//Moving Left
	painter_moving_Left.PushBack({ 636, 222, 106, 222 });
	painter_moving_Left.PushBack({ 742, 222, 106, 222 });
	painter_moving_Left.PushBack({ 848, 222, 106, 222 });
	painter_moving_Left.PushBack({ 954, 222, 106, 222 });
	painter_moving_Left.PushBack({ 1060, 222, 106, 222 });
	painter_moving_Left.PushBack({ 1166, 222, 106, 222 });
	painter_moving_Left.speed = 0.08f;

	//Moving RightBack
	painter_moving_RightBack.PushBack({ 0, 444, 106, 222 });
	painter_moving_RightBack.PushBack({ 106, 444, 106, 222 });
	painter_moving_RightBack.PushBack({ 212, 444, 106, 222 });
	painter_moving_RightBack.PushBack({ 318, 444, 106, 222 });
	painter_moving_RightBack.PushBack({ 424, 444, 106, 222 });
	painter_moving_RightBack.PushBack({ 530, 444, 106, 222 });
	painter_moving_RightBack.speed = 0.08f;

	//Moving LeftBack
	painter_moving_LeftBack.PushBack({ 636, 444, 106, 222 });
	painter_moving_LeftBack.PushBack({ 742, 444, 106, 222 });
	painter_moving_LeftBack.PushBack({ 848, 444, 106, 222 });
	painter_moving_LeftBack.PushBack({ 954, 444, 106, 222 });
	painter_moving_LeftBack.PushBack({ 1060, 444, 106, 222 });
	painter_moving_LeftBack.PushBack({ 1166, 444, 106, 222 });
	painter_moving_LeftBack.speed = 0.08f;


	//Moving RightFront
	painter_moving_RightFront.PushBack({ 0, 666, 106, 222 });
	painter_moving_RightFront.PushBack({ 106, 666, 106, 222 });
	painter_moving_RightFront.PushBack({ 212, 666, 106, 222 });
	painter_moving_RightFront.PushBack({ 318, 666, 106, 222 });
	painter_moving_RightFront.PushBack({ 424, 666, 106, 222 });
	painter_moving_RightFront.PushBack({ 530, 666, 106, 222 });
	painter_moving_RightFront.speed = 0.08f;

	//Moving LeftFront
	painter_moving_LeftFront.PushBack({ 636, 666, 106, 222 });
	painter_moving_LeftFront.PushBack({ 742, 666, 106, 222 });
	painter_moving_LeftFront.PushBack({ 848, 666, 106, 222 });
	painter_moving_LeftFront.PushBack({ 954, 666, 106, 222 });
	painter_moving_LeftFront.PushBack({ 1060, 666, 106, 222 });
	painter_moving_LeftFront.PushBack({ 1166, 666, 106, 222 });
	painter_moving_LeftFront.speed = 0.08f;

	//Moving Back
	painter_moving_Back.PushBack({ 0, 888, 106, 222 });
	painter_moving_Back.PushBack({ 106, 888, 106, 222 });
	painter_moving_Back.PushBack({ 212, 888, 106, 222 });
	painter_moving_Back.PushBack({ 318, 888, 106, 222 });
	painter_moving_Back.PushBack({ 424, 888, 106, 222 });
	painter_moving_Back.PushBack({ 530, 888, 106, 222 });
	painter_moving_Back.speed = 0.08f;

	//Moving Front
	painter_moving_Front.PushBack({ 636, 888, 106, 222 });
	painter_moving_Front.PushBack({ 742, 888, 106, 222 });
	painter_moving_Front.PushBack({ 848, 888, 106, 222 });
	painter_moving_Front.PushBack({ 954, 888, 106, 222 });
	painter_moving_Front.PushBack({ 1060, 888, 106, 222 });
	painter_moving_Front.PushBack({ 1166, 888, 106, 222 });
	painter_moving_Front.speed = 0.08f;
}
