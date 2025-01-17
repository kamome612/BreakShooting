#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment( lib, "ws2_32.lib" )

#include "DxLib.h"

#include "Engine/global.h"
#include "Engine/RootObject.h"

namespace Screen {
	static const int WIDTH = 1280;
	static const int HEIGHT = 720;
	static const char* WINDOW_NAME = "BSS";
	static const int WINDOW_EXTEND = 0;
	static const int WINDOW_MODE = 1;
};

// �|�[�g�ԍ�
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
	WSADATA wsaData;

	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0) {
		//�G���[����
		return 0;
	}

	// UDP�\�P�b�g�̍쐬
	SOCKET sock;
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == INVALID_SOCKET) {
		//�G���[����
		return 0;
	}

	// sock���m���u���b�L���O���[�h��
	unsigned long cmdarg = 0x01;
	int ret = ioctlsocket(sock, FIONBIO, &cmdarg);
	if (ret == INVALID_SOCKET) {
		//�G���[����
		return 0;
	}

	// �Œ�A�h���X�̊��蓖��
	SOCKADDR_IN bindAddr;
	memset(&bindAddr, 0, sizeof(bindAddr));//0�N���A�ŏ�����
	bindAddr.sin_family = AF_INET;
	bindAddr.sin_port = htons(SERVER_PORT);
	bindAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(sock, (SOCKADDR*)&bindAddr, sizeof(bindAddr)) == SOCKET_ERROR) {
		//�G���[����
		return 0;
	}


	SetGraphMode(Screen::WIDTH, Screen::HEIGHT, 32);
	SetOutApplicationLogValidFlag(FALSE); // ���O���o���Ȃ�

	SetMainWindowText(Screen::WINDOW_NAME);
	SetWindowSizeExtendRate(Screen::WINDOW_EXTEND);
	ChangeWindowMode(Screen::WINDOW_MODE); // Window���[�h�̏ꍇ

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}
	SetDrawScreen(DX_SCREEN_BACK);
	SetAlwaysRunFlag(TRUE);
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	RootObject* pRootObject = new RootObject;
	pRootObject->Initialize();

	while (true) {
		//�S�I�u�W�F�N�g�̍X�V����
		//���[�g�I�u�W�F�N�g��Update���Ă񂾂��ƁA�����I�Ɏq�A����Update���Ă΂��
		pRootObject->UpdateSub();


		if (DxLib::ProcessMessage() == -1 /*|| AppIsExit()*/)
			break;

		ClearDrawScreen();
		//�S�I�u�W�F�N�g��`��
		//���[�g�I�u�W�F�N�g��Draw���Ă񂾂��ƁA�����I�Ɏq�A����Update���Ă΂��
		pRootObject->DrawSub();

		// �����l...��ʂ͈̔͊O
		CIRCLE circle = { -100, -100, 0, GetColor(255, 255, 255) };


		// ��M
		int ret;
		CIRCLE recvCircle;
		struct sockaddr_in clientAddr; //�N���C�A���g�̃A�h���X���i�[�̈�
		int addrlen = sizeof(clientAddr);

		ret = recvfrom(sock, (char*)&recvCircle, sizeof(recvCircle), 0, (SOCKADDR*)&clientAddr, &addrlen);
		// ��M��
		if (ret > 0)
		{
			// �o�C�g�I�[�_�[�̕ϊ�
			circle.centerX = ntohl(recvCircle.centerX);
			circle.centerY = ntohl(recvCircle.centerY);
			circle.size = ntohl(recvCircle.size);
			circle.color = ntohl(recvCircle.color);
		}
		// ��M�G���[	����M����WSAEWOULDBLOCK������
		else if (WSAGetLastError() != WSAEWOULDBLOCK)
		{
			// ��M���s�̃G���[����
			return 0;
		}


		// �`��
		DrawCircle(circle.centerX, circle.centerY, circle.size, circle.color, 1);

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