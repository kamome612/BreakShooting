#include "Stage.h"
#include "Player.h"
#include "Bullet.h"
#include "Block.h"
#include <vector>
std::vector<Block*> hBlock;
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


	for (int i = 0; i < 15; i++)
	{
		Block* pBlock = Instantiate<Block>(GetParent());
		pBlock->SetPosition({ (float)180 + (60 * i) + 10,(float)390,(float)0 });
		hBlock.push_back(pBlock);
	}
}

void Stage::Update()
{
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
	//for (int i = 0; i < count; i++)
	//{
	//	//DrawBoxAA(180 + (60 * i) + 10, 390, 180 + (60 * i) + 61, 410, Bcr, FALSE);
	//	Block* pBlock = Instantiate<Block>(this);
	//	pBlock->SetPosition({(float)180 + (60 * i) + 10,(float) 390,(float)0 });
	//}

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

