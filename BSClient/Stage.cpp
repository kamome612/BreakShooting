#include "Stage.h"
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
	//↓外枠の壁
	Cr = GetColor(255, 0, 0);
	Bcr = GetColor(255, 255, 255);
}

void Stage::Draw()
{
	int Linelength = 60;
	int LineHeight = 400;
	int xSStart = 170;
	int count = 15;
	int Hcount = 3;
	//↓ステージの外枠
	DrawBoxAA(100, 100, 1200, 680, Cr, FALSE);
	DrawBoxAA(101, 101, 1201, 681, Cr, FALSE);
	
	//↓ステージを分断する破壊できる壁
	for (int i = 0; i < count; i++)
	{
		DrawBoxAA(170 + (60 * i) + 10, 390, 170 + (60 * i) + 61, 410, Bcr, FALSE);
	}
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
