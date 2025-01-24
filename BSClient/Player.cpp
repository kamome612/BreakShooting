#include "Player.h"
#include "Engine/time.h"
#include "Bullet.h"
#include "Stage.h"

namespace {
	const float CHIP_SIZE = 64.0f;
	const float SPEED = 150;
	const XMFLOAT3 INIT_POS = { 320,180,0 };//最初の位置
}

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), pImage_(-1), lImage_(-1), dImage_(-1),
	fImage_(-1), Life_(3)
{
	transform_.position_ = INIT_POS;
}

void Player::Initialize()
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

void Player::Update()
{
	Stage pStage = Stage(GetParent());

	float x= transform_.position_.x;
	float y = transform_.position_.y;

	float moveX, moveY;
	moveX = 0.0f;
	moveY = 0.0f;

	if (CheckHitKey(KEY_INPUT_D)) {
		moveX = SPEED * Time::DeltaTime();
		transform_.position_.x += moveX;
	}
	else if (CheckHitKey(KEY_INPUT_A)) {
		moveX = SPEED * Time::DeltaTime();
		transform_.position_.x -= moveX;
	}

	if (CheckHitKey(KEY_INPUT_SPACE)) {
		Bullet* bullet = Instantiate<Bullet>(GetParent());
		bullet->SetPosition(transform_.position_.x, transform_.position_.y);
	}

	if (pStage.IsRectIntersectsOtherRect(x, y, CHIP_SIZE, CHIP_SIZE)) {

	}
}

void Player::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;
	DrawGraph(x, y, pImage_, TRUE);

	//ライフの枠
	int lenF = -120;//x移動
	DrawExtendGraph(lenF, -175, lenF + 510, 245, fImage_, TRUE);

	//ライフとライフの下に黒くしたライフを描画
	int lenYff = 95;//ハートフレームだけのx移動
	int lenY = 36;   //Y移動
	for (int j = 0; j < 3; j++) {
		//DrawGraph((CHIP_SIZE * j) + 40, 30, dImage_, TRUE);
		DrawExtendGraph((CHIP_SIZE * j) + lenYff, lenY, (CHIP_SIZE * j) + lenYff - 60, lenY + 45, dImage_, TRUE);
	}

	for (int i = 0; i < Life_; i++) {
		//DrawGraph((CHIP_SIZE * i) + 40, 30, lImage_, TRUE);
		DrawExtendGraph((CHIP_SIZE * i) + 100, lenY, (CHIP_SIZE * i) - 40, lenY + 45, lImage_, TRUE);
	}

	DrawBox(x+15, y, x+CHIP_SIZE-15,y+CHIP_SIZE, GetColor(0, 0, 0), FALSE);//当たり判定確認用
}

void Player::Release()
{
}

void Player::RecvData()
{
	//int ret;
	//struct sockaddr_in clientAddr;//クライアントアドレス情報格納領域
	//int addrlen = sizeof(clientAddr);
	//XMFLOAT3 trs;
	//ret = recvfrom(sock, (char*)&trs, sizeof(trs), 0, (SOCKADDR*)&clientAddr, &addrlen);
	//if (ret > 0)
	//{
	//	//バイトオーダー変換
	//	transform_.position_.x = ntohl(trs.x);
	//	transform_.position_.y = ntohl(trs.y);
	//	transform_.position_.z = ntohl(trs.z);
	//}
	//// 受信エラー	未受信時はWSAEWOULDBLOCKが発生
	//else if (WSAGetLastError() != WSAEWOULDBLOCK)
	//{
	//	// 受信失敗のエラー処理
	//	return;
	//}
}

void Player::SendData()
{
	//XMFLOAT3 trs = { htonl(transform_.position_.x),htonl(transform_.position_.y),htonl(transform_.position_.z) };
	//int ret = sendto(sock, (char*)&trs, sizeof(trs), 0, (SOCKADDR*)&serverAddr, sizeof(serverAddr);
	//// 未送信以外のエラー
	//if (ret == SOCKET_ERROR && WSAGetLastError() != WSAEWOULDBLOCK)
	//{
	//	// エラー処理
	//	return;
	//}

}

void Player::SetPosition(float _x, float _y)
{
	transform_.position_.x = _x;
	transform_.position_.y = _y;
}

//bool Player::CollideRect(float x, float y, float w, float h)
//{
//	 //プレイヤーの矩形の左上と右下の座標を計算
//	float playerLeft = transform_.position_.x + 15; // プレイヤーの左上X座標
//	float playerTop = transform_.position_.y;       // プレイヤーの上Y座標
//	float playerRight = transform_.position_.x + CHIP_SIZE - 15; // プレイヤーの右下X座標
//	float playerBottom = transform_.position_.y + CHIP_SIZE;    // プレイヤーの下Y座標
//}

//bool Player::CollideBox(float x, float y, float r)
//{
//
//	DrawBox(x + 15, y, x + CHIP_SIZE - 15, y + CHIP_SIZE, GetColor(0, 0, 0), FALSE);//当たり判定確認用
//	//x,y,rが相手の円の情報
//	//自分の円の情報
//	float myCenterX = transform_.position_.x +15;
//	float myCenterY = transform_.position_.y + (float)CHIP_SIZE / 2;
//	float myR = 16.0f;
//	float dx = myCenterX - x;
//	float dy = myCenterY - y;
//	if ((dx * dx + dy * dy) < ((r + myR) * (r + myR))) {
//		return true;
//	}
//	else {
//		return false;
//	}
//	return false;
//}
