#pragma once
#include "Engine/GameObject.h"
class ResultScene :
    public GameObject
{
private:
	int rPict_;
	bool isWin_;
public:
	//�R���X�g���N�^
	ResultScene(GameObject* parent);

	//�f�X�g���N�^
	~ResultScene();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};

