#pragma once
#include "Engine/GameObject.h"
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
};

