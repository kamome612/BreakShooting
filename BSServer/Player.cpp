#include "Player.h"
#include "Engine/time.h"
#include "Bullet.h"
namespace {
	const float CHIP_SIZE = 64.0f;
	const float SPEED = 50;
}

Player::Player(GameObject* parent)
{
}

void Player::Initialize()
{
	pImage_ = LoadGraph("Assets\\chara.png");
	assert(pImage_ >= 0);
}

void Player::Update()
{
	float moveX, moveY;
	moveX = 0.0f;
	moveY = 0.0f;

	if (CheckHitKey(KEY_INPUT_D)) {
		moveX += SPEED * Time::DeltaTime();
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
	DrawRectGraph(x, y, CHIP_SIZE, CHIP_SIZE, CHIP_SIZE, CHIP_SIZE, pImage_, TRUE);
}

void Player::Release()
{
}
