#pragma once
#include "Engine/GameObject.h"
class Enemy :
    public GameObject
{
public:
    //�R���X�g���N�^
    Enemy(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

private:
	int pImage_;
	int lImage_;
	int dImage_;
	int fImage_;
	int Life_;
};

