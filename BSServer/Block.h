#pragma once
#include "Engine/GameObject.h"
class Block :
    public GameObject
{
	int Bc;
	int width_ = 51;
	int height_ = 20;
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
};

