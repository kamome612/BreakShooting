#include "Enemy.h"
#include "Bullet.h"

namespace {
	const float CHIP_SIZE = 64.0f;
	const float SPEED = 150;
	const XMFLOAT3 INIT_POS = { 320,180,0 };
}

Enemy::Enemy(GameObject* parent)
	:GameObject(parent,"Enemy"),pImage_(-1),lImage_(-1),dImage_(-1),
	                            fImage_(-1),Life_(3)
{
}

void Enemy::Initialize()
{
	pImage_ = LoadGraph("Assets\\chara.png");
	assert(pImage_ >= 0);
	lImage_ = LoadGraph("Assets\\Image\\Life.png");
	assert(lImage_ >= 0);
	dImage_ = LoadGraph("Assets\\Image\\Damage.png");
	assert(dImage_ >= 0);
	fImage_ = LoadGraph("Assets\\Image\\LifeFrame.png");
	assert(fImage_ >= 0);

	transform_.position_ = INIT_POS;
}

void Enemy::Update()
{
}

void Enemy::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;
	DrawGraph(x, y, pImage_, TRUE);

	////ライフの枠
	//int lenF = -120;//x移動
	//DrawExtendGraph(lenF, -175, lenF + 510, 245, fImage_, TRUE);

	////ライフとライフの下に黒くしたライフを描画
	//int lenYff = 95;//ハートフレームだけのx移動
	//int lenY = 36;   //Y移動
	//for (int j = 0; j < 3; j++) {
	//	//DrawGraph((CHIP_SIZE * j) + 40, 30, dImage_, TRUE);
	//	DrawExtendGraph((CHIP_SIZE * j) + lenYff, lenY, (CHIP_SIZE * j) + lenYff - 60, lenY + 45, dImage_, TRUE);
	//}

	//for (int i = 0; i < Life_; i++) {
	//	//DrawGraph((CHIP_SIZE * i) + 40, 30, lImage_, TRUE);
	//	DrawExtendGraph((CHIP_SIZE * i) + 100, lenY, (CHIP_SIZE * i) - 40, lenY + 45, lImage_, TRUE);
	//}

	DrawBox(x + 15, y, x + CHIP_SIZE - 15, y + CHIP_SIZE, GetColor(0, 0, 0), FALSE);//当たり判定確認用
}

void Enemy::Release()
{
}
