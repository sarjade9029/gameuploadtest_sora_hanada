#include <Windows.h>
#include "../../dxlib/dxlib.h"

// ウィンドウフォーカスをこのアプリにする
// メインループ内で呼ぶ

void focus()
{
	// ウィンドウアクティブ化
	HWND hMainWnd = GetMainWindowHandle();

	if (GetMainWindowHandle() != GetForegroundWindow())
	{
		// ウィンドウアクティブ化
		SetActiveWindow(hMainWnd);

	}
}

// ランチャー(Launcher.exe)呼び出し関数 
// pathにはLauncher.exeへの相対パスへの文字列を入れる
void runLauncher(const char* path)
{

	char fullPathexe[512];
#pragma warning (disable:4996)
	sprintf(fullPathexe, "%s%s", path, "Launcher.exe");

	// プロセス起動準備
	PROCESS_INFORMATION pi = { 0 };
	STARTUPINFO si = { 0 };
	si.cb = sizeof(STARTUPINFO);

	CreateProcess(fullPathexe, (LPSTR)"" , NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, path, &si, &pi);
}

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);
	SetMainWindowText("LeftGameApp");
	
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	SetAlwaysRunFlag(TRUE);
	SetGraphMode( 1600, 900, 32);
	int graph;
	int movieHandle ;

	int fonthandle;
	fonthandle = CreateFontToHandle("メイリオ", 48,10 , DX_FONTTYPE_ANTIALIASING_8X8);

	graph       = LoadGraph("fcalogo.png");
	movieHandle = LoadGraph("../../movie/movie01.mp4");

	// ムービースタート
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

		//ムービー連続再生
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

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	// DxLib_End()の後に呼び出し
	runLauncher("../../");

	return 0;				// ソフトの終了 
}