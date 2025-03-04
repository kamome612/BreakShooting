#include "PlayScene.h"
#include "Stage.h"
#include "Engine/time.h"

PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent,"PlayScene"), fpsTimer_(0.0f), fpsCount_(0), fps_(0)
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
	Ip = pSceneManager->GetIP();
}

void PlayScene::Update()
{
	//fps確認用
	/*if (fpsTimer_ >= 1.0f) {
		fpsTimer_ = 0.0f;
		fps_ = fpsCount_;
		fpsCount_ = 0;
	}
	fpsTimer_ += Time::DeltaTime();
	fpsCount_++;*/

	DataReception();
	DataTransmission();
	DataReception();
	DataReception();

	//XMFLOAT3 pPos = pPlayer->GetPosition();
	//pPos.y = 180.0f;
	////float sendPos[3] = { htonl(pPos.x),htonl(pPos.y),htonl(pPos.z) };
	//float sendPos[3] = { pPos.x,pPos.y,pPos.z };
	//int ret = NetWorkSendUDP(sock, sendIp, 8888, &sendPos, sizeof(sendPos));
    //   
	//int recvPort;
	//int peek = 0;
	//int type;
	//XMFLOAT3 ePos = pEnemy->GetPosition();
	//float recvPos[3] = { 0,0,0 };
	//if (CheckNetWorkRecvUDP(sock)) {
	//	ret = NetWorkRecvUDP(sock, &sendIp, &recvPort, &recvPos, sizeof(recvPos), peek);
	//	//type = (int)ntohl(recvData[0]);
	//}
	////float tmp = (float)ntohl(recvPos[0]);
	//float tmp = recvPos[0];
	//if (ret > 0 && 0 < tmp)
	//{
	//	//バイトオーダー変換
	//	/*ePos.x = (float)ntohl(recvData[0]);
	//	ePos.y = (float)ntohl(recvData[1]);
	//	ePos.z = (float)ntohl(recvData[2]);*/
	//	ePos.x = recvPos[0];
	//	ePos.y = recvPos[1];
	//	ePos.z = recvPos[2];
	//	pEnemy->SetPosition(ePos);
	//}
	//else if (ret == -1 || ret == -2 || ret == -3)
	//{
	//	// 受信失敗のエラー処理
	//	printfDx("%d", ret);
	//}
	//
	//int bType = 0;
	//float bData[2] = { 0,0 };
	////BulletData bulletData_ = { 0,0,0,0,0 };
	//if (CheckNetWorkRecvUDP(sock)) {
	//	ret = NetWorkRecvUDP(sock, &sendIp, &recvPort, &bData, sizeof(bData), peek);
	//	//bType = (int)ntohl(bData[0]);
	//	bType = (int)bData[0];
	//}
	//if (ret > 0 && bType == 6)
	//{
	//	Player* pPlayer = (Player*)FindObject("Player");
	//	Bullet* pBullet = Instantiate<Bullet>(GetParent());
	//	Enemy* pEnemy = (Enemy*)FindObject("Enemy");
	//	XMFLOAT3 bPos = pEnemy->GetPosition();
	//	//float rAngle = (float)ntohl(bData[1]);
	//	float rAngle = bData[1];
	//	bPos.y += 64;
	//	//bPos.x -= 30;
	//	pBullet->SetPosition(bPos.x, bPos.y);
	//	pBullet->SetAngle(XM_PI/2,XM_2PI - rAngle);
	//	pPlayer->SetBullets(pBullet);
	//	
	//	//XMFLOAT3 bulletPos = pBullet->GetPosition();
	//	//float angle = 0.0;
	//	//float time = 0.0;
	//	////バイトオーダー変換
	//	//bulletPos.x = (float)ntohl(bulletData_.x);
	//	//bulletPos.y = (float)ntohl(bulletData_.y);
	//	//angle = (float)ntohl(bulletData_.angle);
	//	//time = (float)ntohl(bulletData_.time);
	//
	//	//pBullet->SetPosition(bulletPos.x, bulletPos.y);
	//	//pBullet->SetAngle(-angle);
	//	//pBullet->SetBulletTime(time);
	//}
	//else {
	//	//受信失敗のエラー内容
	//	switch (ret)
	//	{
	//	case -1:
	//		printfDx("エラー");
	//		break;
	//	case -2:
	//		printfDx("受信データよりバッファのサイズの方が小さい");
	//		break;
	//	case -3:
	//		printfDx("受信データがない");
	//		break;
	//	default:
	//		break;
	//	}
	//}
}

