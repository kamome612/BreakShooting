#pragma once
#include "Engine/GameObject.h"
class Stage :
    public GameObject
{
private:
	int Cr;
public:
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Stage(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

};

