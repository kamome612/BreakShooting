#include "Block.h"
#include "Engine/time.h"

namespace
{
	const float LimitTime_ = 3.0f;
}
Block::Block(GameObject* parent)
	:GameObject(parent, "Block"), BlockTime_(0), isDead(false)
{
}

void Block::Initialize()
{
	Bc = GetColor(255, 255, 255);
}

void Block::Update()
{
	if (isDead == true)
	{
		BlockTime_ += Time::DeltaTime();
	}
	if (BlockTime_ >= LimitTime_)
	{
		BlockTime_ = 0;
		isDead = false;
	}

}

void Block::Draw()
{
	float x = transform_.position_.x;
	float y = transform_.position_.y;

	//if (BlockTime_ > LimitTime_)
	//{
	//	DrawBoxAA(x, y, x + width_ + 1, y + height_ + 1, Bc, TRUE);
	//}
	//if (isDead == false)
	//{
	//	
	//}
	if (!isDead)
		DrawBoxAA(x, y, x + width_ + 1, y + height_ + 1, Bc, TRUE);
}

void Block::Release()
{
}
bool Block::BulletCollistion(float bx, float by, float br)
{
	if (!isDead)
	{


		float x = transform_.position_.x - 30;
		float y = transform_.position_.y;
		//isDead = true;

		float nearX, nearY;

		// ‰~‚Ì“–‚½‚è”»’è
		if (bx < x) {
			nearX = x;
		}
		else if (bx > x + width_) {
			nearX = x + width_;
		}
		else {
			nearX = bx;
		}

		if (by < y) {
			nearY = y;
		}
		else if (by > y + height_) {
			nearY = y + height_;
		}
		else {
			nearY = by;
		}

		float dx = bx - nearX;
		float dy = by - nearY;

		if ((dx * dx + dy * dy) <= (br * br))
		{
			isDead = true;
			BlockTime_ = 0;
			return true;
		}
		else
		{
			isDead = false;
			return false;
		}
	}
	else
	{
		return false;
	}
	//return (dx * dx + dy * dy) <= (br * br);
}