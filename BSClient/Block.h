#pragma once
#include "Engine/GameObject.h"

class Block :
	public GameObject
{
	int Bc;
	int width_ = 51;
	int height_ = 15;
public:
	//引数：parent  親オブジェクト（SceneManager）
	Block(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	bool BulletCollistion(float bx, float by, float br);
};
