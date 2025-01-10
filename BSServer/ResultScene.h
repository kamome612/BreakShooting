#pragma once
#include "Engine/GameObject.h"
class ResultScene :
    public GameObject
{
public:
	//コンストラクタ
	ResultScene(GameObject* parent);

	//デストラクタ
	~ResultScene();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};

