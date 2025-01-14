#include "Bullet.h"
#include"Engine/time.h"

namespace
{
	const float Speed_{ 10.0 };


}
Bullet::Bullet(GameObject* parent)
	:GameObject(parent, "Bullet"), hImage_(-1)
{


}

Bullet::~Bullet()
{
	if (hImage_ > 0)
		DeleteGraph(hImage_);
}

void Bullet::Initialize()
{
	hImage_ = LoadGraph("Assets\Image\missile.png");
	assert(hImage_ > 0);

}


void Bullet::Update()
{
	transform_.position_.y += Speed_ * Time::DeltaTime();

	//if (CheckHitKey(KEY_INPUT_SPACE))//テスト
	//{
	//	transform_.position_.y += Speed_ * Time::DeltaTime();
	//}


	// 距離でKill　、　反射の数　、　敵に当たったら　、　　
}

void Bullet::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;

	DrawGraph(x, y, hImage_, TRUE); 

}


void Bullet::SetPosition(float x, float y)
{
	transform_.position_.x = x;
	transform_.position_.y = y;
}