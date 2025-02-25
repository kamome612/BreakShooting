#include "StandByScene.h"
#include "Engine/SceneManager.h"

StandByScene::StandByScene(GameObject* parent)
	:GameObject(parent, "StandByScene"), sPict_(-1)
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
	IPDATA sendIp;
	sendIp.d1 = 192;
	sendIp.d2 = 168;
	sendIp.d3 = 42;
	sendIp.d4 = 175;
	//int recvPort;
	int s;
	//int peek = 0;
	if (CheckHitKey(KEY_INPUT_P)) {
	}
	int ret = NetWorkSendUDP(sock_, sendIp, 8888, &s, sizeof(s));

	bool judg = true;
	if (CheckNetWorkRecvUDP(sock_)) {
		//NetWorkRecvUDP(sock_, &sendIp, &recvPort, &s, sizeof(s), peek);
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
		pSceneManager->SetSock(sock_);
	}
}

void StandByScene::Draw()
{
	DrawGraph(0, 0, sPict_, TRUE);
}

void StandByScene::Release()
{
}