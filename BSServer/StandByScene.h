#pragma once
#include "Engine/GameObject.h"
class StandByScene :
    public GameObject
{
private:
	int sPict_;
	int sock_;
public:
	//�R���X�g���N�^
	StandByScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};

