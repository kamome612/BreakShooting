#pragma once
#include "Engine/GameObject.h"
class StandByScene :
    public GameObject
{
private:
	int sPict_;
	int sButton_;
	int sock_;
	IPDATA recvIp_;
	bool connectOK;

public:
	//コンストラクタ
	StandByScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};

