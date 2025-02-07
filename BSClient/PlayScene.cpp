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

	//自分で実行する場合
	/*sendIp.d1 = 172;
	sendIp.d2 = 0;
	sendIp.d3 = 0;
	sendIp.d4 = 1;*/

	XMFLOAT3 pPos = pPlayer->GetPosition();
	pPos.y = 180.0f;
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
    
	int recvPort;
	int peek = 0;
	XMFLOAT3 ePos = pEnemy->GetPosition();
	long recvPos[3] = { 0,0,0 };
	if (CheckNetWorkRecvUDP(sock)) {
		ret = NetWorkRecvUDP(sock, &sendIp, &recvPort, &recvPos, sizeof(recvPos), peek);
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
