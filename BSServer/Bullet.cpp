#include "Bullet.h"
#include"Engine/time.h"

namespace
{
	const float Speed_{ 500.0 };
	const float LimitTime_ = 2.0f;

}
Bullet::Bullet(GameObject* parent)
	:GameObject(parent, "Bullet"), hImage_(-1), BulletTime_(0)
{

}

void Bullet::Initialize()
{
	hImage_ = LoadGraph("Assets\\Image\\missile.png");
	assert(hImage_ > 0);
}


void Bullet::Update()
{
	BulletTime_ += Time::DeltaTime();
	if (BulletTime_ >= LimitTime_)
	{
		KillMe();
	}

	transform_.position_.y -= Speed_ * Time::DeltaTime();

}

void Bullet::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;

	DrawGraph(x, y, hImage_, TRUE);
}


void Bullet::SetPosition(float _x, float _y)
{
	transform_.position_.x = _x;
	transform_.position_.y = _y;
}