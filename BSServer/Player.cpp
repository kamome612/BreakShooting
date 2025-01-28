#include "Player.h"
#include "Engine/time.h"
#include "Bullet.h"

namespace {
	const float CHIP_SIZE = 64.0f;
	const float SPEED = 150;
	const XMFLOAT3 INIT_POS = { 320,540,0 };//�ŏ��̈ʒu
	const float RWIDTH = 1200; //�X�e�[�W�̉E
	const float LWIDTH = 100; //�X�e�[�W�̍�
	const float HEIGHT = 680; //�X�e�[�W�̍���
	const float MARGIN = 15; //�]��
}

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), pImage_(-1),lImage_(-1), dImage_(-1),
	                               fImage_(-1), Life_(3)
{
	transform_.position_ = INIT_POS;
}

void Player::Initialize()
{
	pImage_ = LoadGraph("Assets\\chara.png");
	assert(pImage_ >= 0);
	lImage_=LoadGraph("Assets\\Image\\Life.png");
	assert(lImage_ >= 0);
	dImage_ = LoadGraph("Assets\\Image\\Damage.png");
	assert(dImage_ >= 0);
	fImage_=LoadGraph("Assets\\Image\\LifeFrame.png");
	assert(fImage_ >= 0);

	transform_.position_ = INIT_POS;
}

void Player::Update()
{
	float x = transform_.position_.x;
	float y = transform_.position_.y;

	float moveX, moveY;
	moveX = 0.0f;
	moveY = 0.0f;

	if (CheckHitKey(KEY_INPUT_D)) {
		moveX = SPEED * Time::DeltaTime();
		if (transform_.position_.x < RWIDTH - CHIP_SIZE + MARGIN) {
			transform_.position_.x += moveX;
		}
		else {
			transform_.position_.x = RWIDTH - CHIP_SIZE + MARGIN; //��яo������K�^�K�^���Ȃ��悤��
		}

	}
	else if (CheckHitKey(KEY_INPUT_A)) {
		moveX = SPEED * Time::DeltaTime();
		if (transform_.position_.x > LWIDTH - MARGIN) {
			transform_.position_.x -= moveX;
		}
		else {
			transform_.position_.x = LWIDTH - MARGIN; //��яo�����肪���������Ȃ��悤��
		}
	}

	if (CheckHitKey(KEY_INPUT_SPACE)) {
		Bullet* bullet = Instantiate<Bullet>(GetParent());
		bullet->SetPosition(transform_.position_.x, transform_.position_.y);
	}
}

void Player::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;
	DrawGraph(x, y, pImage_, TRUE);

	//���C�t�̘g
	int lenF = -120;//x�ړ�
	DrawExtendGraph(lenF, -175, lenF + 510, 245, fImage_, TRUE);

	//���C�t�ƃ��C�t�̉��ɍ����������C�t��`��
	int lenYff = 95;//�n�[�g�t���[��������x�ړ�
	int lenY = 36;   //Y�ړ�
	for (int j = 0; j < 3; j++) {
		//DrawGraph((CHIP_SIZE * j) + 40, 30, dImage_, TRUE);
		DrawExtendGraph((CHIP_SIZE * j) + lenYff, lenY, (CHIP_SIZE * j) + lenYff - 60, lenY + 45, dImage_, TRUE);
	}

	for (int i = 0; i < Life_; i++) {
		//DrawGraph((CHIP_SIZE * i) + 40, 30, lImage_, TRUE);
		DrawExtendGraph((CHIP_SIZE * i) + 100, lenY, (CHIP_SIZE * i) - 40, lenY + 45, lImage_, TRUE);
	}

	DrawBox(x + 15, y, x + CHIP_SIZE - 15, y + CHIP_SIZE, GetColor(0, 0, 0), FALSE);//�����蔻��m�F�p
}

void Player::Release()
{
}

void Player::RecvData()
{
	//int ret;
	//struct sockaddr_in clientAddr;//�N���C�A���g�A�h���X���i�[�̈�
	//int addrlen = sizeof(clientAddr);
	//XMFLOAT3 trs;
	//ret = recvfrom(sock,(char*)&trs, sizeof(trs), 0, (SOCKADDR*)&clientAddr, &addrlen);
	//if (ret > 0)
	//{
	//	//�o�C�g�I�[�_�[�ϊ�
	//	transform_.position_.x = ntohl(trs.x);
	//	transform_.position_.y = ntohl(trs.y);
	//	transform_.position_.z = ntohl(trs.z);
	//}
	//// ��M�G���[	����M����WSAEWOULDBLOCK������
	//else if (WSAGetLastError() != WSAEWOULDBLOCK)
	//{
	//	// ��M���s�̃G���[����
	//	return;
	//}
}

void Player::SendData()
{
	//XMFLOAT3 trs = { htonl(transform_.position_.x),htonl(transform_.position_.y),htonl(transform_.position_.z) };
	//int ret = sendto(sock, (char*)&trs, sizeof(trs), 0, (SOCKADDR*)&bindAddr, sizeof(bindAddr);
	//// �����M�ȊO�̃G���[
	//if (ret == SOCKET_ERROR && WSAGetLastError() != WSAEWOULDBLOCK)
	//{
	//	// �G���[����
	//	return;
	//}

}

void Player::SetPosition(float _x, float _y)
{
	transform_.position_.x = _x;
	transform_.position_.y = _y;
}
