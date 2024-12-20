#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment( lib, "ws2_32.lib" )

#include "DxLib.h"


// �T�[�o��IP�A�h���X
const char* SERVER_ADDRESS = "127.0.0.1";
//const char* SERVER_ADDRESS = "192.168.43.38";       // �ڑ���Ȃ񂩓K���ɃN���X���[�g�Ƃ���āI
// �T�[�o�̃|�[�g�ԍ�
const unsigned short SERVER_PORT = 8888;

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
		return 0;
	}

	// sock���m���u���b�L���O���[�h��
	unsigned long cmdarg = 0x01;
	int ret = ioctlsocket(sock, FIONBIO, &cmdarg);
	if (ret == SOCKET_ERROR) {
		return 0;
	}

	// �T�[�o�A�h���X�̎w��
	SOCKADDR_IN serverAddr;
	int addrlen = sizeof(serverAddr);

	//�T�[�o�̈�����Z�b�g
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVER_PORT);
	inet_pton(AF_INET, (PCSTR)SERVER_ADDRESS, &serverAddr.sin_addr.s_addr);


	// DxLib����̏������E�E�B���h�E�쐬����
	SetWindowText("�N���C�A���g");
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

		// �T�C�Y�Ƃ��F�͂��C��
		CIRCLE circle = { 0, 0, 20, GetColor(138,43,226) };
		// �}�E�X���W�擾���Acircle��centerX��centerT�Ɋi�[
		GetMousePoint(&circle.centerX, &circle.centerY);
		// �`��
		DrawCircle(circle.centerX, circle.centerY, circle.size, circle.color, 1);

		// �T�[�o( serverAddr )�Ɂ��̏�񑗐M
		CIRCLE sendCircle = { htonl(circle.centerX),htonl(circle.centerY),htonl(circle.size),htonl(circle.color) };
		int ret = sendto(sock, (char*)&sendCircle, sizeof(sendCircle), 0, (SOCKADDR*)&serverAddr, sizeof(serverAddr));


		// �����M�ȊO�̃G���[
		if (ret == SOCKET_ERROR && WSAGetLastError() != WSAEWOULDBLOCK)
		{
			// �G���[����
			return 0;
		}

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