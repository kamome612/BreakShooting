#pragma once
#include "Engine/GameObject.h"
class TitleScene :
    public GameObject
{
private:
	int tPict_;
public:
    //コンストラクタ
    TitleScene(GameObject* parent);

    //デストラクタ
    ~TitleScene();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};

