#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment( lib, "ws2_32.lib" )

#include "DxLib.h"

#include "Engine/global.h"
#include "Engine/RootObject.h"

namespace Screen {
	static const int WIDTH = 1280;
	static const int HEIGHT = 720;
	static const char* WINDOW_NAME = "SampleGame";
	static const int WINDOW_EXTEND = 0;
	static const int WINDOW_MODE = 1;
};

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


		RefreshDxLibDirect3DSetting();

		ScreenFlip();
	}
	pRootObject->ReleaseSub();
	delete pRootObject;

	DxLib_End();
	return 0;
}