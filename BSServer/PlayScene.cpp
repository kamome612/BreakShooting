#include "PlayScene.h"
#include "Stage.h"

const unsigned short SERVER_PORT = 8888;

PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent,"PlayScene")
{
}

void PlayScene::Initialize()
{
	Image_ = LoadGraph("Assets\\Play.jpg");
	assert(Image_ >= 0);
	Stage* pStage = Instantiate<Stage>(this);
	pPlayer = Instantiate<Player>(GetParent());
	//ePlayer = Instantiate<Player>(GetParent());
}

void PlayScene::Update()
{

	/*ePlayer->SendData();
	pPlayer->RecvData();
	pPlayer->SendData();
	ePlayer->RecvData();*/
	
}

void PlayScene::Draw()
{
	DrawGraph(0, 0, Image_, TRUE);
}

void PlayScene::Release()
{
}
