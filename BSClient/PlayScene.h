#pragma once
#include "Engine/GameObject.h"
#include "Player.h"
#include "Enemy.h"
class PlayScene :
    public GameObject
{
	int Image_;
	Player* pPlayer;
	Enemy* pEnemy;
	int sock;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	PlayScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};

