#include "StandByScene.h"
#include "Engine/SceneManager.h"

StandByScene::StandByScene(GameObject* parent)
	:GameObject(parent,"StandByScene"),sPict_(-1), connectOK{false}
{
}

void StandByScene::Initialize()
{
	sPict_ = LoadGraph("Assets\\Picture\\standby.jpg");
	assert(sPict_ >= 0);
	sButton_ = LoadGraph("Assets\\Picture\\StButton.png");
	assert(sButton_ >= 0);
	sock_ = MakeUDPSocket(8888);
}

void StandByScene::Update()
{
	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	recvIp_.d1 = 172;
	recvIp_.d2 = 0;
	recvIp_.d3 = 0;
	recvIp_.d4 = 1;
	int peek = 0;
	int recvPort;
	//long s;
	int s = 1;
	if (connectOK != true) {
		connectOK = CheckNetWorkRecvUDP(sock_);
		
	}
	if (CheckNetWorkRecvUDP(sock_)) {
		NetWorkRecvUDP(sock_, &recvIp_, &recvPort, &s, sizeof(s), peek);
		/*int ret = NetWorkSendUDP(sock_, recvIp, 8888, &s, sizeof(s));
		pSceneManager->SetSock(sock_);
		pSceneManager->ChangeScene(SCENE_ID_PLAY);*/
	}
	if (connectOK && CheckHitKey(KEY_INPUT_P)) {
		NetWorkSendUDP(sock_, recvIp_, 8888, &s, sizeof(s));
		pSceneManager->SetSock(sock_);
		pSceneManager->SetIP(recvIp_);
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}
}

void StandByScene::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;
	int height = 600 / 2;
	int width = 800 / 2;
	
	DrawGraph(0, 0, sPict_, TRUE);
	if (connectOK)
	{
		DrawGraph(x + width, y + (height + 50), sButton_, TRUE);
	}
	//DrawGraph(x + width, y + (height + 50), sButton_, TRUE);

}

void StandByScene::Release()
{
}
