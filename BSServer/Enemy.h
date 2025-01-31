#pragma once
#include "Engine/GameObject.h"
class Enemy :
    public GameObject
{
public:
    //コンストラクタ
    Enemy(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

private:
	int pImage_;
	int lImage_;
	int dImage_;
	int fImage_;
	int Life_;
};

