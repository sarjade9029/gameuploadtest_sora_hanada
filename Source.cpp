#include <Windows.h>
#include "../../dxlib/dxlib.h"

// �E�B���h�E�t�H�[�J�X�����̃A�v���ɂ���
// ���C�����[�v���ŌĂ�

void focus()
{
	// �E�B���h�E�A�N�e�B�u��
	HWND hMainWnd = GetMainWindowHandle();

	if (GetMainWindowHandle() != GetForegroundWindow())
	{
		// �E�B���h�E�A�N�e�B�u��
		SetActiveWindow(hMainWnd);

	}
}

// �����`���[(Launcher.exe)�Ăяo���֐� 
// path�ɂ�Launcher.exe�ւ̑��΃p�X�ւ̕����������
void runLauncher(const char* path)
{

	char fullPathexe[512];
#pragma warning (disable:4996)
	sprintf(fullPathexe, "%s%s", path, "Launcher.exe");

	// �v���Z�X�N������
	PROCESS_INFORMATION pi = { 0 };
	STARTUPINFO si = { 0 };
	si.cb = sizeof(STARTUPINFO);

	CreateProcess(fullPathexe, (LPSTR)"" , NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, path, &si, &pi);
}

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);
	SetMainWindowText("LeftGameApp");
	
	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}
	SetAlwaysRunFlag(TRUE);
	SetGraphMode( 1600, 900, 32);
	int graph;
	int movieHandle ;

	int fonthandle;
	fonthandle = CreateFontToHandle("���C���I", 48,10 , DX_FONTTYPE_ANTIALIASING_8X8);

	graph       = LoadGraph("fcalogo.png");
	movieHandle = LoadGraph("../../movie/movie01.mp4");

	// ���[�r�[�X�^�[�g
	PlayMovieToGraph(movieHandle);


	int anim = 0;
	while (1)
	{
		focus();
		anim -= 2;
		anim %= 1600;

		if (ProcessMessage() != 0) {
			break;
		}
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}

		//���[�r�[�A���Đ�
		if (!GetMovieStateToGraph(movieHandle))
		{
			SeekMovieToGraph(movieHandle,0);
			PlayMovieToGraph(movieHandle);
		}

		SetDrawScreen(DX_SCREEN_BACK);
		ClearDrawScreen();
		DrawExtendGraph(0, 0, 1600, 900, movieHandle, FALSE);
		ScreenFlip();
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	// DxLib_End()�̌�ɌĂяo��
	runLauncher("../../");

	return 0;				// �\�t�g�̏I�� 
}