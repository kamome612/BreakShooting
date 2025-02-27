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
	sock = pSceneManager->GetSock();
	sendIp = pSceneManager->GetIP();
}

void PlayScene::Update()
{
	/*ePlayer->SendData();
	pPlayer->RecvData();
	pPlayer->SendData();
	ePlayer->RecvData();*/

	XMFLOAT3 pPos = pPlayer->GetPosition();
	pPos.y = 180.0f;
	long sendPos[3] = { htonl(pPos.x),htonl(pPos.y),htonl(pPos.z) };

	int ret = NetWorkSendUDP(sock, sendIp, 8888, &sendPos, sizeof(sendPos));
    
	int recvPort;
	int peek = 0;
	int type;
	XMFLOAT3 ePos = pEnemy->GetPosition();
	long recvData[3] = { 0,0,0 };
	if (CheckNetWorkRecvUDP(sock)) {
		ret = NetWorkRecvUDP(sock, &sendIp, &recvPort, &recvData, sizeof(recvData), peek);
		//type = (int)ntohl(recvData[0]);
	}
	if (ret > 0)
	{
		//バイトオーダー変換
		ePos.x = (float)ntohl(recvData[1]);
		ePos.y = (float)ntohl(recvData[2]);
		ePos.z = (float)ntohl(recvData[3]);
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

	struct BulletData
	{
		int type;
		float x;
		float y;
		float angle;
		float time;
	};

	BulletData bulletData_ = { 0,0,0,0,0 };
	if (CheckNetWorkRecvUDP(sock)) {
		ret = NetWorkRecvUDP(sock, &sendIp, &recvPort, &bulletData_, sizeof(bulletData_), peek);
		int type = (int)ntohl(bulletData_.type);
	}
	if (ret > 0 && bulletData_.type == 6)
	{
		Bullet* pBullet = Instantiate<Bullet>(GetParent());
		XMFLOAT3 bulletPos = pBullet->GetPosition();
		float angle = 0.0;
		float time = 0.0;
		//バイトオーダー変換
		bulletPos.x = (float)ntohl(bulletData_.x);
		bulletPos.y = (float)ntohl(bulletData_.y);
		angle = (float)ntohl(bulletData_.angle);
		time = (float)ntohl(bulletData_.time);

		pBullet->SetPosition(bulletPos.x, bulletPos.y);
		pBullet->SetAngle(-angle);
		pBullet->SetBulletTime(time);
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
