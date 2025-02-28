#pragma once
#include "Engine/GameObject.h"
class ResultScene :
    public GameObject
{
private:
	int rPict_;
	bool isWin_;
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

