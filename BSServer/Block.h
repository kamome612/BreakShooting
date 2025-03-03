#pragma once
#include "Engine/GameObject.h"

class Block :
    public GameObject
{
	int Bc;
	int width_ = 51;
	int height_ = 20;

	bool isDead;
	float BlockTime_;
public:
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Block(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//�����蔻��
	bool BulletCollistion(float bx, float by, float br);


};

