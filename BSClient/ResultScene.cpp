#include "ResultScene.h"
#include "Engine/SceneManager.h"

ResultScene::ResultScene(GameObject* parent)
	:GameObject(parent, "ResultScene"), rPict_(-1),isWin_(false)
{
	isWin_ = scenemanager->GetWinFlag();
	sock_ = scenemanager->GetSock();
}

ResultScene::~ResultScene()
{
}

void ResultScene::Initialize()
{
	WaitTimer(2000);
	if (isWin_ == true) {
		rPict_ = LoadGraph("Assets\\Picture\\WIN.jpg");
	}
	else {
		rPict_ = LoadGraph("Assets\\Picture\\LOSE.jpg");
	}
	assert(rPict_ > 0);
}

void ResultScene::Update()
{
	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	if (CheckHitKey(KEY_INPUT_R))
	{
		pSceneManager->ChangeScene(SCENE_ID_TITLE);
	}
	if (CheckHitKey(KEY_INPUT_Q))
	{
		DeleteUDPSocket(sock);
		DxLib_End();
	}
}

void ResultScene::Draw()
{
	DrawGraph(0, 0, rPict_, TRUE);
}

void ResultScene::Release()
{
}