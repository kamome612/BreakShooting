#include "Bullet.h"
#include"Engine/time.h"

namespace
{ 
	const float Speed_{ 10.0 };


}
Bullet::Bullet(GameObject* parent)
	:GameObject(parent,"Bullet"),hImage_(-1)
{
	transform_.position_ = { 400,300,0 };
}

Bullet::~Bullet()
{
	if (hImage_ > 0)
		DeleteGraph(hImage_);
}

void Bullet::Initialize()
{
	/* �摜�̃��[�h
	hImage_ = LoadGraph("Assets\Image\�Z�Z.png");
	assert(hImage_ > 0);
	*/

}


void Bullet::Update()
{
	//transform_.position_.y += 1.0;
	
	if (CheckHitKey(KEY_INPUT_SPACE))//�e�X�g
	{
		transform_.position_.y += Speed_ * Time::DeltaTime();
	}
	if (transform_.position_.y >= 10)
		KillMe();
		

	// ������Kill�@�A�@���˂̐��@�A�@�G�ɓ���������@�A�@�@
}

void Bullet::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;

	DrawCircle(x ,y , 10,255, TRUE);   //����
	//DrawGraph(x, y, hImage_, TRUE); //�摜�̕\��

}


void Bullet::SetPosition(float x, float y)
{
	transform_.position_.x = x;
	transform_.position_.y = y;
}