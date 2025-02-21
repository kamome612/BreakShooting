#pragma once
#include "Engine/GameObject.h"

class Player : public GameObject
{
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Player(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//�ʒu���Z�b�g
	void SetPosition(float _x, float _y);

	//�����[�h
	void Reload();
private:
	int pImage_;
	int lImage_;
	int dImage_;
	int fImage_;
	int Life_;
	int BImage_;
	bool isPush_;//�e����������
	bool reloading_;//�����[�h��
	int currentNum_;//���݂̒e��
	float reloadTime_;//���݂̎���
	bool hitFlag_;
};