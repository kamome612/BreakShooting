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

	//当たり判定
	bool BulletCollistion(float bx, float by, float br);


};

