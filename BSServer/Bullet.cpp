#include "Bullet.h"
#include"Engine/time.h"
#include "Stage.h"
namespace
{
	const float Speed_{ 550.0 };
	const float LimitTime_ = 6.0f;

	const float Lwidth = 100; //左壁
	const float Rwidth = 1200;//右壁
	const float height = 100; //天井
	const float low = 680; //地面
	const float MARGIN = 15; //余白

	const float posX = 30;//x座標の修正
}

Bullet::Bullet(GameObject* parent)
	:GameObject(parent, "Bullet"), hImage_(-1), BulletTime_(0), angle_(XM_PI / -2.0), moveX(0), moveY(0)
                                 , isDead_(false)
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

	moveX = cos(angle_) * Speed_ * Time::DeltaTime();
	moveY = sin(angle_) * Speed_ * Time::DeltaTime();

	transform_.position_.x += moveX;
	transform_.position_.y += moveY;

	WallJudge();

}

void Bullet::Draw()
{
	int x = (int)transform_.position_.x + posX;
	int y = (int)transform_.position_.y;

	//DrawGraph(x, y, hImage_, TRUE);
	DrawRotaGraph(x, y, 1, angle_ - 80.1, hImage_, TRUE);

}


void Bullet::SetPosition(float _x, float _y)
{
	transform_.position_.x = _x;
	transform_.position_.y = _y;
}

bool Bullet::CollideCircle(float x, float y, float r)
{
	float myCenterX = transform_.position_.x;
	float myCenterY = transform_.position_.y;
	float myR = 12.0f;
	float dx = myCenterX - x;
	float dy = myCenterY - y;
	if ((dx * dx + dy * dy) < ((r + myR) * (r + myR))) {
		return true;
	}
	else
	{
		return false;
	}
}

void Bullet::WallJudge()
{

	if (transform_.position_.x < Lwidth - posX + MARGIN) {//左壁
		transform_.position_.x = Lwidth - posX + MARGIN;
		angle_ = XM_PI - angle_;
	}

	if (transform_.position_.x > Rwidth - posX - MARGIN) {//右壁
		transform_.position_.x = Rwidth - posX - MARGIN;
		angle_ = XM_PI - angle_;
	}

	if (transform_.position_.y < height + MARGIN) {//天井
		transform_.position_.y = height + MARGIN;

		if (angle_ == (XM_PI / -2.0)) {//90度だったら
			if (rand() % 2 == 0)
			{
				angle_ = 5.0f * XM_PI / 4.0f;//左

			}
			else {
				angle_ = XM_PI / -4.0;

			}
		}
		else {
			angle_ = -angle_;
		}

	}

	if (transform_.position_.y > low - MARGIN) {//地面
		transform_.position_.y = low - MARGIN;
		angle_ = -angle_;
	}


}

bool Bullet::IsAlive()
{
	return !isDead_;
}
