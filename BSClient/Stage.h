#pragma once
#include "Engine/GameObject.h"
#include "Block.h"
#include<vector>

class Stage :
    public GameObject
{
private:
	int Cr;
	int Bcr;
	int WallCr;
	int Image_;
	float width_;
	float height_;
public:
	//引数：parent  親オブジェクト（SceneManager）
	Stage(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	bool IsRectIntersectsOtherRect(float x, float y, float w, float h);

	static std::vector<Block*> hBlock;

};

