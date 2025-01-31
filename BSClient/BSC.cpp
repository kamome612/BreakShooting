#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment( lib, "ws2_32.lib" )

//SOCKET sock;
//SOCKADDR_IN serverAddr;

#include "DxLib.h"

#include "Engine/global.h"
#include "Engine/RootObject.h"

namespace Screen {
	static const int WIDTH = 1280;
	static const int HEIGHT = 720;
	static const char* WINDOW_NAME = "BSC";
	static const int WINDOW_EXTEND = 0;
	static const int WINDOW_MODE = 1;
};

// サーバのIPアドレス
//const char* SERVER_ADDRESS = "127.0.0.1";
//const char* SERVER_ADDRESS = "192.168.43.38";       // 接続先なんか適当にクラスメートとやって！
// サーバのポート番号
//const unsigned short SERVER_PORT = 8888;

struct CIRCLE
{
	int centerX;
	int centerY;
	int size;
	int color;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WSADATA wsaData;

	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0) {
		//エラー処理
		return 0;
	}

	// UDPソケットの作成
	//SOCKET sock;
	//sock = socket(AF_INET, SOCK_DGRAM, 0);
	//if (sock == INVALID_SOCKET) {
	//	return 0;
	//}

	//// sockをノンブロッキングモードに
	//unsigned long cmdarg = 0x01;
	//int ret = ioctlsocket(sock, FIONBIO, &cmdarg);
	//if (ret == SOCKET_ERROR) {
	//	return 0;
	//}

	//// サーバアドレスの指定
	////SOCKADDR_IN serverAddr;
	//int addrlen = sizeof(serverAddr);

	////サーバの宛先情報セット
	//memset(&serverAddr, 0, sizeof(serverAddr));
	//serverAddr.sin_family = AF_INET;
	//serverAddr.sin_port = htons(SERVER_PORT);
	//inet_pton(AF_INET, (PCSTR)SERVER_ADDRESS, &serverAddr.sin_addr.s_addr);


	SetGraphMode(Screen::WIDTH, Screen::HEIGHT, 32);
	SetOutApplicationLogValidFlag(FALSE); // ログを出さない

	SetMainWindowText(Screen::WINDOW_NAME);
	SetWindowSizeExtendRate(Screen::WINDOW_EXTEND);
	ChangeWindowMode(Screen::WINDOW_MODE); // Windowモードの場合

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	SetDrawScreen(DX_SCREEN_BACK);
	SetAlwaysRunFlag(TRUE);
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	RootObject* pRootObject = new RootObject;
	pRootObject->Initialize();

	while (true) {
		//全オブジェクトの更新処理
		//ルートオブジェクトのUpdateを呼んだあと、自動的に子、孫のUpdateが呼ばれる
		pRootObject->UpdateSub();


		if (DxLib::ProcessMessage() == -1 /*|| AppIsExit()*/)
			break;

		ClearDrawScreen();
		//全オブジェクトを描画
		//ルートオブジェクトのDrawを呼んだあと、自動的に子、孫のUpdateが呼ばれる
		pRootObject->DrawSub();

		// サイズとか色はお任せ
		//CIRCLE circle = { 0, 0, 20, GetColor(138,43,226) };
		//// マウス座標取得し、circleのcenterXとcenterTに格納
		//GetMousePoint(&circle.centerX, &circle.centerY);
		//// 描画
		//DrawCircle(circle.centerX, circle.centerY, circle.size, circle.color, 1);

		//// サーバ( serverAddr )に●の情報送信
		//CIRCLE sendCircle = { htonl(circle.centerX),htonl(circle.centerY),htonl(circle.size),htonl(circle.color) };
		//int ret = sendto(sock, (char*)&sendCircle, sizeof(sendCircle), 0, (SOCKADDR*)&serverAddr, sizeof(serverAddr));


		//// 未送信以外のエラー
		//if (ret == SOCKET_ERROR && WSAGetLastError() != WSAEWOULDBLOCK)
		//{
		//	// エラー処理
		//	return 0;
		//}


		RefreshDxLibDirect3DSetting();

		ScreenFlip();
		WaitTimer(16);
		if (ProcessMessage() == -1 || CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}

	}
	pRootObject->ReleaseSub();
	delete pRootObject;

	DxLib_End();
	return 0;
}