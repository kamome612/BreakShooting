#pragma once
#include "Engine/GameObject.h"

class Player : public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Player(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	//位置をセット
	void SetPosition(float _x, float _y);
private:
	int pImage_;
	int lImage_;
	int dImage_;
	int fImage_;
	int Life_;
	bool isPush_;//弾を押したか
	bool hitFlag_;//当たったか
	float invTime_;//無敵時間
};