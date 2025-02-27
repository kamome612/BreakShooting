#include "Player.h"
#include "Engine/time.h"
#include "Bullet.h"
#include <vector>

namespace {
	const float CHIP_SIZE = 64.0f;
	const float SPEED = 400;
	const XMFLOAT3 INIT_POS = { 320,540,0 };//�ŏ��̈ʒu
	const float RWIDTH = 1200; //�X�e�[�W�̉E
	const float LWIDTH = 100; //�X�e�[�W�̍�
	const float HEIGHT = 680; //�X�e�[�W�̍���
	const float MARGIN = 15; //�]��
	const float FINV_TIME = 1.0f;//���G�I������
	const float DEATH_TIME = 2.0f;

	const int MAX_BULLET = 5;//�e�̍ő吔
	//const float INTERVAL = 3.0f;//�����[�h����
}

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), pImage_(-1), lImage_(-1), dImage_(-1), BImage_(-1),
	fImage_(-1), Life_(3), reloading_(false), reloadTime_(0.0),
	currentNum_(MAX_BULLET),hitFlag_(false),time_(0)
{
	sock_ = pSceneManager->GetSock();
	ip_ = pSceneManager->GetIP();
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
	BImage_ = LoadGraph("Assets\\Image\\missile.png");
	assert(BImage_ > 0);

	transform_.position_ = INIT_POS;
}

void Player::Update()
{
	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");

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

	if (CheckHitKey(KEY_INPUT_SPACE) && bullets.size() < MAX_BULLET) {
		if (!isPush_) {
			Bullet* bullet = Instantiate<Bullet>(GetParent());
			bullet->SetPosition(transform_.position_.x, transform_.position_.y);
			bullets.push_back(bullet);
			//currentNum_--;
			isPush_ = true;

			//���M
			int type = 6;
			/*XMFLOAT3 bPos = bullet->GetPosition();
			float angle = -(bullet->GetAngle());
			float time = bullet->GetBulletTime();
			long sendData[5] = { htonl(type), htonl(bPos.x),htonl(bPos.y),htonl(angle),htonl(time) };*/
			long sendData[1] = { htonl(type) };
			int ret = NetWorkSendUDP(sock_, ip_, 8888, &sendData, sizeof(sendData));
		}
	}
	else {
		isPush_ = false;
	}

	for (int i = bullets.size() - 1; i >= 0; i--)
	{
		if (!bullets[i]->IsAlive()) {
			bullets[i]->KillMe();
			bullets.erase(bullets.begin() + i);//�폜
		}
	}

	//�e�Ƃ̓����蔻��
	std::list<Bullet*> pBullets = GetParent()->FindGameObjects<Bullet>();
	for (Bullet* pBullet : pBullets) {
		if (hitFlag_ == false) {
			if (pBullet->CollideCircle(x+CHIP_SIZE/2,y+CHIP_SIZE/2 ,20.0f )) {
				Life_ -= 1;
				hitFlag_ = true;
			}
		}
	}

	//�e�����������班���̊Ԗ��G�ɂȂ�
	if (hitFlag_ == true) {
		invTime_ += Time::DeltaTime();
		if (invTime_ >= FINV_TIME) {
			hitFlag_ = false;
			invTime_ = 0;
		}
	}
	
	if (Life_ == 0)
	{
		pSceneManager->ChangeScene(SCENE_ID_RESULT);
	}
	
	/*time_ += Time::DeltaTime();
	if (time_ >= DEATH_TIME) {
		
	}*/

	//�����[�h
	//if (CheckHitKey(KEY_INPUT_L) || currentNum_ == 0)
	//{
	//	if (currentNum_ != MAX_BULLET && reloading_ != true) {
	//		reloading_ = true;
	//	}
	//}
	////�����[�h��
	//if (reloading_) {
	//	Reload();
	//}

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

	DrawCircle(x + CHIP_SIZE / 2, y + CHIP_SIZE / 2, 20.0f, GetColor(0, 0, 255), FALSE);
	//int lenX = 870;
	//for (int i = 0; i < bullets.size(); i++) {//�e�̊m�F�p
	//	//DrawGraph((CHIP_SIZE * i) + 40, 30, lImage_, TRUE);
	//	DrawGraph((i * 64) + lenX + 65, 10, BImage_, TRUE);
	//}

}

void Player::Release()
{

}

void Player::SetPosition(float _x, float _y)
{
	transform_.position_.x = _x;
	transform_.position_.y = _y;
}

bool Player::CollideCircle(float x, float y, float r)
{
	float myCenterX = transform_.position_.x+CHIP_SIZE/2;
	float myCenterY = transform_.position_.y+CHIP_SIZE/2;
	float myR = 20.0f;
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

//void Player::Reload()
//{
//	reloadTime_ += Time::DeltaTime();
//	if (reloadTime_ > INTERVAL)
//	{
//		currentNum_ = MAX_BULLET;
//		reloading_ = false;
//		reloadTime_ = 0.0;
//	}
//}
