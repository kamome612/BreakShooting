#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

class PlayScene :
	public GameObject
{
private:
	int Image_;
	Player* pPlayer;
	Enemy* pEnemy;
	int sock;
	IPDATA Ip;
	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
    
	//ちょいfps確認用
	int fpsCount_;
	float fpsTimer_;
	int fps_;
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

	//データ受信
	void DataReception();

	//データ送信(プレイヤー位置)
	void DataTransmission();
};

