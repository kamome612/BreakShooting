#include "Stage.h"
#include "Player.h"
Stage::Stage(GameObject* parent)
	: GameObject(parent, "Stage")
{
}

void Stage::Initialize()
{

}

void Stage::Update()
{
	Cr = GetColor(255, 0, 0);

}

void Stage::Draw()
{

	DrawBox(100, 100, 1200, 680, Cr, FALSE);
	//DrawOval(640, 360, 550, 350, Cr, FALSE);

}

void Stage::Release()
{
}

//bool Stage::CollideCircle(float x, float y, float r) 
//{
//	//x,y,r‚ª‘Šè‚Ì‰~‚Ìî•ñ
//	//©•ª‚Ì‰~‚Ìî•ñ
//	float myCenterX = 320;
//	float myCenterY = 180;
//	float myR = 50.0f;
//	float dx = myCenterX - x;
//	float dy = myCenterY - y;
//	if ((dx * dx + dy * dy) < ((r + myR) * (r + myR))) {
//		return true;
//	}
//	else {
//		return false;
//	}
//}

