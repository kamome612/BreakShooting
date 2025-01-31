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

// �T�[�o��IP�A�h���X
//const char* SERVER_ADDRESS = "127.0.0.1";
//const char* SERVER_ADDRESS = "192.168.43.38";       // �ڑ���Ȃ񂩓K���ɃN���X���[�g�Ƃ���āI
// �T�[�o�̃|�[�g�ԍ�
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
		//�G���[����
		return 0;
	}

	// UDP�\�P�b�g�̍쐬
	//SOCKET sock;
	//sock = socket(AF_INET, SOCK_DGRAM, 0);
	//if (sock == INVALID_SOCKET) {
	//	return 0;
	//}

	//// sock���m���u���b�L���O���[�h��
	//unsigned long cmdarg = 0x01;
	//int ret = ioctlsocket(sock, FIONBIO, &cmdarg);
	//if (ret == SOCKET_ERROR) {
	//	return 0;
	//}

	//// �T�[�o�A�h���X�̎w��
	////SOCKADDR_IN serverAddr;
	//int addrlen = sizeof(serverAddr);

	////�T�[�o�̈�����Z�b�g
	//memset(&serverAddr, 0, sizeof(serverAddr));
	//serverAddr.sin_family = AF_INET;
	//serverAddr.sin_port = htons(SERVER_PORT);
	//inet_pton(AF_INET, (PCSTR)SERVER_ADDRESS, &serverAddr.sin_addr.s_addr);


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

		// �T�C�Y�Ƃ��F�͂��C��
		//CIRCLE circle = { 0, 0, 20, GetColor(138,43,226) };
		//// �}�E�X���W�擾���Acircle��centerX��centerT�Ɋi�[
		//GetMousePoint(&circle.centerX, &circle.centerY);
		//// �`��
		//DrawCircle(circle.centerX, circle.centerY, circle.size, circle.color, 1);

		//// �T�[�o( serverAddr )�Ɂ��̏�񑗐M
		//CIRCLE sendCircle = { htonl(circle.centerX),htonl(circle.centerY),htonl(circle.size),htonl(circle.color) };
		//int ret = sendto(sock, (char*)&sendCircle, sizeof(sendCircle), 0, (SOCKADDR*)&serverAddr, sizeof(serverAddr));


		//// �����M�ȊO�̃G���[
		//if (ret == SOCKET_ERROR && WSAGetLastError() != WSAEWOULDBLOCK)
		//{
		//	// �G���[����
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