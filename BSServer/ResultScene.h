#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
class ResultScene :
    public GameObject
{
private:
	int rPict_;
	bool isWin_;
	int sock_;
	SceneManager* scenemanager = (SceneManager*)FindObject("SceneManager");
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

