#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment( lib, "ws2_32.lib" )

#include "DxLib.h"

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
	// WinSock2.2 ����������
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

	// DxLib����̏������E�E�B���h�E�쐬����
	SetWindowText("�T�[�o�I");
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