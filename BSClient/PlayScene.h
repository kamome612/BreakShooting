#pragma once
#include "Engine/GameObject.h"
#include "Player.h"
class PlayScene :
    public GameObject
{
	int Image_;
	Player* pPlayer;
	//Player* ePlayer;
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

