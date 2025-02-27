#pragma once
#include "Engine/GameObject.h"
#include "Block.h"
#include <vector>

class Stage :
	public GameObject
{
private:
	int Cr;
	int Bcr;
	int WallCr;
	int Image_;
	float width_;
	float height_;
	float timer_;
	int hit;
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

	//bool CollideCircle(float x, float y, float r);
	bool IsRectIntersectsOtherRect(float x, float y, float w,float h);

	static std::vector<Block*> hBlock;

};
