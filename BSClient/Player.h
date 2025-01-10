#pragma once
#include "Engine/GameObject.h"
class Player :
    public GameObject
{
    //これから追加していく　光秀
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
private:
	int pImage_;
	int lImage_;
};

