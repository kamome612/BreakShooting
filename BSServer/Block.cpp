#include "Block.h"

Block::Block(GameObject* parent)
	:GameObject(parent,"Block")
{
}

void Block::Initialize()
{
	Bc = GetColor(255, 255, 255);
}

void Block::Update()
{
}

void Block::Draw()
{
	float x = transform_.position_.x;
	float y = transform_.position_.y;
	DrawBoxAA(x,y,x + width_ + 0.5, y + height_ + 0.5, Bc, FALSE);
}

void Block::Release()
{
}

bool Block::BulletCollistion(float bx, float by, float br)
{
	float x = transform_.position_.x - 30;
	float y = transform_.position_.y;

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
	return (dx * dx + dy * dy) <= (br * br);
}
