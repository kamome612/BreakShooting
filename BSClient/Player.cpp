#include "Player.h"
#include "Engine/time.h"
#include "Bullet.h"

namespace {
	const float CHIP_SIZE = 64.0f;
	const float SPEED = 50;
	const XMFLOAT3 INIT_POS = { 320,180,0 };//Å‰‚ÌˆÊ’u
}

Player::Player(GameObject* parent)
{
	transform_.position_ = INIT_POS;
}

void Player::Initialize()
{
	pImage_ = LoadGraph("Assets\\chara.png");
	assert(pImage_ >= 0);
	transform_.position_ = INIT_POS;
}

void Player::Update()
{
	float moveX, moveY;
	moveX = 0.0f;
	moveY = 0.0f;

	if (CheckHitKey(KEY_INPUT_D)) {
		transform_.position_.x += SPEED * Time::DeltaTime();
	}
	else if (CheckHitKey(KEY_INPUT_A)) {
		moveX -= SPEED * Time::DeltaTime();
	}

	/*if (CheckHitKey(KEY_INPUT_SPACE)) {
		Bullet* bullet = Instantiate<Bullet>(GetParent());
	}*/
}

void Player::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;
	DrawGraph(x, y, pImage_, TRUE);
}

void Player::Release()
{
}
