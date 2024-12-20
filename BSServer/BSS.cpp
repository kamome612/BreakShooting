#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment( lib, "ws2_32.lib" )

#include "DxLib.h"

// ポート番号
const unsigned short SERVER_PORT = 8888;
const unsigned int MESSAGE_LENGTH = 1024;

struct CIRCLE
{
	int centerX;
	int centerY;
	int size;
	int color;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// WinSock2.2 初期化処理
	WSADATA wsaData;

	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0) {
		//エラー処理
		return 0;
	}

	// UDPソケットの作成
	SOCKET sock;
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == INVALID_SOCKET) {
		//エラー処理
		return 0;
	}

	// sockをノンブロッキングモードに
	unsigned long cmdarg = 0x01;
	int ret = ioctlsocket(sock, FIONBIO, &cmdarg);
	if (ret == INVALID_SOCKET) {
		//エラー処理
		return 0;
	}

	// 固定アドレスの割り当て
	SOCKADDR_IN bindAddr;
	memset(&bindAddr, 0, sizeof(bindAddr));//0クリアで初期化
	bindAddr.sin_family = AF_INET;
	bindAddr.sin_port = htons(SERVER_PORT);
	bindAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(sock, (SOCKADDR*)&bindAddr, sizeof(bindAddr)) == SOCKET_ERROR) {
		//エラー処理
		return 0;
	}

	// DxLib周りの初期化・ウィンドウ作成処理
	SetWindowText("サーバ！");
	SetGraphMode(800, 600, 32);
	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1)
		return -1;

	SetBackgroundColor(0, 0, 0);
	SetDrawScreen(DX_SCREEN_BACK);
	SetAlwaysRunFlag(1);


	while (1)
	{
		ClearDrawScreen();

		// 初期値...画面の範囲外
		CIRCLE circle = { -100, -100, 0, GetColor(255, 255, 255) };


		// 受信
		int ret;
		CIRCLE recvCircle;
		struct sockaddr_in clientAddr; //クライアントのアドレス情報格納領域
		int addrlen = sizeof(clientAddr);

		ret = recvfrom(sock, (char*)&recvCircle, sizeof(recvCircle), 0, (SOCKADDR*)&clientAddr, &addrlen);
		// 受信時
		if (ret > 0)
		{
			// バイトオーダーの変換
			circle.centerX = ntohl(recvCircle.centerX);
			circle.centerY = ntohl(recvCircle.centerY);
			circle.size = ntohl(recvCircle.size);
			circle.color = ntohl(recvCircle.color);
		}
		// 受信エラー	未受信時はWSAEWOULDBLOCKが発生
		else if (WSAGetLastError() != WSAEWOULDBLOCK)
		{
			// 受信失敗のエラー処理
			return 0;
		}


		// 描画
		DrawCircle(circle.centerX, circle.centerY, circle.size, circle.color, 1);

		ScreenFlip();
		WaitTimer(16);
		if (ProcessMessage() == -1 || CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}

	DxLib_End();
	return 0;
}