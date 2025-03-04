#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Bullet.h"
#include <vector>

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

	//リロード
	void Reload();

	//Bulletsに追加
	void SetBullets(Bullet* b);

	bool CollideCircle(float x, float y, float r);

private:
	int pImage_;
	int lImage_;
	int dImage_;
	int fImage_;
	int Life_;
	int BImage_;
	bool isPush_;//弾を押したか
	bool reloading_;//リロード中
	int currentNum_;//現在の弾数
	float reloadTime_;//現在の時間
	float invTime_; //無敵時間
	bool hitFlag_;
	int sock_;
	int myBulletNum_;
	IPDATA ip_;
	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
};