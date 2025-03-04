#include "Bullet.h"
#include"Engine/time.h"
#include "Stage.h"
#include"Block.h"
#include<vector>

namespace
{
	const float Speed_{ 550.0 };
	const float LimitTime_ = 4.0f;

	const float Lwidth = 100; //����
	const float Rwidth = 1200;//�E��
	const float height = 100; //�V��
	const float low = 680; //�n��
	const float MARGIN = 15; //�]��
	const float myR = 8.0f;//���a

	const float posX = 30;//x���W�̏C��
}

Bullet::Bullet(GameObject* parent)
	:GameObject(parent, "Bullet"), hImage_(-1), BulletTime_(0), angle_(XM_PI / -2.0), moveX(0), moveY(0)
	, isDead_(false)
{
	ip_ = pSceneManager->GetIP();
	sock_ = pSceneManager->GetSock();
}

void Bullet::Initialize()
{
	hImage_ = LoadGraph("Assets\\Image\\missile.png");
	assert(hImage_ > 0);

	if (rand() % 2 == 0)
	{
		randomAngle_ = 3.0f * XM_PI / 4.0f;
	}
	else {
		randomAngle_ = XM_PI / 4.0f; // �E�΂ߏ�i�E�����j
	}
}


void Bullet::Update()
{
	DataTransmission();

	BulletTime_ += Time::DeltaTime();
	if (BulletTime_ >= LimitTime_)
	{
		KillMe();
	}

	moveX = cos(angle_) * Speed_ * Time::DeltaTime();
	moveY = sin(angle_) * Speed_ * Time::DeltaTime();

	transform_.position_.x += moveX;
	transform_.position_.y += moveY;

	DataReception();

	WallJudge();
	BlockJudge();


}

void Bullet::Draw()
{
	int x = (int)transform_.position_.x + posX;
	int y = (int)transform_.position_.y;

	//DrawGraph(x, y, hImage_, TRUE);
	DrawRotaGraph(x, y, 1, angle_ - 80.1, hImage_, TRUE);

	DrawCircle(x - 1, y, 8.0f, GetColor(0, 0, 255), FALSE);
}


void Bullet::SetPosition(float _x, float _y)
{
	transform_.position_.x = _x;
	transform_.position_.y = _y;
}

bool Bullet::CollideCircle(float x, float y, float r)
{
	float myCenterX = transform_.position_.x + posX - 1;
	float myCenterY = transform_.position_.y;
	//float myR = 8.0f;
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

	if (transform_.position_.x < Lwidth - posX + MARGIN) {//����
		transform_.position_.x = Lwidth - posX + MARGIN;
		angle_ = XM_PI - angle_;
	}

	if (transform_.position_.x > Rwidth - posX - MARGIN) {//�E��
		transform_.position_.x = Rwidth - posX - MARGIN;
		angle_ = XM_PI - angle_;
	}

	if (transform_.position_.y < height + MARGIN) {//�V��
		transform_.position_.y = height + MARGIN;

		if (angle_ == (XM_PI / -2.0) || angle_ == (XM_PI / 2.0)) {//90�x��������
			angle_ = randomAngle_;
		}
		else {
			angle_ = -angle_;
		}

	}

	if (transform_.position_.y > low - MARGIN) {//�n��
		if (angle_ == (XM_PI / -2.0) || angle_ == (XM_PI / 2.0)) {//90�x��������
			angle_ = randomAngle_;
		}
		else {
			transform_.position_.y = low - MARGIN;
			angle_ = -angle_;
		}
	}
}

void Bullet::BlockJudge()
{
	if (Stage::hBlock.empty()) {
		return;//�u���b�N���Ȃ��ꍇ �������Ȃ�
	}

	std::vector<Block*>dBlocks;//�폜�p

	for (auto& blocks : Stage::hBlock)
	{
		if (blocks == nullptr) {
			continue;
		}
		if (blocks->BulletCollistion(transform_.position_.x, transform_.position_.y, myR))
		{
			dBlocks.push_back(blocks);

			if (angle_ == (XM_PI / -2.0f) || angle_ == (XM_PI / 2.0)) {
				angle_ = randomAngle_;
				//if (rand() % 2 == 0) {
				//	angle_ = 3.0f * XM_PI / 4.0f; //��
				//}
				//else {
				//	angle_ = -XM_PI / 4.0f;
				//}
			}
			else {
				angle_ = -angle_;
			}
		}
	}

	//for (auto& blocks : dBlocks) {
	//	blocks->KillMe();

	//	//�v�f������
	//	std::vector<Block*>::iterator it = std::find(Stage::hBlock.begin(), Stage::hBlock.end(), blocks);
	//	if (it != Stage::hBlock.end())
	//	{
	//		Stage::hBlock.erase(it); // �폜
	//	}
	//}
}

bool Bullet::IsAlive()
{
	return !isDead_;
}

void Bullet::DataReception()
{
	int ret = 0;
	int recvPort;
	int peek = 0;
	int type = 3;

	float recvData[3] = { 0,0,0 };
	if (CheckNetWorkRecvUDP(sock_)) {
		ret = NetWorkRecvUDP(sock_, &ip_, &recvPort, &recvData, sizeof(recvData), peek);
		type = recvData[0];
	}
	if (ret > 0 && type == 3 && recvData[1] > 0) {
		transform_.position_.x = recvData[1];
		transform_.position_.y = recvData[2];
		transform_.position_.z = 0;
	}
	else if (ret == -1 || ret == -2 || ret == -3)
	{
		// ��M���s�̃G���[�m�F�p
		//printfDx("%d", ret);
	}
}

void Bullet::DataTransmission()
{
	XMFLOAT3 pos = transform_.position_;
	int type = 3;
	pos.y = 780 - transform_.position_.y;
	float sendData[3] = { type,pos.x,pos.y };
	int ret = NetWorkSendUDP(sock_, ip_, 8888, &sendData, sizeof(sendData));
}
