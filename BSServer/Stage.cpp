#include "Stage.h"
#include "Player.h"
Stage::Stage(GameObject* parent)
	: GameObject(parent, "Stage")
{
}

void Stage::Initialize()
{
	transform_.position_.x = 100;
	transform_.position_.y = 100;
	width_ = 1200;
	height_ = 680;
}

void Stage::Update()
{
	Cr = GetColor(255, 0, 0);

}

void Stage::Draw()
{

	DrawBox(transform_.position_.x,transform_.position_.y , width_, height_, Cr, FALSE);
	//DrawOval(640, 360, 550, 350, Cr, FALSE);

}

void Stage::Release()
{
}

bool Stage::IsRectIntersectsOtherRect(float x, float y, float w, float h)
{
	float sx = transform_.position_.x;
	float sy = transform_.position_.y;

	if (x <= sx)
	{
		return true;
	}
	else if (x + w >= sx + width_)
		return true;
	if (y <= sy)
	{
		return true;
	}
	else if (y + h >= sy + height_)
		return true;
	
	return false;
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

