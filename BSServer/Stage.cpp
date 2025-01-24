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


	DrawOval(640, 360, 550, 350, Cr, FALSE);

}

void Stage::Release()
{
}

//bool Stage::CollideCircle(float x, float y, float r) 
//{
//	//x,y,rが相手の円の情報
//	//自分の円の情報
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