void PlayScene::Draw()
{
	DrawGraph(0, 0, Image_, TRUE);

	//fps確認用
	/*std::string s = std::to_string(fps_);
	int Cr = GetColor(255, 255, 255);
	DrawString(620, 0, s.c_str(), Cr);*/
}

void PlayScene::Release()
{
}

void PlayScene::DataReception()
{
	int ret = 0;
	int recvPort;
	int peek = 0;
	int type = 0;

	XMFLOAT3 ePos = pEnemy->GetPosition();
	float recvData[3] = { 0,0,0 };
	if (CheckNetWorkRecvUDP(sock)) {
		ret = NetWorkRecvUDP(sock, &Ip, &recvPort, &recvData, sizeof(recvData), peek);
		type = (int)ntohl(recvData[0]);
	}
	int num = (float)ntohl(recvData[1]);
	if (ret > 0 && type == 1 && num > 0) {
		ePos.x = (float)ntohl(recvData[1]);
		ePos.y = (float)ntohl(recvData[2]);
		ePos.z = 0;
		pEnemy->SetPosition(ePos);
	}
	else if (ret > 0 && type == 2) {
		Player* pPlayer = (Player*)FindObject("Player");
		Bullet* pBullet = Instantiate<Bullet>(GetParent());
		Enemy* pEnemy = (Enemy*)FindObject("Enemy");
		XMFLOAT3 bPos = pEnemy->GetPosition();
		float rAngle = (float)ntohl(recvData[1]);
		bPos.y += 64;
		pBullet->SetPosition(bPos.x, bPos.y);
		pBullet->SetAngle(XM_PI / 2, XM_2PI - rAngle);
		pPlayer->SetBullets(pBullet);
	}
	else if (ret == -1 || ret == -2 || ret == -3)
	{
		// 受信失敗のエラー確認用
		//printfDx("%d", ret);
	}

	//int ret = 0;
	//int recvPort;
	//int peek = 0;
	//int type = 0;

	//XMFLOAT3 ePos = pEnemy->GetPosition();
	//float recvData[3] = { 0,0,0 };
	//if (CheckNetWorkRecvUDP(sock)) {
	//	ret = NetWorkRecvUDP(sock, &Ip, &recvPort, &recvData, sizeof(recvData), peek);
	//	type = recvData[0];
	//}
	//if (ret > 0 && type == 1 && recvData[1] > 0) {
	//	ePos.x = recvData[1];
	//	ePos.y = recvData[2];
	//	ePos.z = 0;
	//	pEnemy->SetPosition(ePos);
	//}
	//else if (ret > 0 && type == 2) {
	//	Player* pPlayer = (Player*)FindObject("Player");
	//	Bullet* pBullet = Instantiate<Bullet>(GetParent());
	//	Enemy* pEnemy = (Enemy*)FindObject("Enemy");
	//	XMFLOAT3 bPos = pEnemy->GetPosition();
	//	float rAngle = recvData[1];
	//	bPos.y += 64;
	//	pBullet->SetPosition(bPos.x, bPos.y);
	//	pBullet->SetAngle(XM_PI / 2, XM_2PI - rAngle);
	//	pPlayer->SetBullets(pBullet);
	//}
	//else if (ret == -1 || ret == -2 || ret == -3)
	//{
	//	// 受信失敗のエラー確認用
	//	//printfDx("%d", ret);
	//}
}

void PlayScene::DataTransmission()
{
	int ret = 0;
	XMFLOAT3 pPos = pPlayer->GetPosition();
	pPos.y = 180.0f;
	int type = 1;
	float sendData[3] = { htonl(type),htonl(pPos.x),htonl(pPos.y) };
	ret = NetWorkSendUDP(sock, Ip, 8888, &sendData, sizeof(sendData));

	/*int ret = 0;
	XMFLOAT3 pPos = pPlayer->GetPosition();
	pPos.y = 180.0f;
	int type = 1;
	float sendData[3] = { type,pPos.x,pPos.y };
	ret = NetWorkSendUDP(sock, Ip, 8888, &sendData, sizeof(sendData));*/
}
