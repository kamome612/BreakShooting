#include "Enemy.h"
#include "Bullet.h"
#include "Engine/time.h"
#include "Engine/SceneManager.h"

namespace {
	const float CHIP_SIZE = 64.0f;
	const float SPEED = 150;
	const XMFLOAT3 INIT_POS = { 618,150,0 };
	const float FINV_TIME = 1.0f;//無敵終了時間
}
Enemy::Enemy(GameObject* parent)
	:GameObject(parent,"Enemy"),pImage_(-1),lImage_(-1),dImage_(-1),
	                            fImage_(-1),Life_(3),invTime_(0.0f),hitFlag_(false)
{
}

void Enemy::Initialize()
{
	pImage_ = LoadGraph("Assets\\Enemy2.png");
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
	float x = transform_.position_.x;
	float y = transform_.position_.y;

	//弾との当たり判定
	std::list<Bullet*> pBullets = GetParent()->FindGameObjects<Bullet>();
	for (Bullet* pBullet : pBullets) {
		if (hitFlag_ == false) {
			if (pBullet->CollideCircle(x+CHIP_SIZE/2 , y+CHIP_SIZE/2, 20.0f)) {
				Life_ -= 1;
				hitFlag_ = true;
			}
		}
	}

	//弾が当たったら少しの間無敵になる
	if (hitFlag_ == true) {
		invTime_ += Time::DeltaTime();
		if (invTime_ >= FINV_TIME) {
			hitFlag_ = false;
			invTime_ = 0;
		}
	}

	SceneManager* scenemanager = (SceneManager*)FindObject("SceneManager");
	if (Life_ == 0) {
		//bool flag = true;
		//scenemanager->SetWinFlag(flag);
		scenemanager->winFlag_ = true;
		scenemanager->ChangeScene(SCENE_ID_RESULT);
	}
}

void Enemy::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;
	DrawGraph(x, y, pImage_, TRUE);
	//DrawRotaGraph(x, y, 1, XM_PI,pImage_, false, false);

	// ライフの枠
	int lenF = 900;  // x移動
	DrawExtendGraph(lenF, -175, lenF + 510, 245, fImage_, TRUE);

	//ライフとライフの下に黒くしたライフを描画
	int lenYff = 1115;//ハートフレームだけのx移動
	int lenY = 36;   //Y移動
	for (int j = 0; j < 3; j++) {
		//DrawGraph((CHIP_SIZE * j) + 40, 30, dImage_, TRUE);
		DrawExtendGraph((CHIP_SIZE * j) + lenYff, lenY, (CHIP_SIZE * j) + lenYff - 60, lenY + 45, dImage_, TRUE);
	}

	for (int i = 0; i < Life_; i++) {
		//DrawGraph((CHIP_SIZE * i) + 40, 30, lImage_, TRUE);
		DrawExtendGraph((CHIP_SIZE * i) + lenYff+5, lenY, (CHIP_SIZE * i)+ 980,lenY + 45, lImage_, TRUE);
	}

	//DrawBox(x + 15, y, x + CHIP_SIZE - 15, y + CHIP_SIZE, GetColor(0, 0, 255), FALSE);//当たり判定確認用
}

void Enemy::Release()
{
}