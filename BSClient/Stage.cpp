#include "Stage.h"
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
	//DrawOval(640, 360,Å@550,Å@350, Cr, FALSE);
	
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
