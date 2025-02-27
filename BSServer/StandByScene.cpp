#include "StandByScene.h"
#include "Engine/SceneManager.h"

StandByScene::StandByScene(GameObject* parent)
	:GameObject(parent,"StandByScene"),sPict_(-1)
{
}

void StandByScene::Initialize()
{
	sPict_ = LoadGraph("Assets\\Picture\\standby.jpg");
	assert(sPict_ >= 0);
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
	static bool connectOK = false;
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
	DrawGraph(0, 0, sPict_, TRUE);
}

void StandByScene::Release()
{
}
