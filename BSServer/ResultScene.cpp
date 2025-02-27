#include "ResultScene.h"
#include "Engine/SceneManager.h"

ResultScene::ResultScene(GameObject* parent)
	:GameObject(parent, "ResultScene"),rPict_(-1)
{
}

ResultScene::~ResultScene()
{
}

void ResultScene::Initialize()
{
	rPict_ = LoadGraph("Assets\\Picture\\gameover.jpg");
	assert(rPict_ > 0);
}

void ResultScene::Update()
{
	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	if (CheckHitKey(KEY_INPUT_T))
	{
		pSceneManager->ChangeScene(SCENE_ID_TITLE);
	}
}

void ResultScene::Draw()
{
	DrawGraph(0, 0, rPict_, TRUE);
}

void ResultScene::Release()
{
}