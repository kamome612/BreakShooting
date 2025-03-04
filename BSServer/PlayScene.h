#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

class PlayScene :
	public GameObject
{
private:
	int Image_;
	Player* pPlayer;
	Enemy* pEnemy;
	int sock;
	IPDATA Ip;
	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
    
	//���傢fps�m�F�p
	int fpsCount_;
	float fpsTimer_;
	int fps_;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	PlayScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//�f�[�^��M
	void DataReception();

	//�f�[�^���M(�v���C���[�ʒu)
	void DataTransmission();
};

