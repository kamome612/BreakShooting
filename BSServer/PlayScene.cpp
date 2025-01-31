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
	pEnemy = Instantiate<Enemy>(GetParent());
	sock = MakeUDPSocket(8888);
}

void PlayScene::Update()
{

	/*ePlayer->SendData();
	pPlayer->RecvData();
	pPlayer->SendData();
	ePlayer->RecvData();*/
	int ret = 0;
	IPDATA recvIp;
	int recvPort;
	int peek = 0;
	XMFLOAT3 ePos;
	long recvPos[3] = { 0,0,0 };
	if (CheckNetWorkRecvUDP(sock)) {
		ret = NetWorkRecvUDP(sock, &recvIp, &recvPort, &recvPos, sizeof(recvPos), peek);
	}
	if (ret > 0)
	{
		//バイトオーダー変換
		ePos.x = (float)ntohl(recvPos[0]);
		ePos.y = (float)ntohl(recvPos[1]);
		ePos.z = (float)ntohl(recvPos[2]);
		/*u_long scaledX = ntohl(recvPos.x);
		u_long scaledY = ntohl(recvPos.y);
		u_long scaledZ = ntohl(recvPos.z);
		ePos = { (float)scaledX,(float)scaledY,(float)scaledZ };*/
		pEnemy->SetPosition(ePos);
	}
	else if (ret == -1 || ret == -2 || ret == -3)
	{
		// 受信失敗のエラー処理
		printfDx("%d", ret);
	}
	
}

void PlayScene::Draw()
{
	DrawGraph(0, 0, Image_, TRUE);
}

void PlayScene::Release()
{
}
