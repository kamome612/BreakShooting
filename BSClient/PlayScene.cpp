#include "PlayScene.h"
#include "Stage.h"
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent,"PlayScene")
{
}

void PlayScene::Initialize()
{
	Image_ = LoadGraph("Assets\\Picture\\PlayScene.jpg");
	assert(Image_ >= 0);
	Stage* pStage = Instantiate<Stage>(this);
	pPlayer = Instantiate<Player>(GetParent());
	pEnemy = Instantiate<Enemy>(GetParent());
	sock = MakeUDPSocket(8888);
}

void PlayScene::Update()
{
	/*ePlayer->SendData();
	pPlayer->RecvData();
	pPlayer->SendData();
	ePlayer->RecvData();*/

	IPDATA sendIp;
	sendIp.d1 = 192;
	sendIp.d2 = 168;
	sendIp.d3 = 43;
	sendIp.d4 = 66;

	XMFLOAT3 pPos = pPlayer->GetPosition();
	long sendPos[3] = { htonl(pPos.x),htonl(pPos.y),htonl(pPos.z) };

	//	// スケーリングを行う（例えば 1000倍）
	//u_long scaledX = static_cast<u_long>(pPos.x);
	//u_long scaledY = static_cast<u_long>(pPos.y);
	//u_long scaledZ = static_cast<u_long>(pPos.z);

	//// htonlでネットワークバイトオーダーに変換
	//long sendPos[3] = {
	//	htonl(scaledX),
	//	htonl(scaledY),
	//	htonl(scaledZ)
	//};

	int ret = NetWorkSendUDP(sock, sendIp, 8888, &sendPos, sizeof(sendPos));
}

void PlayScene::Draw()
{

	DrawGraph(0, 0, Image_, TRUE);
}

void PlayScene::Release()
{
}
