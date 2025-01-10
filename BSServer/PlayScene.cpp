#include "PlayScene.h"
#include "Stage.h"
#include "Player.h"
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

void PlayScene::Initialize()
{
	Image_ = LoadGraph("Assets\\Play.jpg");
	assert(Image_ >= 0);
	Stage* pStage = Instantiate<Stage>(this);
	Player* pPlayer = Instantiate<Player>(GetParent());
}

void PlayScene::Update()
{
}

void PlayScene::Draw()
{
	DrawGraph(0, 0, Image_, TRUE);
}

void PlayScene::Release()
{
}
