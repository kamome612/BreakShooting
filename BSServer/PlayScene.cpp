#include "PlayScene.h"
#include "Stage.h"
#include "Engine/time.h"
#include <string>

PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent,"PlayScene"),fpsTimer_(0.0f),fpsCount_(0),fps_(0)
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
	recvIp = pSceneManager->GetIP();
}

void PlayScene::Update()
{
	//fps確認用
	if (fpsTimer_ >= 1.0f) {
		fpsTimer_ = 0.0f;
		fps_ = fpsCount_;
		fpsCount_ = 0;
	}
	fpsTimer_ += Time::DeltaTime();
	fpsCount_++;

	/*ePlayer->SendData();
	pPlayer->RecvData();
	pPlayer->SendData();
	ePlayer->RecvData();*/
	int ret = 0;
	int recvPort;
	int peek = 0;
	XMFLOAT3 ePos = pEnemy->GetPosition();
	long recvPos[3] = { 0,0,0 };
	if (CheckNetWorkRecvUDP(sock)) {
		ret = NetWorkRecvUDP(sock, &recvIp, &recvPort, &recvPos, sizeof(recvPos), peek);
	}
	float tmp = (float)ntohl(recvPos[0]);
	if (ret > 0 && 0 < tmp)
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

	XMFLOAT3 pPos = pPlayer->GetPosition();
	pPos.y = 180.0f;
	long sendPos[3] = { htonl(pPos.x),htonl(pPos.y),htonl(pPos.z) };
	ret = NetWorkSendUDP(sock, recvIp, 8888, &sendPos, sizeof(sendPos));

	/*struct BulletData
	{
		int type;
		float x;
		float y;
		float angle;
		float time;
	};*/

	int bType = 0;

	//BulletData bulletData_ = { 0,0,0,0,0 };
	if (CheckNetWorkRecvUDP(sock)) {
		ret = NetWorkRecvUDP(sock, &recvIp, &recvPort, &bType, sizeof(bType), peek);
		bType = (int)ntohl(bType);
	}
	if (ret > 0 && bType == 6)
	{
		Player* pPlayer = (Player*)FindObject("Player");
		Bullet* pBullet = Instantiate<Bullet>(GetParent());
		Enemy* pEnemy = (Enemy*)FindObject("Enemy");
		XMFLOAT3 bPos = pEnemy->GetPosition();
		bPos.y += 64;
		bPos.x -= 30;
		pBullet->SetPosition(bPos.x, bPos.y);
		pBullet->SetAngle(80.1);
		pPlayer->SetBullets(pBullet);

		//XMFLOAT3 bulletPos = pBullet->GetPosition();
		//float angle = 0.0;
		//float time = 0.0;
		////バイトオーダー変換
		//bulletPos.x = (float)ntohl(bulletData_.x);
		//bulletPos.y = (float)ntohl(bulletData_.y);
		//angle = (float)ntohl(bulletData_.angle);
		//time = (float)ntohl(bulletData_.time);

		//pBullet->SetPosition(bulletPos.x, bulletPos.y);
		//pBullet->SetAngle(-angle);
		//pBullet->SetBulletTime(time);
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
	std::string s = std::to_string(fps_);
	int Cr = GetColor(255, 255, 255);
	DrawString(620, 0, s.c_str(), Cr);
}

void PlayScene::Release()
{
}
