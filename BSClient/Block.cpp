#include "Block.h"

Block::Block(GameObject* parent)
	:GameObject(parent, "Block")
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
	DrawBoxAA(x, y, x + width_ + 1, y + height_ + 1, Bc, FALSE);
}

void Block::Release()
{
}