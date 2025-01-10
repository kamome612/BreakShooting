#include "TitleScene.h"
#include "Engine/SceneManager.h"

TitleScene::TitleScene(GameObject* parent)
	:GameObject(parent,"TitleScene"),tPict_(-1)
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
	tPict_ = LoadGraph("Assets\\Picture\\title.jpg");
	assert(tPict_ > 0);
}

void TitleScene::Update()
{
	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	if (CheckHitKey(KEY_INPUT_T))
	{
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}
}

void TitleScene::Draw()
{
	DrawGraph(0, 0, tPict_, TRUE);
}

void TitleScene::Release()
{
}
